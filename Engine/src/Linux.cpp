#ifdef __linux__

#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <unordered_map>

#include <glad/gl.h>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
typedef Display XDisplay;
typedef Window XWindow;

#include "Context.hpp"

#include "headers/Engine.hpp"
#include "headers/Windows.hpp"
#include "headers/Graphics.hpp"

XDisplay* display;
int screen;
XVisualInfo *vi;
GLXContext glContext;

namespace JintGEEn {
#include <GL/glx.h>
    void Initalize() {
        JintGEEn::InternalContext::SetupContext();
        JintGEEn::Graphics::Setup();
    }
    void Cleanup() {
        JintGEEn::Windows::DestroyAllWindows();
        JintGEEn::InternalContext::CleanupContext();
    }
}

template<class T>
void changeXWindowPropertyAnyType(const char* name, XWindow win, T data) {
    XChangeProperty(display, win, XInternAtom(display, name, False), XA_CARDINAL, 8, PropModeReplace, (const unsigned char*)&data, sizeof(T));
}
template<class T>
T getXWindowPropertyAnyType(const char* name, XWindow win) {
    Atom actualType;
    int actualFormat;
    unsigned long nitems, bytesAfter;
    unsigned char* prop = nullptr;
    XGetWindowProperty(display, win, XInternAtom(display, name, False), 0, sizeof(T), False, XA_CARDINAL, &actualType, &actualFormat, &nitems, &bytesAfter, &prop);
    T data = *((T*)prop);
    XFree(prop);
    return data;
}

namespace JintGEEn {
    namespace InternalContext {
        void SetupContext() {
            display = XOpenDisplay(nullptr);
            if (display == nullptr) {
                std::cerr << "Cannot open X display!" << std::endl;
                return;
            }
        
            screen = DefaultScreen(display);
        
            int attributes[] = {
                GLX_RGBA,
                GLX_DEPTH_SIZE, 24,
                GLX_DOUBLEBUFFER,
                None
            };
            vi = glXChooseVisual(display, 0, attributes);

            glContext = glXCreateContext(display, vi, nullptr, GL_TRUE);
            if (!glContext) {
                std::cerr << "Unable to create OpenGL context!" << std::endl;
                return;
            }

            glXMakeCurrent(display, None, glContext);

            if (!gladLoadGL((GLADloadfunc)glXGetProcAddress)) {
                std::cerr << "Failed to initialize GLAD!" << std::endl;
                glXDestroyContext(display, glContext);
                XCloseDisplay(display);
                return;
            }

            const char* version = (const char*)glGetString(GL_VERSION);
            if (!version) {
                std::cerr << "Failed to get OpenGL version" << std::endl;
                XCloseDisplay(display);
                return;
            }
            std::cout << "OpenGL Version: " << version << std::endl;
        
        }
        void CleanupContext() {
            glXDestroyContext(display, glContext);
            XCloseDisplay(display);
        }
    }
}

// Windows
namespace JintGEEn {
    namespace Windows {
        struct internalWindow {
            XWindow win;
            int x,y;
            unsigned int width, height;
            std::unordered_map<std::string, void*> properties;

            void getWindowGeometry() {
                unsigned int a,b;
                XWindow c;
                XGetGeometry(display, win, &c, &x, &y, &width, &height, &a, &b);
            }
            void setWindowGeometry() {
                XMoveResizeWindow(display, win, x, y, width, height);
                //XFlush(display);
            }
        };
        std::vector<Window*> pWindows;

        void DestroyAllWindows() {
            for (Window* pWindow : pWindows) {
                for (auto property : pWindow->pInternalWindow->properties) {
                    pWindow->DeleteProperty(property.first.c_str());
                }
                DestroyWindow(pWindow);
            }
            pWindows.clear();
        }

        // Window Class
        void Window::SetWidth(unsigned int width) {
            this->pInternalWindow->width = width;
            this->pInternalWindow->setWindowGeometry();
        }
        void Window::SetHeight(unsigned int height) {
            this->pInternalWindow->height = height;
            this->pInternalWindow->setWindowGeometry();
        }
        void Window::SetDimensions(unsigned int width, unsigned int height) {
            this->pInternalWindow->width = width;
            this->pInternalWindow->height = height;
            this->pInternalWindow->setWindowGeometry();
        }
        unsigned int Window::GetWidth() {
            this->pInternalWindow->getWindowGeometry();
            return this->pInternalWindow->width;
        }
        unsigned int Window::GetHeight() {
            this->pInternalWindow->getWindowGeometry();
            return this->pInternalWindow->height;
        }

        void Window::SetXPosition(unsigned int x) {
            this->pInternalWindow->x = x;
            this->pInternalWindow->setWindowGeometry();
        }
        void Window::SetYPosition(unsigned int y) {
            this->pInternalWindow->y = y;
            this->pInternalWindow->setWindowGeometry();
        }
        void Window::SetPosition(unsigned int x, unsigned int y) {
            this->pInternalWindow->x = x;
            this->pInternalWindow->y = y;
            this->pInternalWindow->setWindowGeometry();
        }
        unsigned int Window::GetXPosition() {
            this->pInternalWindow->getWindowGeometry();
            return this->pInternalWindow->x;
        }
        unsigned int Window::GetYPosition() {
            this->pInternalWindow->getWindowGeometry();
            return this->pInternalWindow->y;
        }

        void Window::setProperty(const char* name, void* pData) {
            this->pInternalWindow->properties[name] = pData;
        }
        void* Window::getProperty(const char* name) {
            if (this->propertyExists(name)) {
                return this->pInternalWindow->properties[name];
            } else {
                throw std::runtime_error("Property not found");
            }
        }
        bool Window::propertyExists(const char* name) {
            return this->pInternalWindow->properties.find(name) != this->pInternalWindow->properties.end();
        }
        void Window::deleteProperty(const char* name) {
            if (this->propertyExists(name)) this->pInternalWindow->properties.erase(name);
        }

        Window* CreateWindow(const char* windowTitle, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
            Window* pWindow = new Window;
            pWindow->pInternalWindow = new internalWindow;
            pWindow->pInternalWindow->win = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width,height, 1, BlackPixel(display, screen),WhitePixel(display, screen));
            XSelectInput(display, pWindow->pInternalWindow->win, ExposureMask | KeyPressMask);
            XStoreName(display, pWindow->pInternalWindow->win, windowTitle);
            changeXWindowPropertyAnyType("pWindow", pWindow->pInternalWindow->win, (size_t)pWindow);
            XMapWindow(display, pWindow->pInternalWindow->win);
            return pWindow;
        }
        void DestroyWindow(Window* pWindow) {
            XDestroyWindow(display, pWindow->pInternalWindow->win);
            delete pWindow->pInternalWindow;
            delete pWindow;
        }

        Event NextEvent() {
            XEvent event;
            Event e;

            XNextEvent(display, &event);
            
            if (event.type == Expose) {
                e.type = EventType::Render;
            }

            e.pWindow = (Window*)getXWindowPropertyAnyType<size_t>("pWindow", event.xany.window);

            return e;
        }
    }
}

// Graphics
GLuint compileShader(const char* code, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader compilation failed\n" << infoLog << std::endl;
    }
    return shader;
}
namespace JintGEEn {
    namespace Graphics {
        namespace Shaders {
            struct internalShader {
                GLuint shader;
                std::string code;
                ShaderType type;
            };
        }

        namespace State {
            struct GraphicsState {
                Colour CurrentColour;
                struct internalShaderPipeline {
                    JintGEEn::Graphics::Shaders::Shader* pVertexShader;
                    JintGEEn::Graphics::Shaders::Shader* pFragmentShader;

                    GLuint shaderProgram;
                    void rebuildProgram() {
                        shaderProgram = glCreateProgram();;
                        glAttachShader(shaderProgram, pVertexShader->pInternalShader->shader);
                        glAttachShader(shaderProgram, pFragmentShader->pInternalShader->shader);
                        glLinkProgram(shaderProgram);

                        int success;
                        char infoLog[512];
                        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
                        if (!success) {
                            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
                            std::cerr << "Program Linking Failed: " << infoLog << std::endl;
                        }
                    }
                } CurrentShaderPipeline;
                JintGEEn::Windows::Window* pCurrentWindow = nullptr;
            };
            GraphicsState CurrentState;
            std::vector<GraphicsState> StateStack;
        }

        namespace Shaders {
            ShaderType convertToShaderType(GLenum shaderType) {
                if (shaderType == GL_VERTEX_SHADER) return ShaderType::VERTEX;
                if (shaderType == GL_FRAGMENT_SHADER) return ShaderType::FRAGMENT;
                throw std::runtime_error("Unknown GLenum shader type.");
            }
            GLenum convertToGLShaderType(ShaderType shaderType) {
                if (shaderType == ShaderType::VERTEX) return GL_VERTEX_SHADER;
                if (shaderType == ShaderType::FRAGMENT) return GL_FRAGMENT_SHADER;
                throw std::runtime_error("Unknown shader type.");
            }

            ShaderType Shader::GetShaderType() {
                return this->pInternalShader->type;
            }

            void Shader::SetShaderCode(const char* shaderCode) {
                glDeleteShader(this->pInternalShader->shader);
                this->pInternalShader->code = std::string(shaderCode);
                this->pInternalShader->shader = compileShader(shaderCode, convertToGLShaderType(this->pInternalShader->type));
            }
            const char* Shader::GetShaderCode() {
                return this->pInternalShader->code.c_str();
            }
            
            namespace Defaults {
                Shader* pDefaultVertexShader;
                Shader* pDefaultFragmentShader;
            }

            Shader* CreateShader(const char* shaderCode, ShaderType type) {
                Shader* shader = new Shader;
                shader->pInternalShader = new internalShader;
                shader->pInternalShader->code = std::string(shaderCode);
                shader->pInternalShader->type = type;
                shader->pInternalShader->shader = compileShader(shaderCode, convertToGLShaderType(type));
                return shader;
            }
            void DestoyShader(Shader* pShader) {
                glDeleteShader(pShader->pInternalShader->shader);
                delete pShader->pInternalShader;
                delete pShader;
            }
        }

        namespace Draw {
            void Clear(Colour colour) {
                glClearColor(colour.r, colour.g, colour.b, colour.a);
                glClear(GL_COLOR_BUFFER_BIT);
            }
            void ClearDepth() {
                glClear(GL_DEPTH_BUFFER_BIT);
            }

            void SwapBuffers(JintGEEn::Windows::Window* pWindow) {
                glXSwapBuffers(display, pWindow->pInternalWindow->win);
            }

            void DrawTrangles(std::vector<float>& vertices, std::vector<VertexAttributeDiscriptor>& vertexAttributeDiscriptors, unsigned int stride) {
                GLint oldProgram;
                glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);

                GLuint VAO, VBO;
                glCreateVertexArrays(1, &VAO);
                glBindVertexArray(VAO);

                glCreateBuffers(1, &VBO);
                glNamedBufferData(VBO, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);


                glVertexArrayVertexBuffer(VAO, 0, VBO, 0, stride * sizeof(float));

                for (size_t i = 0; i < vertexAttributeDiscriptors.size(); i++) {
                    VertexAttributeDiscriptor& vad = vertexAttributeDiscriptors[i];

                    glVertexArrayAttribFormat(VAO, vad.index, vad.size, GL_FLOAT, GL_FALSE, vad.offset);
                    glVertexArrayAttribBinding(VAO, vad.index, 0);
                    glEnableVertexArrayAttrib(VAO, vad.index);
                }

                glUseProgram(State::CurrentState.CurrentShaderPipeline.shaderProgram);

                if (glGetUniformLocation(State::CurrentState.CurrentShaderPipeline.shaderProgram, "uColour") != -1) {
                    glUniform4f(glGetUniformLocation(State::CurrentState.CurrentShaderPipeline.shaderProgram, "uColour"),
                        State::CurrentState.CurrentColour.r, State::CurrentState.CurrentColour.g, State::CurrentState.CurrentColour.b, State::CurrentState.CurrentColour.a
                    );
                }

                glDrawArrays(GL_TRIANGLES, 0, 3);
                glBindVertexArray(0);

                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);

                glUseProgram(oldProgram);
            }
        }

        namespace State {
            void Push() {
                StateStack.push_back(CurrentState);
            }
            void Pop() {
                if (StateStack.size() != 0) {
                    CurrentState = StateStack.back();
                    StateStack.pop_back();
                } else {
                    throw std::runtime_error("Trying to pop off of empty state stack (More pops than pushes?)");
                }
            }
            size_t GetStackDepth() {
                return StateStack.size();
            }

            void BindWindow(JintGEEn::Windows::Window* pWindow) {
                CurrentState.pCurrentWindow = pWindow;
                if (pWindow != nullptr) {
                    glXMakeCurrent(display, pWindow->pInternalWindow->win, glContext);
                    glViewport(0,0, pWindow->GetWidth(), pWindow->GetHeight());
                } else {
                    glXMakeCurrent(display, None, glContext);
                }
            }
            JintGEEn::Windows::Window* GetBoundWindow() {
                return CurrentState.pCurrentWindow;
            }

            void SetColour(Colour colour) {
                CurrentState.CurrentColour = colour;
            }
            Colour GetColour() {
                return CurrentState.CurrentColour;
            }

            void SetShader(JintGEEn::Graphics::Shaders::Shader* pShader) {
                if (pShader->GetShaderType() == JintGEEn::Graphics::Shaders::ShaderType::VERTEX) {CurrentState.CurrentShaderPipeline.pVertexShader = pShader; CurrentState.CurrentShaderPipeline.rebuildProgram(); return;}
                if (pShader->GetShaderType() == JintGEEn::Graphics::Shaders::ShaderType::FRAGMENT) {CurrentState.CurrentShaderPipeline.pFragmentShader = pShader; CurrentState.CurrentShaderPipeline.rebuildProgram(); return;}
                throw std::runtime_error("Unsupported shader type.");
            }
            JintGEEn::Graphics::Shaders::Shader* GetShader(JintGEEn::Graphics::Shaders::ShaderType type) {
                if (type == JintGEEn::Graphics::Shaders::ShaderType::VERTEX) return CurrentState.CurrentShaderPipeline.pVertexShader;
                if (type == JintGEEn::Graphics::Shaders::ShaderType::FRAGMENT) return CurrentState.CurrentShaderPipeline.pFragmentShader;
                throw std::runtime_error("Unsupported shader type.");
            }
        }

        void Setup() {
            JintGEEn::Graphics::Shaders::Defaults::pDefaultVertexShader = JintGEEn::Graphics::Shaders::CreateShader(R"(
            #version 460 core

            layout(location = 0) in vec4 aPosition;

            void main() {
                gl_Position = aPosition;
            }
            )", JintGEEn::Graphics::Shaders::ShaderType::VERTEX);
            JintGEEn::Graphics::Shaders::Defaults::pDefaultFragmentShader = JintGEEn::Graphics::Shaders::CreateShader(R"(
            #version 460 core

            out vec4 FragColour;

            uniform vec4 uColour;

            void main() {
                FragColour = uColour;
            }
            )", JintGEEn::Graphics::Shaders::ShaderType::FRAGMENT);
            JintGEEn::Graphics::State::CurrentState.CurrentShaderPipeline.pVertexShader = JintGEEn::Graphics::Shaders::Defaults::pDefaultVertexShader;
            JintGEEn::Graphics::State::CurrentState.CurrentShaderPipeline.pFragmentShader = JintGEEn::Graphics::Shaders::Defaults::pDefaultFragmentShader;
            JintGEEn::Graphics::State::CurrentState.CurrentShaderPipeline.rebuildProgram();
        }
        void Cleanup() {

        }
    }
}

#endif
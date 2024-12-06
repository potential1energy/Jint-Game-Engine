#ifdef __linux__

#include <iostream>

#include <glad/gl.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

#include "Context.hpp"

#include "headers/Engine.hpp"
#include "headers/Windows.hpp"
#include "headers/Graphics.hpp"

Display* display;
int screen;
XVisualInfo *vi;
GLXContext glContext;

namespace JintGEEn {
    void Initalize() {
        JintGEEn::InternalContext::SetupContext();
    }
    void Cleanup() {
        JintGEEn::InternalContext::CleanupContext();
    }
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
        
            glContext = glXCreateContext(display, vi, NULL, GL_TRUE);
            if (!glContext) {
                std::cerr << "Unable to create OpenGL context!" << std::endl;
                return;
            }
        
            glXMakeCurrent(display, None, glContext);
        }
        void CleanupContext() {
            glXDestroyContext(display, glContext);
            XCloseDisplay(display);
        }
    }
}

// Windows
struct internalWindow {
    Window win;
};
namespace JintGEEn {
    namespace Windows {
        Window* CreateWindow(const char* windowTitle, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
            Window* window = new Window;
            internalWindow* pInWindow = new internalWindow;

            pInWindow->win = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width,height, 1, BlackPixel(display, screen),WhitePixel(display, screen));

            XSelectInput(display, pInWindow->win, ExposureMask | KeyPressMask);

            XMapWindow(display, pInWindow->win);

            window->internalWindow = (void*)pInWindow;

            return window;
        }
        void DestroyWindow(Window* pWindow) {
            internalWindow* pInWindow = (internalWindow*)pWindow->internalWindow;
            XDestroyWindow(display, pInWindow->win);

            delete pInWindow;
        }

        void EventUpdate(Window* pWindow) {
            internalWindow* pInWindow = (internalWindow*)pWindow->internalWindow;

            XEvent event;

            XNextEvent(display, &event);  // Wait for the next event

            // Handle events
            if (event.type == Expose) {
                // Redraw the window (triggered when the window is exposed)
                XFillRectangle(display, pInWindow->win, DefaultGC(display, screen),
                               20, 20, 100, 50);
            }
        }
    }
}

// Graphics
struct internalShader {
    const char* code;
    JintGEEn::Graphics::ShaderType type;
    GLuint shader;
};
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
        // Shader
        ShaderType Shader::GetShaderType() {
            internalShader* pInShader = (internalShader*)this->pInternalShader;
            return pInShader->type;
        }

        // Uniforms
        bool Shader::HasUniform(const char* uniformName) {
            return this->GetUniformLocation(uniformName) != -1;
        }
        unsigned int Shader::GetUniformLocation(const char* uniformName) {
            internalShader* pInShader = (internalShader*)this->pInternalShader;
            return glGetUniformLocation(pInShader->shader, uniformName);
        }

        void Shader::SendUniform(unsigned int location, uint32_t v) {
            glUniform1ui(location, v);
        }
        void Shader::SendUniform(unsigned int location, int32_t v) {
            glUniform1i(location, v);
        }
        void Shader::SendUniform(unsigned int location, float v) {
            glUniform1f(location, v);
        }
        void Shader::SendUniform(unsigned int location, double v) {
            glUniform1d(location, v);
        }
        void Shader::SendUniform(unsigned int location, vec2 v) {
            glUniform2f(location, v.x, v.y);
        }
        void Shader::SendUniform(unsigned int location, vec3 v) {
            glUniform3f(location, v.x, v.y, v.z);
        }
        void Shader::SendUniform(unsigned int location, vec4 v) {
            glUniform4f(location, v.x, v.y, v.z, v.w);
        }
        void Shader::SendUniform(unsigned int location, dvec2 v) {
            glUniform2d(location, v.x, v.y);
        }
        void Shader::SendUniform(unsigned int location, dvec3 v) {
            glUniform3d(location, v.x, v.y, v.z);
        }
        void Shader::SendUniform(unsigned int location, dvec4 v) {
            glUniform4d(location, v.x, v.y, v.z, v.w);
        }
        void Shader::SendUniform(unsigned int location, Colour v) {
            glUniform4f(location, v.r, v.g, v.b, v.a);
        }
        
        // Object creation
        Shader* CreateShader(const char* shaderCode, ShaderType type) {
            Shader* shader = new Shader;
            internalShader* pInShader = new internalShader;

            pInShader->code = shaderCode;
            pInShader->type = type;
            
            if (type == ShaderType::VERTEX) {
                pInShader->shader = compileShader(shaderCode, GL_VERTEX_SHADER);
            }
            if (type == ShaderType::FRAGMENT) {
                pInShader->shader = compileShader(shaderCode, GL_FRAGMENT_SHADER);
            }

            shader->pInternalShader = (void*)pInShader;
            
            return shader;
        }
        void DestoyShader(Shader* pShader) {
            internalShader* pInShader = (internalShader*)pShader->pInternalShader;
            glDeleteShader(pInShader->shader);
            delete pInShader;
            delete pShader;
        }
    }
}

#endif
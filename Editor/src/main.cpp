#include "Engine.hpp"
#include "Windows.hpp"
#include "Graphics.hpp"

#include <iostream>

int main() {
    #ifdef __linux__

    JintGEEn::Initalize();

    JintGEEn::Windows::Window* pWindow1 = JintGEEn::Windows::CreateWindow("Test1 window", 0,0, 800,600);
    JintGEEn::Windows::Window* pWindow2 = JintGEEn::Windows::CreateWindow("Test2 window", 0,0, 800,600);


    JintGEEn::Graphics::Shaders::Shader* pVertexShader = JintGEEn::Graphics::Shaders::CreateShader(R"(
    #version 460 core

    layout(location = 0) in vec4 aPosition;
    layout(location = 1) in vec3 aColour;

    out vec3 vColour;

    void main() {
        gl_Position = aPosition;
        vColour = aColour;
    }
    )", JintGEEn::Graphics::Shaders::ShaderType::VERTEX);
    JintGEEn::Graphics::Shaders::Shader* pFragmentShader = JintGEEn::Graphics::Shaders::CreateShader(R"(
    #version 460 core

    in vec3 vColour;
    out vec4 FragColour;

    void main() {
        FragColour = vec4(vColour, 1.0);
    }
    )", JintGEEn::Graphics::Shaders::ShaderType::FRAGMENT);

    JintGEEn::Graphics::State::SetShader(pVertexShader);
    JintGEEn::Graphics::State::SetShader(pFragmentShader);

    while (true) {
        JintGEEn::Windows::Event event = JintGEEn::Windows::NextEvent();

        if (event.type == JintGEEn::Windows::EventType::Render) {
            if (event.pWindow == pWindow1) {
                JintGEEn::Graphics::State::BindWindow(pWindow1);

                JintGEEn::Graphics::State::SetColour({1,0,0,1});
                JintGEEn::Graphics::Draw::Clear({0,0,0,0});

                std::vector<float> vertices = {
                    0.0f,  0.5f, 0.0,0.0,0.0,
                    -0.5f, -0.5f, 1.0,0.0,0.0,
                    0.5f, -0.5f, 1.0,1.0,0.0
                };
                std::vector<JintGEEn::Graphics::Draw::VertexAttributeDiscriptor> discr = {
                    {
                        0,
                        2,
                        false,
                        0
                    },
                    {
                        1,
                        3,
                        false,
                        2 * sizeof(float)
                    }
                };

                JintGEEn::Graphics::Draw::DrawTrangles(vertices, discr, 5);

                JintGEEn::Graphics::Draw::SwapBuffers(pWindow1);

                JintGEEn::Graphics::State::BindWindow(nullptr);
            }
            if (event.pWindow == pWindow2) {
                JintGEEn::Graphics::State::BindWindow(pWindow2);

                JintGEEn::Graphics::State::SetColour({1,0,0,1});
                JintGEEn::Graphics::Draw::Clear({0,0,0,0});

                std::vector<float> vertices = {
                    0.0f,  0.5f, 0.0,1.0,0.0,
                    -0.5f, -0.5f, 0.0,0.0,1.0,
                    0.5f, -0.5f, 0.0,1.0,1.0
                };
                std::vector<JintGEEn::Graphics::Draw::VertexAttributeDiscriptor> discr = {
                    {
                        0,
                        2,
                        false,
                        0
                    },
                    {
                        1,
                        3,
                        false,
                        2 * sizeof(float)
                    }
                };

                JintGEEn::Graphics::Draw::DrawTrangles(vertices, discr, 5);

                JintGEEn::Graphics::Draw::SwapBuffers(pWindow2);

                JintGEEn::Graphics::State::BindWindow(nullptr);
            }
        }
    }

    JintGEEn::Windows::DestroyAllWindows();
    JintGEEn::Cleanup();
    #endif

    #ifdef _WIN64

    std::cout << "Window is not supported yet.\n";

    #endif
}
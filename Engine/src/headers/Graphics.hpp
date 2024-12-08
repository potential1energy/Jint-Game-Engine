#pragma once

#include <vector>
#include <stdint.h>

#include "Windows.hpp"

namespace JintGEEn {
    namespace Graphics {
        struct Colour {float r=0,g=0,b=0,a=1;};

        void Setup();
        void Cleanup();

        namespace Shaders {
            struct internalShader;

            enum class ShaderType {
                VERTEX, FRAGMENT
            };
            class Shader {
            public:
                // Shader Type
                ShaderType GetShaderType();

                void SetShaderCode(const char* shaderCode);
                const char* GetShaderCode();

                // Internal shader
                internalShader* pInternalShader;
            };
            namespace Defaults {
                extern Shader* pDefaultVertexShader;
                extern Shader* pDefaultFragmentShader;
            }

            Shader* CreateShader(const char* shaderCode, ShaderType type);
            void DestoyShader(Shader* pShader);
        }

        namespace Draw {
            struct VertexAttributeDiscriptor {
                size_t index;
                size_t size;
                bool normalize;
                size_t offset;
            };

            void Clear(Colour colour);
            void ClearDepth();

            void SwapBuffers(JintGEEn::Windows::Window* pWindow);
    
            void DrawTrangles(std::vector<float>& vertices, std::vector<VertexAttributeDiscriptor>& vertexAttributeDiscriptors, unsigned int stride);
        }

        namespace State {
            void Push();
            void Pop();
            size_t GetStackDepth();

            void BindWindow(JintGEEn::Windows::Window* pWindow);
            JintGEEn::Windows::Window* GetBoundWindow();

            void SetColour(Colour colour);
            Colour GetColour();

            void SetShader(JintGEEn::Graphics::Shaders::Shader* pShader);
            JintGEEn::Graphics::Shaders::Shader* GetShader(JintGEEn::Graphics::Shaders::ShaderType type);
        }
    }
}
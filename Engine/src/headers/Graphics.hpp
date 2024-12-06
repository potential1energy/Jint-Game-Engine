#pragma once

#include <vector>
#include <stdint.h>

#include "Windows.hpp"

namespace JintGEEn {
    namespace Graphics {
        struct vec2 {
            float x,y;
        };
        struct vec3 {
            float x,y,z;
        };
        struct vec4 {
            float x,y,z,w;
        };
        struct dvec2 {
            double x,y;
        };
        struct dvec3 {
            double x,y,z;
        };
        struct dvec4 {
            double x,y,z,w;
        };
        struct Colour {
            float r,g,b,a;
        };

        enum class ShaderType {
            VERTEX, FRAGMENT
        };
        class Shader {
        public:
            // Shader Type
            ShaderType GetShaderType();

            // Uniforms
            bool HasUniform(const char* uniformName);
            unsigned int GetUniformLocation(const char* uniformName);

            void SendUniform(unsigned int location, uint8_t v);
            void SendUniform(unsigned int location, int8_t v);
            void SendUniform(unsigned int location, uint16_t v);
            void SendUniform(unsigned int location, int16_t v);
            void SendUniform(unsigned int location, uint32_t v);
            void SendUniform(unsigned int location, int32_t v);
            void SendUniform(unsigned int location, float v);
            void SendUniform(unsigned int location, double v);
            void SendUniform(unsigned int location, vec2 v);
            void SendUniform(unsigned int location, vec3 v);
            void SendUniform(unsigned int location, vec4 v);
            void SendUniform(unsigned int location, dvec2 v);
            void SendUniform(unsigned int location, dvec3 v);
            void SendUniform(unsigned int location, dvec4 v);
            void SendUniform(unsigned int location, Colour v);

            // Internal shader
            void* pInternalShader;
        };
        struct RenderPipeline {
            Shader* VertexShader;
            Shader* FragmentShader;
        };

        // Object creation
        Shader* CreateShader(const char* shaderCode, ShaderType type);

        // Graphics state stack
        void Push();
        void Pop();
        size_t GetStackDepth();

        // Graphics state
        void BindWindow(JintGEEn::Windows::Window* pWindow);
        JintGEEn::Windows::Window* GetBoundWindow();

        void SetColour(Colour colour);
        Colour GetColour();

        void SetShader(Shader* shader, ShaderType type);
        Shader* GetShader(ShaderType type);

        void SetRenderPipeline(RenderPipeline renderPipeline);
        RenderPipeline GetRenderPipeline();

        namespace Draw {
            enum class VertexAttributeType {
                BYTE, UBYTE,
                SHORT, USHORT,
                INT, UINT,
                HALFFLOAT, FLOAT, DOUBLE
            };
            struct VertexAttributeDiscriptor {
                size_t index;
                size_t size;
                VertexAttributeType type;
                bool normalize;
                size_t stride, offset;
            };

            void DrawTrangles(std::vector<float>& verticies, std::vector<VertexAttributeDiscriptor>& vertexAttributeDiscriptors);
        }
    }
}
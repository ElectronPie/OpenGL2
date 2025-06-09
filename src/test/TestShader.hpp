#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Renderer.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <string>

namespace Tests
{
    class TestShader: public Test
    {
    public:
        TestShader();
        ~TestShader();

        void OnRender() override;
        void OnImGuiRender() override;
        void OnUpdate(float deltaTime) override;

    private:
        std::string m_fragmentShaderPath = "assets/shaders/TestShader/TestShader.frag.glsl";

        // clang-format off
        static inline float s_vertices[12] = {
            // position
            -1.0f, +1.0f, 0.0f,     // top left
            +1.0f, +1.0f, 0.0f,     // top right
            +1.0f, -1.0f, 0.0f,     // bottom right
            -1.0f, -1.0f, 0.0f,     // bottom left
        };
        static inline unsigned int s_indices[6] = {
            0, 1, 2,
            0, 2, 3,
        };
        // clang-format on
        VBO m_vbo;
        VBLayout m_layout;
        EBO m_ebo;
        VAO m_vao;
        ShaderProgram m_shaderProgram;
        Renderer& m_rendererInstance;

        float m_time = 0.0f;
        glm::vec2 m_mouse;
        glm::vec2 m_resolution;

        int m_easingTypeID = 0;
        static inline const char* s_easingTypes =
            "Linear (none)\0"
            "Sine\0"
            "Circular\0"
            "Quadratic\0"
            "Cubic\0"
            "Quartic\0"
            "Quintic\0"
            "Exponential\0"
            "Ease-Back\0"
            "Elastic\0"
            "Bounce\0";

        int m_easingCharacterID                      = 0;
        static inline const char* s_easingCharacters = "In\0Out\0In-Out\0Out-In\0";
    };
} // namespace Tests

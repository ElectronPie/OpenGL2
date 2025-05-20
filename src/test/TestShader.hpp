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

        int m_functionID = 0;
        static inline const char* s_functions =
            "Default linear\0"
            "Blinn - Wyvil cosine approximation\0"
            "Double cubic seat\0"
            "Double cubic seat with linear blend\0"
            "Double odd polynomial seat\0"
            "Double polynomial sigmoid\0"
            "Quadratic through a given point\0"
            "Exponential easing\0"
            "Double exponential seat\0"
            "Double exponential sigmoid\0"
            "Logistic sigmoid\0"
            "Circular ease-in\0"
            "Circular ease-out\0"
            "Double circle seat\0"
            "Double circle sigmoid\0"
            "Double elliptic seat\0"
            "Double elliptic sigmoid\0"
            "Two lines joined with a circular arc fillet\0"
            "Circular arc through a given point\0"
            "Quadratic Bezier\0"
            "Cubic Bezier\0"
            "Cubic Bezier nearly through two points\0"
            "Almost identity\0"
            "Almost abs\0"
            "Smoothstep integral\0"
            "Exponential impulse\0"
            "Quadratic impulse\0"
            "Polynomial impulse\0"
            "Exponential sustained impulse\0"
            "Sinc\0"
            "Truncated falloff\0"
            "Almost unit identity\0"
            "Gain\0"
            "Parabola\0"
            "Power curve\0"
            "Tone map\0"
            "Cubic pulse\0"
            "Rational bump\0"
            "Exponential step\0";
        float m_zoom = 1.0f;
        glm::vec2 m_p1{0.0f};
        glm::vec2 m_p2{1.0f};
        float m_point = 0.0f;
        float m_inflection = 1.0f;
        int m_exponent = 1;
        float m_radius = 0.5f;
    };
} // namespace Tests

#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"

#include "Camera.hpp"

namespace Tests
{
    /**
     * @brief Lighting test
     */
    class TestLighting: public Test
    {
    public:
        /**
         * @brief Construct a new Test Lighting object
         */
        TestLighting();
        /**
         * @brief Destroy the Test Lighting object
         */
        virtual ~TestLighting();

        /**
         * @copydoc Tests::Test::OnRender
         */
        void OnRender() override;
        /**
         * @copydoc Tests::Test::OnImGuiRender
         */
        void OnImGuiRender() override;
        /**
         * @copydoc Tests::Test::OnUpdate
         */
        void OnUpdate(float deltaTime) override;

    private:
        // clang-format off
        static inline float s_vertices[] = {
            // position             // normal
            -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,
        };
        // clang-format on
        VBO m_vbo;
        VBLayout m_layout;
        VAO m_objectVAO;
        VAO m_lightVAO;
        ShaderProgram m_phongShaderProgram;
        ShaderProgram m_gouraudShaderProgram;
        ShaderProgram m_lightShaderProgram;

        bool m_useGouraud = false;

        glm::vec3 m_objectColor{1.0f, 0.5f, 0.31f};
        glm::vec3 m_lightColor{1.0f, 1.0f, 1.0f};

        glm::vec3 m_lightPos{1.2f, 1.0f, 2.0f};

        float m_ambientStrength = 0.1f;
        float m_diffuseStrength = 1.0f;
        float m_specularStrength = 0.5f;
        int m_shininessExponent = 5;

        Camera m_camera;
        glm::vec2 m_cursorPos;
        bool m_mouseButtonPressed = false;
    };
} // namespace Tests

#pragma once

#include "Test.hpp"
#include "Camera.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>

namespace Tests
{
    /**
     * @brief Camera test
     */
    class TestCamera: public Test
    {
    public:
        /**
         * @brief Construct a new TestCamera object
         */
        TestCamera();
        /**
         * @brief Destroy the TestCamera object
         */
        virtual ~TestCamera();

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
        /**
         * @brief Vertices of a cube
         */
        static inline float s_vertices[180] = {
            // position             // texture coords
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
            +0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
            +0.5f, +0.5f, -0.5f,    1.0f, 1.0f,
            +0.5f, +0.5f, -0.5f,    1.0f, 1.0f,
            -0.5f, +0.5f, -0.5f,    0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,

            -0.5f, -0.5f, +0.5f,    0.0f, 0.0f,
            +0.5f, -0.5f, +0.5f,    1.0f, 0.0f,
            +0.5f, +0.5f, +0.5f,    1.0f, 1.0f,
            +0.5f, +0.5f, +0.5f,    1.0f, 1.0f,
            -0.5f, +0.5f, +0.5f,    0.0f, 1.0f,
            -0.5f, -0.5f, +0.5f,    0.0f, 0.0f,

            -0.5f, +0.5f, +0.5f,    1.0f, 0.0f,
            -0.5f, +0.5f, -0.5f,    1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
            -0.5f, -0.5f, +0.5f,    0.0f, 0.0f,
            -0.5f, +0.5f, +0.5f,    1.0f, 0.0f,

            +0.5f, +0.5f, +0.5f,    1.0f, 0.0f,
            +0.5f, +0.5f, -0.5f,    1.0f, 1.0f,
            +0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
            +0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
            +0.5f, -0.5f, +0.5f,    0.0f, 0.0f,
            +0.5f, +0.5f, +0.5f,    1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
            +0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
            +0.5f, -0.5f, +0.5f,    1.0f, 0.0f,
            +0.5f, -0.5f, +0.5f,    1.0f, 0.0f,
            -0.5f, -0.5f, +0.5f,    0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,

            -0.5f, +0.5f, -0.5f,    0.0f, 1.0f,
            +0.5f, +0.5f, -0.5f,    1.0f, 1.0f,
            +0.5f, +0.5f, +0.5f,    1.0f, 0.0f,
            +0.5f, +0.5f, +0.5f,    1.0f, 0.0f,
            -0.5f, +0.5f, +0.5f,    0.0f, 0.0f,
            -0.5f, +0.5f, -0.5f,    0.0f, 1.0f,
        };
        // clang-format on
        /**
         * @brief Vertex buffer object for the cube
         */
        VBO m_vbo;
        /**
         * @brief The cube's vertex buffers' layout
         */
        VBLayout m_layout;
        /**
         * @brief Cube's vertex array object
         */
        VAO m_vao;
        /**
         * @brief The shader program
         */
        ShaderProgram m_shaderProgram;
        /**
         * @brief A texture
         */
        Texture m_texture1;
        /**
         * @brief A texture
         */
        Texture m_texture2;

        /**
         * @brief The cubes' positions
         */
        static inline glm::vec3 s_cubePositions[] = {
            {0.0f,  0.0f,  0.0f  },
            {2.0f,  5.0f,  -15.0f},
            {-1.5f, -2.2f, -2.5f },
            {-3.8f, -2.0f, -12.3f},
            {2.4f,  -0.4f, -3.5f },
            {-1.7f, 3.0f,  -7.5f },
            {1.3f,  -2.0f, -2.5f },
            {1.5f,  2.0f,  -2.5f },
            {1.5f,  0.2f,  -1.5f },
            {-1.3f, 1.0f,  -1.5f },
        };

        /**
         * @brief The camera being tested
         */
        Camera m_camera;

        /**
         * @brief The way the camera should be handled
         */
        int m_cameraMode     = 0;
        /**
         * @brief Internal time \(in seconds\)
         */
        float m_timeMark     = 0.0f;
        /**
         * @brief The radius of the circle the camera makes
         */
        float m_circleRadius = 10.0f;
    };
} // namespace Tests

#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include <glm/glm.hpp>

#define __TEST_DEPTH_PAIR_STR(x) {x, #x}

namespace Tests
{
    /**
     * @brief Test for depth testing
     */
    class TestDepth: public Test
    {
    public:
        /**
         * @brief Construct a new TestDepth object
         */
        TestDepth();
        /**
         * @brief Destroy the TestDepth object
         */
        virtual ~TestDepth();

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
         * @brief Vertices of a plane
         */
        static inline float s_planeVertices[20] = {
            // position             // texture coords
            +0.5f, +0.5f, 0.0f,     1.0f, 1.0f,     // top right
            +0.5f, -0.5f, 0.0f,     1.0f, 0.0f,     // bottom right
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     // bottom left
            -0.5f, +0.5f, 0.0f,     0.0f, 1.0f,     // top left
        };
        /**
         * @brief Indices for the plane's vertices
         */
        static inline unsigned int s_planeIndices[6] = {
            0, 1, 2,
            0, 2, 3,
        };
        // clang-format on
        /**
         * @brief Vertex buffer object for the plane
         */
        VBO m_planeVBO;
        /**
         * @brief The plane's vertex buffers' layout
         */
        VBLayout m_planeLayout;
        /**
         * @brief Element buffer object for the plane's indices
         */
        EBO m_planeEBO;
        /**
         * @brief Plane's vertex array object
         */
        VAO m_planeVAO;
        /**
         * @brief Texture for the plane
         */
        Texture m_planeTexture;

        // clang-format off
        /**
         * @brief Vertices of a cube
         */
        static inline float s_cubeVertices[180] = {
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
        VBO m_cubeVBO;
        /**
         * @brief The cube's vertex buffers' layout
         */
        VBLayout m_cubeLayout;
        /**
         * @brief Cube's vertex array object
         */
        VAO m_cubeVAO;
        /**
         * @brief Texture for the cube
         */
        Texture m_cubeTexture;

        /**
         * @brief The shader program to display the scene
         */
        ShaderProgram m_shaderProgram;

        /**
         * @brief The camera used to view the scene
         */
        Camera m_camera;
        /**
         * @brief The cursor's position on the screen
         */
        glm::vec2 m_cursorPos;
        /**
         * @brief Is the left mouse button pressed
         */
        bool m_mouseButtonPressed = false;

        /**
         * @brief Positions of the cubes in the scene
         */
        static inline glm::vec3 s_cubePositions[] = {
            {0.0f, 0.5f, 0.0f },
            {0.5f, 0.0f, -3.0f}
        };

        /**
         * @brief Is depth testing enabled
         */
        bool m_depthTestEnabled   = true;
        /**
         * @brief Whether to clear the depth buffer before rendering
         */
        bool m_clearDepthBuffer   = true;
        /**
         * @brief Whether to display the depth buffer
         */
        bool m_displayDepthBuffer = false;

        /**
         * @brief Depth functions for the combo box
         */
        static inline std::pair<unsigned int, const char*> s_depthFuncs[] = {
            __TEST_DEPTH_PAIR_STR(GL_LESS), // Default (index = 0)
            __TEST_DEPTH_PAIR_STR(GL_LEQUAL),
            __TEST_DEPTH_PAIR_STR(GL_EQUAL),
            __TEST_DEPTH_PAIR_STR(GL_GREATER),
            __TEST_DEPTH_PAIR_STR(GL_GEQUAL),
            __TEST_DEPTH_PAIR_STR(GL_NOTEQUAL),
            __TEST_DEPTH_PAIR_STR(GL_ALWAYS),
            __TEST_DEPTH_PAIR_STR(GL_NEVER),
        };
        /**
         * @brief Number of depth functions
         */
        constexpr static int s_depthFuncsCount = sizeof(s_depthFuncs) / sizeof(s_depthFuncs[0]);
        /**
         * @brief Current depth function index
         */
        int m_currentDepthFuncIndex            = 0; // GL_LESS
    };
} //namespace Tests

#undef __TEST_DEPTH_PAIR_STR

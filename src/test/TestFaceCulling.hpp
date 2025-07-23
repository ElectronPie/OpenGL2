#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#define __TEST_FACE_CULLING_PAIR_STR(x) {x, #x}

namespace Tests
{
    class TestFaceCulling: public Test
    {
    public:
        /**
         * @brief Construct a new TestFaceCulling object
         */
        TestFaceCulling();
        /**
         * @brief Destroy the TestFaceCulling object
         */
        ~TestFaceCulling();

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
         * @brief Vertices of a cube in a counter-clockwise order
         */
        static inline float s_cubeVertices[] = {
            // position             // texture coords
            // Back face
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, // Bottom-left
            +0.5f, +0.5f, -0.5f,    1.0f, 1.0f, // top-right
            +0.5f, -0.5f, -0.5f,    1.0f, 0.0f, // bottom-right
            +0.5f, +0.5f, -0.5f,    1.0f, 1.0f, // top-right
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, // bottom-left
            -0.5f, +0.5f, -0.5f,    0.0f, 1.0f, // top-left
            // Front face
            -0.5f, -0.5f, +0.5f,    0.0f, 0.0f, // bottom-left
            +0.5f, -0.5f, +0.5f,    1.0f, 0.0f, // bottom-right
            +0.5f, +0.5f, +0.5f,    1.0f, 1.0f, // top-right
            +0.5f, +0.5f, +0.5f,    1.0f, 1.0f, // top-right
            -0.5f, +0.5f, +0.5f,    0.0f, 1.0f, // top-left
            -0.5f, -0.5f, +0.5f,    0.0f, 0.0f, // bottom-left
            // Left face
            -0.5f, +0.5f, +0.5f,    1.0f, 0.0f, // top-right
            -0.5f, +0.5f, -0.5f,    1.0f, 1.0f, // top-left
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, // bottom-left
            -0.5f, -0.5f, +0.5f,    0.0f, 0.0f, // bottom-right
            -0.5f, +0.5f, +0.5f,    1.0f, 0.0f, // top-right
            // Right face
            +0.5f, +0.5f, +0.5f,    1.0f, 0.0f, // top-left
            +0.5f, -0.5f, -0.5f,    0.0f, 1.0f, // bottom-right
            +0.5f, +0.5f, -0.5f,    1.0f, 1.0f, // top-right
            +0.5f, -0.5f, -0.5f,    0.0f, 1.0f, // bottom-right
            +0.5f, +0.5f, +0.5f,    1.0f, 0.0f, // top-left
            +0.5f, -0.5f, +0.5f,    0.0f, 0.0f, // bottom-left
            // Bottom face
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, // top-right
            +0.5f, -0.5f, -0.5f,    1.0f, 1.0f, // top-left
            +0.5f, -0.5f, +0.5f,    1.0f, 0.0f, // bottom-left
            +0.5f, -0.5f, +0.5f,    1.0f, 0.0f, // bottom-left
            -0.5f, -0.5f, +0.5f,    0.0f, 0.0f, // bottom-right
            -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, // top-right
            // Top face
            -0.5f, +0.5f, -0.5f,    0.0f, 1.0f, // top-left
            +0.5f, +0.5f, +0.5f,    1.0f, 0.0f, // bottom-right
            +0.5f, +0.5f, -0.5f,    1.0f, 1.0f, // top-right
            +0.5f, +0.5f, +0.5f,    1.0f, 0.0f, // bottom-right
            -0.5f, +0.5f, -0.5f,    0.0f, 1.0f, // top-left
            -0.5f, +0.5f, +0.5f,    0.0f, 0.0f  // bottom-left
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
         * @brief Shader program to render the cube
         */
        ShaderProgram m_shaderProgram;

        /**
         * @brief The camera used to view the scene
         */
        Camera m_camera;

        /**
         * @brief Whether to enable face culling
         */
        bool m_enableFaceCulling = true;

        /**
         * @brief Value-name pairs of cull face values
         */
        constexpr static inline std::pair<GLenum, const char*> s_cullFaceValues[] = {
            __TEST_FACE_CULLING_PAIR_STR(GL_FRONT),
            __TEST_FACE_CULLING_PAIR_STR(GL_BACK), // Default cull face value (index = 1)
            __TEST_FACE_CULLING_PAIR_STR(GL_FRONT_AND_BACK),
        };
        /**
         * @brief Number of cull face value-name pairs
         */
        constexpr static inline std::size_t s_numCullFaceValues =
            sizeof(s_cullFaceValues) / sizeof(s_cullFaceValues[0]);
        /**
         * @brief Current cull face value index
         */
        int m_currentCullFaceIdx = 1;

        /**
         * @brief Value-name pairs of front face values
         */
        constexpr static inline std::pair<GLenum, const char*> s_frontFaceValues[] = {
            __TEST_FACE_CULLING_PAIR_STR(GL_CCW), // Default front face value (index = 1)
            __TEST_FACE_CULLING_PAIR_STR(GL_CW),
        };
        /**
         * @brief Number of front face value-name pairs
         */
        constexpr static inline std::size_t s_numFrontFaceValues =
            sizeof(s_frontFaceValues) / sizeof(s_frontFaceValues[0]);
        /**
         * @brief Current front face value index
         */
        int m_currentFrontFaceIdx = 0;
    };
} // namespace Tests

#undef __TEST_FACE_CULLING_PAIR_STR

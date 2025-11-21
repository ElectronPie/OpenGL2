#pragma once

#include "Test.hpp"

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "RBO.hpp"
#include "FBO.hpp"
#include "Camera.hpp"

#include <glm/glm.hpp>

#define __TEST_FRAMEBUFFER_PAIR_STR(x) {x, #x}

namespace Tests
{
    class TestFramebuffer: public Test
    {
    public:
        /**
         * @brief Construct a new Test Framebuffer object
         */
        TestFramebuffer();
        /**
         * @brief Destroy the Test Framebuffer object
         */
        virtual ~TestFramebuffer();

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
         * @brief Positions of the cubes in the scene
         */
        static inline glm::vec3 s_cubePositions[] = {
            {0.0f, 0.5f, 0.0f },
            {0.5f, 0.0f, -3.0f},
        };

        /**
         * @brief The shader program to display the scene
         */
        ShaderProgram m_sceneShaderProgram;

        /**
         * @brief The camera used to view the scene
         */
        Camera m_camera;

        /**
         * @brief The shader program to display the framebuffer texture on a quad
         */
        ShaderProgram m_screenShaderProgram;
        // clang-format off
        /**
         * @brief Vertices of a plane
         */
        static inline float s_quadVertices[20] = {
            // position             // texture coords
            +1.0f, +1.0f, 0.0f,     1.0f, 1.0f,     // top right
            +1.0f, -1.0f, 0.0f,     1.0f, 0.0f,     // bottom right
            -1.0f, -1.0f, 0.0f,     0.0f, 0.0f,     // bottom left
            -1.0f, +1.0f, 0.0f,     0.0f, 1.0f,     // top left
        };
        /**
         * @brief Indices for the plane's vertices
         */
        static inline unsigned int s_quadIndices[6] = {
            0, 1, 2,
            0, 2, 3,
        };
        // clang-format on
        /**
         * @brief Vertex buffer object for the plane
         */
        VBO m_quadVBO;
        /**
         * @brief The plane's vertex buffers' layout
         */
        VBLayout m_quadLayout;
        /**
         * @brief Element buffer object for the plane's indices
         */
        EBO m_quadEBO;
        /**
         * @brief Plane's vertex array object
         */
        VAO m_quadVAO;
        /**
         * @brief Framebuffer object to render the scene to
         */
        FBO m_FBO;
        /**
         * @brief Texture to render the scene to
         */
        Texture m_screenTexture;
        /**
         * @brief Renderbuffer object for depth and stencil attachment
         */
        RBO m_RBO;

        /**
         * @brief Face types specified in the call to glPolygonMode
         */
        static inline std::pair<unsigned int, const char*> s_faceTypes[] = {
            __TEST_FRAMEBUFFER_PAIR_STR(GL_FRONT),
            __TEST_FRAMEBUFFER_PAIR_STR(GL_BACK),
            __TEST_FRAMEBUFFER_PAIR_STR(GL_FRONT_AND_BACK), // Default (index = 2)
        };
        /**
         * @brief Number of face types specified in the call to glPolygonMode
         */
        constexpr static int s_faceTypesCount = sizeof(s_faceTypes) / sizeof(s_faceTypes[0]);
        /**
         * @brief Current face type index
         */
        int m_currentFaceTypeIdx              = 2; // GL_FRONT_AND_BACK

        /**
         * @brief Polygon modes specified in the call to glPolygonMode
         */
        static inline std::pair<unsigned int, const char*> s_polygonModes[] = {
            __TEST_FRAMEBUFFER_PAIR_STR(GL_POINT),
            __TEST_FRAMEBUFFER_PAIR_STR(GL_LINE),
            __TEST_FRAMEBUFFER_PAIR_STR(GL_FILL), // Default (index = 2)
        };
        /**
         * @brief Number of polygon modes
         */
        constexpr static int s_polygonModesCount = sizeof(s_polygonModes) / sizeof(s_polygonModes[0]);
        /**
         * @brief Current polygon mode index
         */
        int m_currentPolygonModeIdx              = 2; // GL_FILL

        /**
         * @brief Shader names for the screen shader
         */
        static inline const char* s_shaderNames[] = {
            "Screen", // Default (index = 0)
            "Inverse",
            "BlackAndWhite",
            "Grayscale",
            "Sharpen",
            "Blur",
            "Edges",
        };
        /**
         * @brief Number of shader names
         */
        constexpr static int s_shaderNamesCount = sizeof(s_shaderNames) / sizeof(s_shaderNames[0]);
        /**
         * @brief Current shader name index
         */
        int m_currentShaderName                 = 0; // Screen
    };
} // namespace Tests

#undef __TEST_FRAMEBUFFER_PAIR_STR

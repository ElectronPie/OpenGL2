#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#define __TEST_BLENDING_PAIR_STR(x) {x, #x}

namespace Tests
{
    class TestBlending: public Test
    {
    public:
        /**
         * @brief Construct a new TestBlending object
         */
        TestBlending();
        /**
         * @brief Destroy the TestBlending object
         */
        virtual ~TestBlending();

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
        static inline float s_planeVertices[30] = {
            // positions            // texture Coords
                                    // (note we set these higher than 1
                                    // (together with GL_REPEAT as texture wrapping mode).
                                    // this will cause the floor texture to repeat)
            +5.0f, -0.5f, +5.0f,    2.0f, 0.0f,
            -5.0f, -0.5f, +5.0f,    0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,    0.0f, 2.0f,

            +5.0f, -0.5f, +5.0f,    2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,    0.0f, 2.0f,
            +5.0f, -0.5f, -5.0f,    2.0f, 2.0f,
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

        // clang-format off
        /**
         * @brief Vertices of a small quad
         */
        static inline float s_quadVertices[30] = {
            // position             // texture coords
            1.0f, +0.5f, 0.0f,      1.0f, 1.0f,
            0.0f, +0.5f, 0.0f,      0.0f, 1.0f,
            0.0f, -0.5f, 0.0f,      0.0f, 0.0f,

            1.0f, +0.5f, 0.0f,      1.0f, 1.0f,
            0.0f, -0.5f, 0.0f,      0.0f, 0.0f,
            1.0f, -0.5f, 0.0f,      1.0f, 0.0f,
        };
        // clang-format on
        /**
         * @brief Vertex buffer object for the quad
         */
        VBO m_quadVBO;
        /**
         * @brief The small quad's vertex buffer's layout
         */
        VBLayout m_quadLayout;
        /**
         * @brief Quad's vertex array object
         */
        VAO m_quadVAO;
        /**
         * @brief Texture for grass
         */
        Texture m_grassTexture;
        /**
         * @brief A semi-transparent window texture
         */
        Texture m_windowTexture;

        /**
         * @brief Shader program to render the scene
         */
        ShaderProgram m_shaderProgram;

        /**
         * @brief The camera used to view the scene
         */
        Camera m_camera;

        /**
         * @brief Positions of the cubes in the scene
         */
        static inline glm::vec3 s_cubePositions[] = {
            {-1.0f, 0.0f, -1.0f},
            {2.0f,  0.0f, 0.0f },
        };

        /**
         * @brief Positions of patches of grass in the scene
         */
        static inline glm::vec3 s_quadsPositions[] = {
            {-1.5f, 0.0f, -0.48f},
            {1.5f,  0.0f, 0.51f },
            {0.0f,  0.0f, 0.7f  },
            {-0.3f, 0.0f, -2.3f },
            {0.5f,  0.0f, -0.6f },
        };

        /**
         * @brief Whether to render semi-transparent windows
         */
        bool m_renderWindows = false;

        /**
         * @brief Whether to enable blending
         */
        bool m_enableBlending = true;

        /**
         * @brief Value-name pairs of blending factor values
         */
        constexpr static inline std::pair<GLenum, const char*> s_factorValues[] = {
            __TEST_BLENDING_PAIR_STR(GL_ZERO),
            __TEST_BLENDING_PAIR_STR(GL_ONE),
            __TEST_BLENDING_PAIR_STR(GL_SRC_COLOR),
            __TEST_BLENDING_PAIR_STR(GL_ONE_MINUS_SRC_COLOR),
            __TEST_BLENDING_PAIR_STR(GL_DST_COLOR),
            __TEST_BLENDING_PAIR_STR(GL_ONE_MINUS_DST_COLOR),
            __TEST_BLENDING_PAIR_STR(GL_SRC_ALPHA),           // Default Source factor (index 6)
            __TEST_BLENDING_PAIR_STR(GL_ONE_MINUS_SRC_ALPHA), // Default Destination factor (index 7)
            __TEST_BLENDING_PAIR_STR(GL_DST_ALPHA),
            __TEST_BLENDING_PAIR_STR(GL_ONE_MINUS_DST_ALPHA),
            __TEST_BLENDING_PAIR_STR(GL_CONSTANT_COLOR),
            __TEST_BLENDING_PAIR_STR(GL_ONE_MINUS_CONSTANT_COLOR),
            __TEST_BLENDING_PAIR_STR(GL_CONSTANT_ALPHA),
            __TEST_BLENDING_PAIR_STR(GL_ONE_MINUS_CONSTANT_ALPHA),
        };
        /**
         * @brief Number of blending factor value-name pairs
         */
        constexpr static inline std::size_t s_numFactors = sizeof(s_factorValues) / sizeof(s_factorValues[0]);

        /**
         * @brief Value-name pairs of blending equation values
         */
        constexpr static inline std::pair<GLenum, const char*> s_equationValues[] = {
            __TEST_BLENDING_PAIR_STR(GL_FUNC_ADD), // Default Blending equation (index 0)
            __TEST_BLENDING_PAIR_STR(GL_FUNC_SUBTRACT),
            __TEST_BLENDING_PAIR_STR(GL_FUNC_REVERSE_SUBTRACT),
            __TEST_BLENDING_PAIR_STR(GL_MIN),
            __TEST_BLENDING_PAIR_STR(GL_MAX),
        };
        /**
         * @brief Number of blending equation value-name pairs
         */
        constexpr static inline std::size_t s_numEquations = sizeof(s_equationValues) / sizeof(*s_equationValues);

        /**
         * @brief Current blending source factor index
         */
        int m_currentSRCFactorIdx     = 6;
        /**
         * @brief Current blending destination factor index
         */
        int m_currentDSTFactorIdx     = 7;
        /**
         * @brief Current blending equation index
         */
        int m_currentBlendEquationIdx = 0;

        /**
         * @brief Blending constant color factor
         */
        glm::vec4 m_blendingConstantColor = {0.0f, 0.0f, 0.0f, 1.0f};
    };
} // namespace Tests

#undef __TEST_BLENDING_PAIR_STR

#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>

namespace Tests
{
    class TestMVP: public Test
    {
    public:
        /**
         * @brief Construct a new TestMVP object
         */
        TestMVP();
        /**
         * @brief Destroy the TestMVP object
         */
        virtual ~TestMVP();

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
        VBO m_planeVbo;
        ;
        /**
         * @brief Element buffer object for the plane's indices
         */
        EBO m_planeEbo;
        /**
         * @brief Plane's vertex array object
         */
        VAO m_planeVao;

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
        VBO m_cubeVbo;
        /**
         * @brief Cube's vertex array object
         */
        VAO m_cubeVao;

        /**
         * @brief The vertex buffers' layout
         */
        VBLayout m_layout;
        /**
         * @brief Shader to display the shape\(s\)
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
         * @brief What scene to render
         */
        int m_mode;

        /**
         * @brief Transforms' descriptions for different scenes
         */
        struct TransformData
        {
            bool operator==(const TransformData&) const = default;
            bool operator!=(const TransformData&) const = default;

            /**
             * @brief The transform's model matrix
             */
            glm::mat4 model;
            /**
             * @brief The transform's model translation
             */
            glm::vec3 modelTranslation;
            /**
             * @brief The transform's model rotation's Euler's angles \(in degrees\)
             */
            glm::vec3 modelAngle;
            /**
             * @brief The transform's model scale
             */
            glm::vec3 modelScale;

            /**
             * @brief The transform's view matrix
             */
            glm::mat4 view;
            /**
             * @brief The transform's view translation
             */
            glm::vec3 viewTranslation;
            /**
             * @brief The transform's view rotation's Euler's angles \(in degrees\)
             *
             */
            glm::vec3 viewAngle;

            /**
             * @brief The transform's projection matrix
             */
            glm::mat4 proj;
            /**
             * @brief Is the projection orthographic or perspective
             */
            int projType;
            /**
             * @brief Whether the formula for calculating the orthographic projection matrix
             * should use the values for the near and far planes
             */
            bool projOrthoUseNearFarPlanes;
            /**
             * @brief Orthographic projection's frustum's left plane
             */
            float projOrthoFrustumLeft;
            /**
             * @brief Orthographic projection's frustum's right plane
             */
            float projOrthoFrustumRight;
            /**
             * @brief Orthographic projection's frustum's top plane
             */
            float projOrthoFrustumTop;
            /**
             * @brief Orthographic projection's frustum's bottom plane
             */
            float projOrthoFrustumBottom;
            /**
             * @brief Orthographic projection's frustum's near plane
             */
            float projOrthoFrustumNear;
            /**
             * @brief Orthographic projection's frustum's far plane
             */
            float projOrthoFrustumFar;
            /**
             * @brief Perspective projection's FOV angle on the Y axis \(in degrees\)
             */
            float projPerspFOV;
            /**
             * @brief Whether to use the current viewport's sides' ratio instead of the provided values'
             */
            bool projPerspUseViewportRatio;
            /**
             * @brief Perspective projection's width
             */
            float projPerspWidth;
            /**
             * @brief Perspective projection's height
             */
            float projPerspHeight;
            /**
             * @brief Perspective projection's frustum's near plane
             */
            float projPerspFrustumNear;
            /**
             * @brief Perspective projection's frustum's far plane
             */
            float projPerspFrustumFar;
        } m_transforms[3] = {
            {
             .modelTranslation = {0.0f, -0.5f, 0.0f},
             .modelAngle       = {-60.0f, 0.0f, 0.0f},
             .modelScale       = {1.0f, 1.0f, 1.0f},

             .viewTranslation = {0.0f, 0.0f, 3.0f},
             .viewAngle       = {0.0f, 0.0f, 0.0f},

             .projType                  = 1,
             .projOrthoUseNearFarPlanes = true,
             .projOrthoFrustumLeft      = -10.0f,
             .projOrthoFrustumRight     = 10.0f,
             .projOrthoFrustumTop       = 10.0f,
             .projOrthoFrustumBottom    = -10.0f,
             .projOrthoFrustumNear      = 0.01f,
             .projOrthoFrustumFar       = 100.0f,
             .projPerspFOV              = 45.0f,
             .projPerspUseViewportRatio = true,
             .projPerspFrustumNear      = 0.01f,
             .projPerspFrustumFar       = 100.f,
             },
            {
             .modelTranslation = {0.0f, 0.0f, 0.0f},
             .modelAngle       = {0.0f, 0.0f, 0.0f},
             .modelScale       = {1.0f, 1.0f, 1.0f},

             .viewTranslation = {0.0f, 0.0f, 3.0f},
             .viewAngle       = {0.0f, 0.0f, 0.0f},

             .projType                  = 1,
             .projOrthoUseNearFarPlanes = true,
             .projOrthoFrustumLeft      = -10.0f,
             .projOrthoFrustumRight     = 10.0f,
             .projOrthoFrustumTop       = 10.0f,
             .projOrthoFrustumBottom    = -10.0f,
             .projOrthoFrustumNear      = 0.01f,
             .projOrthoFrustumFar       = 100.0f,
             .projPerspFOV              = 45.0f,
             .projPerspUseViewportRatio = true,
             .projPerspFrustumNear      = 0.01f,
             .projPerspFrustumFar       = 100.f,
             },
            {
             .modelTranslation = {0.0f, 0.0f, 0.0f},
             .modelAngle       = {0.0f, 0.0f, 0.0f},
             .modelScale       = {1.0f, 1.0f, 1.0f},

             .viewTranslation = {0.0f, 0.0f, 3.0f},
             .viewAngle       = {0.0f, 0.0f, 0.0f},

             .projType                  = 1,
             .projOrthoUseNearFarPlanes = true,
             .projOrthoFrustumLeft      = -10.0f,
             .projOrthoFrustumRight     = 10.0f,
             .projOrthoFrustumTop       = 10.0f,
             .projOrthoFrustumBottom    = -10.0f,
             .projOrthoFrustumNear      = 0.01f,
             .projOrthoFrustumFar       = 100.0f,
             .projPerspFOV              = 45.0f,
             .projPerspUseViewportRatio = true,
             .projPerspFrustumNear      = 0.01f,
             .projPerspFrustumFar       = 100.f,
             },
        };

        /**
         * @brief Is the cubes scene in party mode
         */
        bool m_partyMode                          = false;
        /**
         * @brief Internal time \(in seconds\)
         */
        float m_timeMark                          = 0;
        /**
         * @brief Cubes' positions for the appropriate scene
         *
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

    private:
        /**
         * @brief Updates a transform's matrices based on its other values
         *
         * @param transformData the transform to be updated
         */
        void UpdateTransformData(TransformData& transformData);
        /**
         * @brief By how much to multiply the angles in party mode
         *
         * @return float
         */
        float PartyModeAngleCoefficient();
    };
} // namespace Tests

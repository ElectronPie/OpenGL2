#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <ranges>
#include <vector>

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
        static inline float s_planeVertices[20] = {
            // position             // texture coords
            +0.5f, +0.5f, 0.0f,     1.0f, 1.0f,     // top right
            +0.5f, -0.5f, 0.0f,     1.0f, 0.0f,     // bottom right
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     // bottom left
            -0.5f, +0.5f, 0.0f,     0.0f, 1.0f,     // top left
        };
        static inline unsigned int s_planeIndices[6] = {
            0, 1, 2,
            0, 2, 3,
        };
        // clang-format on
        VBO m_planeVbo;
        VBLayout m_planeLayout;
        EBO m_planeEbo;
        VAO m_planeVao;

        // clang-format off
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
        VBO m_cubeVbo;
        VBLayout m_cubeLayout;
        VAO m_cubeVao;

        ShaderProgram m_shaderProgram;
        Texture m_texture1;
        Texture m_texture2;
        Renderer& m_rendererInstance;

        int m_mode;

        struct TransformData
        {
            bool operator==(const TransformData&) const = default;
            bool operator!=(const TransformData&) const = default;

            glm::mat4 model;
            glm::vec3 modelTranslation;
            glm::vec3 modelAngle;
            glm::vec3 modelScale;

            glm::mat4 view;
            glm::vec3 viewTranslation;
            glm::vec3 viewAngle;

            glm::mat4 proj;
            int projType;
            bool projOrthoUseNearFarPlanes;
            float projOrthoFrustumLeft;
            float projOrthoFrustumRight;
            float projOrthoFrustumTop;
            float projOrthoFrustumBottom;
            float projOrthoFrustumNear;
            float projOrthoFrustumFar;
            float projPerspFOV;
            bool projPerspUseViewportRatio;
            float projPerspWidth;
            float projPerspHeight;
            float projPerspFrustumNear;
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

        bool m_partyMode                          = false;
        float m_timeMark                          = 0;
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
        void UpdateTransformData(TransformData& transformData);
        float PartyModeAngleCoefficient();
    };
} // namespace Tests

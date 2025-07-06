#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Material.hpp"
#include "Light.hpp"
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
            // positions            // normals              // texture coords
            -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     0.0f,  0.0f, 1.0f,     0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f
        };
        // clang-format on
        VBO m_vbo;
        VBLayout m_layout;
        VAO m_objectVAO;
        VAO m_lightVAO;
        ShaderProgram m_objectShaderProgram;
        ShaderProgram m_lightShaderProgram;

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
            {-1.3f, 1.0f,  -1.5f }
        };

        Material m_material;

        glm::vec3 m_backgroundColor = {0.0f, 0.0f, 0.0f};
        DirLight m_dirLight         = {
            {1.0f, 0.0f, 0.0f},
            {0.2f, 0.2f, 0.2f},
            {1.0f, 1.0f, 1.0f},
            {0.5f, 0.5f, 0.5f}
        };
        PointLight m_pointLights[4] = {
            {{0.7f, 0.2f, 2.0f},    {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f},
            {{2.3f, -3.3f, -4.0f},  {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f},
            {{-4.0f, 2.0f, -12.0f}, {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f},
            {{0.0f, 0.0f, -3.0f},   {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f}
        };
        SpotLight m_spotLight = {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {0.2f, 0.2f, 0.2f},
            {1.0f, 1.0f, 1.0f},
            {0.5f, 0.5f, 0.5f},
            glm::cos(glm::radians(12.5f)),
            glm::cos(glm::radians(17.5f)),
            1.0f,
            0.09f,
            0.032f
        };

        int m_currentPreset = 0;
        static inline const char* s_presetNames =
            "Original\0"
            "Desert\0"
            "Factory\0"
            "Horror\0"
            "Biochemical lab\0";

        static inline struct Preset
        {
            glm::vec3 backgroundColor;
            DirLight dirLight;
            PointLight pointLights[4];
            SpotLight spotLight;
        } s_presets[] = {
            // Original
            {{0.0f, 0.0f, 0.0f},
             {{1.0f, 0.0f, 0.0f}, {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}},
             {
                 {{0.7f, 0.2f, 2.0f}, {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f},
                 {{2.3f, -3.3f, -4.0f},
                  {0.2f, 0.2f, 0.2f},
                  {1.0f, 1.0f, 1.0f},
                  {0.5f, 0.5f, 0.5f},
                  1.0f,
                  0.09f,
                  0.032f},
                 {{-4.0f, 2.0f, -12.0f},
                  {0.2f, 0.2f, 0.2f},
                  {1.0f, 1.0f, 1.0f},
                  {0.5f, 0.5f, 0.5f},
                  1.0f,
                  0.09f,
                  0.032f},
                 {{0.0f, 0.0f, -3.0f}, {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f},
             }, {{0.0f, 0.0f, 0.0f},
              {1.0f, 0.0f, 0.0f},
              {0.2f, 0.2f, 0.2f},
              {1.0f, 1.0f, 1.0f},
              {0.5f, 0.5f, 0.5f},
              glm::cos(glm::radians(12.5f)),
              glm::cos(glm::radians(17.5f)),
              1.0f,
              0.09f,
              0.032f}},
            // Desert
            {{0.75f, 0.52f, 0.3f},
             {{-0.2f, -1.0f, -0.3f}, {0.3f, 0.24f, 0.14f}, {0.7f, 0.42f, 0.26f}, {0.5f, 0.5f, 0.5f}},
             {
                 {{0.7f, 0.2f, 2.0f}, {0.1f, 0.06f, 0.0f}, {1.0f, 0.6f, 0.0f}, {1.0f, 0.6f, 0.0f}, 1.0f, 0.09f, 0.032f},
                 {{2.3f, -3.3f, -4.0f},
                  {0.1f, 0.0f, 0.0f},
                  {1.0f, 0.0f, 0.0f},
                  {1.0f, 0.0f, 0.0f},
                  1.0f,
                  0.09f,
                  0.032f},
                 {{-4.0f, 2.0f, -12.0f},
                  {0.1f, 0.1f, 0.0f},
                  {1.0f, 1.0f, 0.0f},
                  {1.0f, 1.0f, 0.0f},
                  1.0f,
                  0.09f,
                  0.032f},
                 {{0.0f, 0.0f, -3.0f},
                  {0.02f, 0.02f, 0.1f},
                  {0.2f, 0.2f, 1.0f},
                  {0.2f, 0.2f, 1.0f},
                  1.0f,
                  0.09f,
                  0.032f},
             }, {{0.0f, 0.0f, 0.0f},
              {1.0f, 0.0f, 0.0f},
              {0.0f, 0.0f, 0.0f},
              {0.8f, 0.8f, 0.8f},
              {0.8f, 0.8f, 0.8f},
              glm::cos(glm::radians(12.5f)),
              glm::cos(glm::radians(13.0f)),
              1.0f,
              0.09f,
              0.032f}},
            // Factory
            {{0.1f, 0.1f, 0.1f},
             {{-0.2f, -1.0f, -0.3f}, {0.3f, 0.24f, 0.14f}, {0.7f, 0.42f, 0.26f}, {0.5f, 0.5f, 0.5f}},
             {
                 {{0.7f, 0.2f, 2.0f},
                  {0.02f, 0.02f, 0.06f},
                  {0.2f, 0.2f, 0.6f},
                  {0.2f, 0.2f, 0.6f},
                  1.0f,
                  0.09f,
                  0.032f},
                 {{2.3f, -3.3f, -4.0f},
                  {0.03f, 0.03f, 0.07f},
                  {0.3f, 0.3f, 0.7f},
                  {0.3f, 0.3f, 0.7f},
                  1.0f,
                  0.09f,
                  0.032f},
                 {{-4.0f, 2.0f, -12.0f},
                  {0.0f, 0.0f, 0.03f},
                  {0.0f, 0.0f, 0.3f},
                  {0.0f, 0.0f, 0.3f},
                  1.0f,
                  0.09f,
                  0.032f},
                 {{0.0f, 0.0f, -3.0f},
                  {0.04f, 0.04f, 0.04f},
                  {0.4f, 0.4f, 0.4f},
                  {0.4f, 0.4f, 0.4f},
                  1.0f,
                  0.09f,
                  0.032f},
             }, {{0.0f, 0.0f, 0.0f},
              {1.0f, 0.0f, 0.0f},
              {0.0f, 0.0f, 0.0f},
              {1.0f, 1.0f, 1.0f},
              {1.0f, 1.0f, 1.0f},
              glm::cos(glm::radians(10.0f)),
              glm::cos(glm::radians(12.5f)),
              1.0f,
              0.09f,
              0.032f}},
            // Horror
            {{0.0f, 0.0f, 0.0f},
             {{-0.2f, -1.0f, -0.3f}, {0.0f, 0.0f, 0.0f}, {0.05f, 0.05f, 0.05f}, {0.2f, 0.2f, 0.2f}},
             {
                 {{0.7f, 0.2f, 2.0f},
                  {0.01f, 0.01f, 0.01f},
                  {0.1f, 0.1f, 0.1f},
                  {0.1f, 0.1f, 0.1f},
                  1.0f,
                  0.14f,
                  0.07f},
                 {{2.3f, -3.3f, -4.0f},
                  {0.01f, 0.01f, 0.01f},
                  {0.1f, 0.1f, 0.1f},
                  {0.1f, 0.1f, 0.1f},
                  1.0f,
                  0.14f,
                  0.07f},
                 {{-4.0f, 2.0f, -12.0f},
                  {0.01f, 0.01f, 0.01f},
                  {0.1f, 0.1f, 0.1f},
                  {0.1f, 0.1f, 0.1f},
                  1.0f,
                  0.22f,
                  0.2f},
                 {{0.0f, 0.0f, -3.0f},
                  {0.03f, 0.01f, 0.01f},
                  {0.3f, 0.1f, 0.1f},
                  {0.3f, 0.1f, 0.1f},
                  1.0f,
                  0.14f,
                  0.07f},
             }, {{0.0f, 0.0f, 0.0f},
              {1.0f, 0.0f, 0.0f},
              {0.0f, 0.0f, 0.0f},
              {1.0f, 1.0f, 1.0f},
              {1.0f, 1.0f, 1.0f},
              glm::cos(glm::radians(10.0f)),
              glm::cos(glm::radians(12.5f)),
              1.0f,
              0.09f,
              0.032f}},
            // Biochemical lab
            {{0.9f, 0.9f, 0.9f},
             {{-0.2f, -1.0f, -0.3f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
             {
                 {{0.7f, 0.2f, 2.0f},
                  {0.04f, 0.07f, 0.01f},
                  {0.4f, 0.7f, 0.1f},
                  {0.4f, 0.7f, 0.1f},
                  1.0f,
                  0.07f,
                  0.017f},
                 {{2.3f, -3.3f, -4.0f},
                  {0.04f, 0.07f, 0.01f},
                  {0.4f, 0.7f, 0.1f},
                  {0.4f, 0.7f, 0.1f},
                  1.0f,
                  0.07f,
                  0.017f},
                 {{-4.0f, 2.0f, -12.0f},
                  {0.04f, 0.07f, 0.01f},
                  {0.4f, 0.7f, 0.1f},
                  {0.4f, 0.7f, 0.1f},
                  1.0f,
                  0.07f,
                  0.017f},
                 {{0.0f, 0.0f, -3.0f},
                  {0.04f, 0.07f, 0.01f},
                  {0.4f, 0.7f, 0.1f},
                  {0.4f, 0.7f, 0.1f},
                  1.0f,
                  0.07f,
                  0.017f},
             }, {{0.0f, 0.0f, 0.0f},
              {1.0f, 0.0f, 0.0f},
              {0.0f, 0.0f, 0.0f},
              {0.0f, 1.0f, 0.0f},
              {0.0f, 1.0f, 0.0f},
              glm::cos(glm::radians(7.0f)),
              glm::cos(glm::radians(10.0f)),
              1.0f,
              0.07f,
              0.17f} }
        };

        void ApplyPreset(const Preset& preset);

        Camera m_camera;
        glm::vec2 m_cursorPos;
        bool m_mouseButtonPressed = false;
    };
} // namespace Tests

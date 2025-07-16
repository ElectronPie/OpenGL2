#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
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
        /**
         * @brief Vertices of a cube
         */
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
        /**
         * @brief OpenGL vertex buffer object for the cube
         */
        VBO m_vbo;
        /**
         * @brief Vertex buffer layout for the cube
         */
        VBLayout m_layout;
        /**
         * @brief OpenGL vertex array object for the objects
         */
        VAO m_objectVAO;
        /**
         * @brief OpenGL vertex array object for the point lights
         */
        VAO m_lightVAO;
        /**
         * @brief Shader program for the objects
         */
        ShaderProgram m_objectShaderProgram;
        /**
         * @brief Shader program for the point lights
         */
        ShaderProgram m_lightShaderProgram;

        /**
         * @brief positions of the cubes in the scene
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
            {-1.3f, 1.0f,  -1.5f }
        };

        // Material properties of the objects
        Texture m_diffuseMap;  ///< Diffuse texture for the objects
        Texture m_specularMap; ///< Specular texture for the objects
        //Texture m_emissionMap;      ///< Emission texture for the objects
        float m_shininess = 32.0f; ///< Shininess factor for the objects

        // Lighting properties
        /**
         * @brief Background color of the scene
         */
        glm::vec3 m_backgroundColor = {0.0f, 0.0f, 0.0f};
        /**
         * @brief Directional light
         */
        DirLight m_dirLight         = {
            {1.0f, 0.0f, 0.0f},
            {0.2f, 0.2f, 0.2f},
            {1.0f, 1.0f, 1.0f},
            {0.5f, 0.5f, 0.5f}
        };
        /**
         * @brief Point lights in the scene
         */
        PointLight m_pointLights[4] = {
            {{0.7f, 0.2f, 2.0f},    {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f},
            {{2.3f, -3.3f, -4.0f},  {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f},
            {{-4.0f, 2.0f, -12.0f}, {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f},
            {{0.0f, 0.0f, -3.0f},   {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, 1.0f, 0.09f, 0.032f}
        };
        /**
         * @brief Spotlight in the scene (always in place of the camera, pointing in the same direction)
         */
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

        // ImGui ComboBox for selecting the lighting preset
        /**
         * @brief Current lighting preset index
         */
        int m_currentPreset = 0;
        /**
         * @brief Names of the lighting presets
         */
        static inline const char* s_presetNames =
            "Original\0"
            "Desert\0"
            "Factory\0"
            "Horror\0"
            "Biochemical lab\0";

        /**
         * @brief Lighting presets
         */
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

        /**
         * @brief Apply the selected lighting preset
         *
         * @param preset The preset to apply
         */
        void ApplyPreset(const Preset& preset);

        // Camera and input handling
        /**
         * @brief Camera for the scene
         */
        Camera m_camera;
        /**
         * @brief Mouse cursor position
         */
        glm::vec2 m_cursorPos;
        /**
         * @brief Mouse button pressed state
         */
        bool m_mouseButtonPressed = false;
    };
} // namespace Tests

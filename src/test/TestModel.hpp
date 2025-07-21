#pragma once

#include "Test.hpp"

#include "Model.hpp"
#include "ShaderProgram.hpp"
#include "Light.hpp"
#include "Camera.hpp"

#include <glm/glm.hpp>

namespace Tests
{
    /**
     * @brief Model test
     */
    class TestModel: public Test
    {
    public:
        /**
         * @brief Construct a new Test Model object
         */
        TestModel();
        /**
         * @brief Destroy the Test Model object
         */
        virtual ~TestModel();

        /**
         * @copydoc Tests::Test::OnRender
         */
        void OnRender() override;
        /**
         * @copydoc Tests::Test::OnUpdate
         */
        void OnUpdate(float deltaTime) override;

    private:
        /**
         * @brief The model to be loaded and displayed
         */
        Model m_model;
        /**
         * @brief The shader program to draw the model with
         */
        ShaderProgram m_shaderProgram;

        /**
         * @brief Camera for the scene
         */
        Camera m_camera;

        DirLight m_dirLight = {
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
    };
} //namespace Tests

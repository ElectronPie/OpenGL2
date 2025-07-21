#include "TestModel.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

namespace Tests
{
    TestModel::TestModel():
        m_model{
            "assets/models/robot/Model.obj", false
    },
        m_shaderProgram{"assets/shaders/TestModel/TestModel.vert.glsl", "assets/shaders/TestModel/TestModel.frag.glsl"},
        m_camera{{0.0f, 0.0f, 3.0f}}
    {
        Renderer& r = Renderer::GetInstance();
        r.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Setup shader uniforms
        m_shaderProgram.SetUniform1("u_material.shininess", 32.0f);

        m_shaderProgram.SetUniform3("u_dirLight.direction", m_dirLight.direction);
        m_shaderProgram.SetUniform3("u_dirLight.ambient", m_dirLight.ambient);
        m_shaderProgram.SetUniform3("u_dirLight.diffuse", m_dirLight.diffuse);
        m_shaderProgram.SetUniform3("u_dirLight.specular", m_dirLight.specular);

        for(unsigned int i = 0; i < sizeof(m_pointLights) / sizeof(m_pointLights[0]); ++i)
        {
            m_shaderProgram.SetUniform3("u_pointLights[" + std::to_string(i) + "].position", m_pointLights[i].position);
            m_shaderProgram.SetUniform3("u_pointLights[" + std::to_string(i) + "].ambient", m_pointLights[i].ambient);
            m_shaderProgram.SetUniform3("u_pointLights[" + std::to_string(i) + "].diffuse", m_pointLights[i].diffuse);
            m_shaderProgram.SetUniform3("u_pointLights[" + std::to_string(i) + "].specular", m_pointLights[i].specular);
            m_shaderProgram.SetUniform1("u_pointLights[" + std::to_string(i) + "].attConst", m_pointLights[i].attConst);
            m_shaderProgram.SetUniform1(
                "u_pointLights[" + std::to_string(i) + "].attLinear", m_pointLights[i].attLinear
            );
            m_shaderProgram.SetUniform1(
                "u_pointLights[" + std::to_string(i) + "].attQuadratic", m_pointLights[i].attQuadratic
            );
        }

        // Initialize camera
        m_camera.InitForGLFW();
    }

    TestModel::~TestModel()
    {}

    void TestModel::OnRender()
    {
        m_shaderProgram.SetUniformMat4("u_model", glm::mat4{1.0f});
        m_shaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_shaderProgram.SetUniformMat4("u_proj", m_camera.proj);
        m_shaderProgram.SetUniformMat3("u_normal", glm::transpose(glm::inverse(glm::mat3{m_camera.view})));

        m_model.Draw(m_shaderProgram);
    }

    void TestModel::OnUpdate(float deltaTime)
    {
        m_camera.OnUpdate(deltaTime);
    }
} //namespace Tests

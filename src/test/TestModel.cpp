#include "TestModel.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

static Camera* s_camera;
static GLFWscrollfun s_oldCallback;

static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    s_camera->ProcessMouseScroll(yOffset);
    s_oldCallback(window, xOffset, yOffset);
}

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

        // Setup GLFW callback for camera zoom
        s_camera      = &m_camera;
        s_oldCallback = glfwSetScrollCallback(r.GetWindow(), ScrollCallback);
    }

    TestModel::~TestModel()
    {
        // Reset GLFW scroll callback
        glfwSetScrollCallback(Renderer::GetInstance().GetWindow(), s_oldCallback);
    }

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
        Renderer& r = Renderer::GetInstance();

        // Keyboard input
        GLFWwindow* window = r.GetWindow();
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Forward, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Backward, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Left, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Right, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Down, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Up, deltaTime);

        // Mouse movement
        double cursorX, cursorY;
        glfwGetCursorPos(window, &cursorX, &cursorY);
        float deltaX = cursorX - m_cursorPos.x;
        float deltaY = m_cursorPos.y - cursorY; // Reversed since y-coordinates range from bottom to top
        m_cursorPos  = {cursorX, cursorY};
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
        {
            if(!m_mouseButtonPressed)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                m_mouseButtonPressed = true;
            }
            m_camera.ProcessMouseMovement(deltaX, deltaY);
        }
        else if(m_mouseButtonPressed)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            m_mouseButtonPressed = false;
        }

        // Update camera projection dimensions
        auto [width, height] = r.GetViewportSize();
        m_camera.width       = width;
        m_camera.height      = height;
        m_camera.UpdateProj();
    }
} //namespace Tests

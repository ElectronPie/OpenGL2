#include "TestLighting.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

#include "Renderer.hpp"

static Camera* s_camera;
static GLFWscrollfun s_oldCallback;

static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    s_camera->ProcessMouseScroll(yOffset);
    s_oldCallback(window, xOffset, yOffset);
}

namespace Tests
{
    TestLighting::TestLighting():
        m_vbo{s_vertices, sizeof(s_vertices)/sizeof(s_vertices[0])},
        m_phongShaderProgram{
            "assets/shaders/TestLighting/Phong.vert.glsl",
            "assets/shaders/TestLighting/Phong.frag.glsl"
        },
        m_lightShaderProgram{
            "assets/shaders/TestLighting/Light.vert.glsl",
            "assets/shaders/TestLighting/Light.frag.glsl"
        },
        m_camera{{0.0f, 0.0f, 3.0f}}
    {
        Renderer& r = Renderer::GetInstance();

        // Setup vertex buffer layout
        m_layout.Push<float>(3);
        m_layout.Push<float>(3);

        // Setup object VAO
        m_objectVAO.AttachVBO(m_vbo, m_layout);

        // Setup light VAO
        m_lightVAO.AttachVBO(m_vbo, m_layout);

        r.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Setup GLFW callback for camera zoom
        s_camera      = &m_camera;
        s_oldCallback = glfwSetScrollCallback(r.GetWindow(), ScrollCallback);
    }

    TestLighting::~TestLighting()
    {
        // Reset GLFW scroll callback
        glfwSetScrollCallback(Renderer::GetInstance().GetWindow(), s_oldCallback);
    }

    void TestLighting::OnRender()
    {
        Renderer& r = Renderer::GetInstance();

        m_phongShaderProgram.SetUniform3("u_objectColor", m_objectColor);
        m_phongShaderProgram.SetUniform3("u_lightColor", m_lightColor);
        m_phongShaderProgram.SetUniform3("u_lightPos", glm::vec3{m_camera.view * glm::vec4{m_lightPos, 1.0f}});

        m_phongShaderProgram.SetUniformMat4("u_model", glm::mat4{1.0f});
        m_phongShaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_phongShaderProgram.SetUniformMat4("u_proj", m_camera.proj);
        m_phongShaderProgram.SetUniformMat3("u_normal", glm::transpose(glm::inverse(glm::mat3{m_camera.view})));

        m_phongShaderProgram.SetUniform1("u_ambientStrength", m_ambientStrength);
        m_phongShaderProgram.SetUniform1("u_diffuseStrength", m_diffuseStrength);
        m_phongShaderProgram.SetUniform1("u_specularStrength", m_specularStrength);
        m_phongShaderProgram.SetUniform1("u_shininess", m_shininess);

        m_lightShaderProgram.SetUniform3("u_lightColor", m_lightColor);

        glm::mat4 model{1.0f};
        model = glm::translate(model, m_lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        m_lightShaderProgram.SetUniformMat4("u_model", model);
        m_lightShaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_lightShaderProgram.SetUniformMat4("u_proj", m_camera.proj);

        r.DrawVertices(m_objectVAO, m_phongShaderProgram);
        r.DrawVertices(m_lightVAO, m_lightShaderProgram);
    }

    void TestLighting::OnImGuiRender()
    {
        ImGui::ColorEdit3("Object color", &m_objectColor[0]);
        ImGui::ColorEdit3("Light color", &m_lightColor[0]);
        ImGui::SliderFloat3("Light position", &m_lightPos[0], -5.0f, 5.0f);
        ImGui::SliderFloat("Ambient strength", &m_ambientStrength, 0.0f, 1.0f);
        ImGui::SliderFloat("Diffuse strength", &m_diffuseStrength, 0.0f, 1.0f);
        ImGui::SliderFloat("Specular strength", &m_specularStrength, 0.0f, 1.0f);
        ImGui::InputFloat("Shininess", &m_shininess);
    }

    void TestLighting::OnUpdate(float deltaTime)
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
} // namespace Tests

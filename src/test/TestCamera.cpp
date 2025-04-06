#include "TestCamera.hpp"

#include "GLFW/glfw3.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

static Camera* camera;
static GLFWscrollfun oldCallback;

static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera->ProcessMouseScroll(yOffset);
    oldCallback(window, xOffset, yOffset);
}

namespace Tests
{
    TestCamera::TestCamera():
        m_vbo{
            s_vertices, sizeof(s_vertices) / sizeof(s_vertices[0])
    },
        m_shaderProgram{"assets/shaders/TestCamera.vert.glsl", "assets/shaders/TestCamera.frag.glsl"},
        m_texture1{"assets/textures/container.jpg"}, m_texture2{"assets/textures/awesomeface.png"},
        m_rendererInstance{Renderer::GetInstance()}, m_camera{{0.0f, 0.0f, 3.0f}}
    {
        // Setup vertex buffer layout
        m_layout.Push<float>(3); // position
        m_layout.Push<float>(2); // texture coords

        // Setup VAO
        m_vao.AttachVBO(m_vbo, m_layout);

        // Bind textures to samplers
        m_texture1.Bind(0);
        m_texture2.Bind(1);
        m_shaderProgram.SetUniform1("u_texture1", 0);
        m_shaderProgram.SetUniform1("u_texture2", 1);

        camera      = &m_camera;
        oldCallback = glfwSetScrollCallback(m_rendererInstance.GetWindow(), ScrollCallback);
    }

    TestCamera::~TestCamera()
    {
        glfwSetScrollCallback(m_rendererInstance.GetWindow(), oldCallback);
    }

    void TestCamera::OnRender()
    {
        m_shaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_shaderProgram.SetUniformMat4("u_proj", m_camera.proj);
        for(unsigned int i = 0; i < 10; ++i)
        {
            glm::mat4 model{1.0f};
            model       = glm::translate(model, s_cubePositions[i]);
            float angle = 20.0f * i;
            model       = glm::rotate(model, glm::radians(angle), glm::vec3{1.0f, 0.3f, 0.5f});
            m_shaderProgram.SetUniformMat4("u_model", model);
            m_rendererInstance.DrawVertices(m_vao, m_shaderProgram);
        }
    }

    void TestCamera::OnImGuiRender()
    {
        ImGui::Text("Camera mode");
        ImGui::RadioButton("Circle", &m_cameraMode, 0);
        ImGui::RadioButton("Free movement", &m_cameraMode, 1);

        switch(m_cameraMode)
        {
        case 0:
            ImGui::InputFloat("Radius", &m_circleRadius);
            break;
        case 1:
            ImGui::InputFloat("Camera speed", &m_camera.movementSpeed);
            ImGui::InputFloat("Mouse sensitivity", &m_camera.mouseSensitivity);
            break;
        }
        ImGui::Text("%.3f", m_camera.zoom);
        ImGui::SameLine();
        ImGui::Text("Zoom");
    }

    void TestCamera::OnUpdate(float deltaTime)
    {
        switch(m_cameraMode)
        {
        case 0: {
            m_timeMark += deltaTime;
            float camX = glm::sin(m_timeMark) * m_circleRadius;
            float camZ = glm::cos(m_timeMark) * m_circleRadius;

            m_camera.position = {camX, 0.0f, camZ};
            m_camera.LookAt({0.0f, 0.0f, 0.0f});
            break;
        }
        case 1: {
            // Keyboard input
            GLFWwindow* window = m_rendererInstance.GetWindow();
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

            break;
        }
        }

        // Update camera projection dimensions
        auto [width, height] = m_rendererInstance.GetViewportSize();
        m_camera.width       = width;
        m_camera.height      = height;
        m_camera.UpdateProj();
    }
} // namespace Tests

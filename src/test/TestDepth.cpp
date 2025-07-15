#include "TestDepth.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

static Camera* s_camera;
static GLFWscrollfun s_oldCallback;

static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    s_camera->ProcessMouseScroll(yOffset);
    s_oldCallback(window, xOffset, yOffset);
}

namespace Tests
{
    TestDepth::TestDepth():
        m_planeVBO{
            s_planeVertices, sizeof(s_planeVertices) / sizeof(s_planeVertices[0])
    },
        m_planeEBO{s_planeIndices, sizeof(s_planeIndices) / sizeof(s_planeIndices[0])},
        m_planeTexture{"assets/textures/metal.jpg"},
        m_cubeVBO{s_cubeVertices, sizeof(s_cubeVertices) / sizeof(s_cubeVertices[0])},
        m_cubeTexture{"assets/textures/grey_marble.jpg"},
        m_shaderProgram{"assets/shaders/TestDepth/TestDepth.vert.glsl", "assets/shaders/TestDepth/TestDepth.frag.glsl"},
        m_camera{{0.0f, 1.0f, 3.0f}}
    {
        Renderer& r = Renderer::GetInstance();
        r.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Setup plane vertex buffer layout
        m_planeLayout.Push<float>(3); // position
        m_planeLayout.Push<float>(2); // texture coords

        // Setup plane VAO
        m_planeVAO.AttachVBO(m_planeVBO, m_planeLayout);
        m_planeVAO.AttachEBO(m_planeEBO);

        // Setup cube vertex buffer layout
        m_cubeLayout.Push<float>(3); // position
        m_cubeLayout.Push<float>(2); // texture coords

        // Setup cube VAO
        m_cubeVAO.AttachVBO(m_cubeVBO, m_cubeLayout);

        // Setup shader uniforms
        m_shaderProgram.SetUniform1("u_texture", 0);
        m_shaderProgram.SetUniform1("u_displayDepthBuffer", false);

        // Setup GLFW callback for camera zoom
        s_camera      = &m_camera;
        s_oldCallback = glfwSetScrollCallback(r.GetWindow(), ScrollCallback);
    }

    TestDepth::~TestDepth()
    {
        // Reset GLFW scroll callback
        glfwSetScrollCallback(Renderer::GetInstance().GetWindow(), s_oldCallback);
    }

    void TestDepth::OnRender()
    {
        Renderer& r = Renderer::GetInstance();

        m_shaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_shaderProgram.SetUniformMat4("u_proj", m_camera.proj);
        m_shaderProgram.SetUniform1("u_near", m_camera.near);
        m_shaderProgram.SetUniform1("u_far", m_camera.far);

        // Render plane
        m_planeTexture.Bind();
        m_shaderProgram.SetUniformMat4(
            "u_model",
            glm::rotate(glm::scale(glm::mat4{1.0f}, glm::vec3{4.0f}), glm::radians(-90.0f), glm::vec3{1.0f, 0.0f, 0.0f})
        );
        r.DrawElements(m_planeVAO, m_shaderProgram);

        // Render cubes
        m_cubeTexture.Bind();
        for(const glm::vec3& position : s_cubePositions)
        {
            glm::mat4 model = glm::translate(glm::mat4{1.0f}, position);
            m_shaderProgram.SetUniformMat4("u_model", model);
            r.DrawVertices(m_cubeVAO, m_shaderProgram);
        }
    }

    void TestDepth::OnImGuiRender()
    {
        if(ImGui::Checkbox("Display depth buffer", &m_displayDepthBuffer))
        {
            m_shaderProgram.SetUniform1("u_displayDepthBuffer", m_displayDepthBuffer);
        }
        if(ImGui::Combo(
               "Depth test function",
               &m_currentDepthFuncIndex,
               [](void* user_data, int idx) -> const char* { return s_depthFuncs[idx].second; },
               nullptr,
               s_depthFuncsCount
           ))
        {
            glDepthFunc(s_depthFuncs[m_currentDepthFuncIndex].first);
        }
    }

    void TestDepth::OnUpdate(float deltaTime)
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

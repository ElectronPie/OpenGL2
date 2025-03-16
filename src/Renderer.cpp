#include "Renderer.hpp"

#include <GLFW/glfw3.h>

#include "GLFWRAII.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"

#include <iostream>
#include <memory>

std::shared_ptr<GLFWRAII> Renderer::s_g;

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

Renderer::Renderer()
{
    if(s_g.get() == nullptr)
    {
        s_g = std::make_shared<GLFWRAII>();
    }

    // OpenGL version 4.3, no legacy functions support
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Create a window
    m_window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
    if(!m_window)
    {
        std::cout << "Failed to create a GLFW window!" << std::endl;
        return;
    }

    // Make the window context current
    glfwMakeContextCurrent(m_window);

    // Force V-Sync so that the CPU/GPU usage doesn't skyrocket
    glfwSwapInterval(1);

    // Load OpenGL with GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Can't load GLAD!" << std::endl;
        return;
    }

    // Output OpenGL version
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Set the viewport size and framebuffer size callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

    // Set key callback
    glfwSetKeyCallback(m_window, KeyCallback);

    m_initialized = true;
}

Renderer::~Renderer()
{
    glfwDestroyWindow(m_window);
}

void Renderer::Draw(const VAO& vao, const ShaderProgram& shaderProgram) noexcept
{
    shaderProgram.Bind();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, vao.GetElementsCount(), vao.GetElementsDataType(), NULL);
}

void Renderer::Clear() noexcept
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::ClearColor(float r, float g, float b, float a) noexcept
{
    glClearColor(r, g, b, a);
}

bool Renderer::ShouldClose() const noexcept
{
    return glfwWindowShouldClose(m_window);
}

void Renderer::FinishFrame() noexcept
{
    // Swap front and back buffers
    glfwSwapBuffers(m_window);

    // Poll and process events
    glfwPollEvents();
}

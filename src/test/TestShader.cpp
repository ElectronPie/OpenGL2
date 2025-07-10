#include "TestShader.hpp"

#include "Renderer.hpp"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_stdlib.h>

namespace Tests
{
    TestShader::TestShader():
        m_vbo{s_vertices, sizeof(s_vertices) / sizeof(s_vertices[0])},
        m_ebo{s_indices, sizeof(s_indices) / sizeof(s_indices[0])},
        m_shaderProgram{"assets/shaders/TestShader/TestShader.vert.glsl", m_fragmentShaderPath}
    {
        // Setup vertex buffer layout
        m_layout.Push<float>(3); // position

        // Setup VAO
        m_vao.AttachVBO(m_vbo, m_layout);
        m_vao.AttachEBO(m_ebo);

        // Setup shader uniforms
        m_shaderProgram.SetUniform4("u_rectangle", m_rectangle);
    }

    TestShader::~TestShader()
    {}

    void TestShader::OnRender()
    {
        Renderer::GetInstance().DrawElements(m_vao, m_shaderProgram);
    }

    void TestShader::OnImGuiRender()
    {
        ImGui::InputText("Shader path", &m_fragmentShaderPath);
        if(ImGui::Button("Reload"))
        {
            m_shaderProgram = ShaderProgram{"assets/shaders/TestShader/TestShader.vert.glsl", m_fragmentShaderPath};
            m_time          = 0.0f;
        }

        if(ImGui::SliderFloat4("Rectangle", &m_rectangle[0], 0.0f, 1.0f))
        {
            m_shaderProgram.SetUniform4("u_rectangle", m_rectangle);
        }
    }

    void TestShader::OnUpdate(float deltaTime)
    {
        Renderer& r = Renderer::GetInstance();

        // Update time
        m_time += deltaTime;
        m_shaderProgram.SetUniform1("u_time", m_time);

        // Update resolution
        auto [resolutionX, resolutionY] = r.GetViewportSize();
        m_resolution                    = {resolutionX, resolutionY};
        m_shaderProgram.SetUniform2("u_resolution", m_resolution);

        // Update mouse
        double cursorX, cursorY;
        glfwGetCursorPos(r.GetWindow(), &cursorX, &cursorY);
        m_mouse = {cursorX, resolutionY - cursorY};
        m_shaderProgram.SetUniform2("u_mouse", m_mouse);
    }
} // namespace Tests

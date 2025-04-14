#include "TestShader.hpp"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_stdlib.h>

namespace Tests
{
    TestShader::TestShader():
        m_vbo{s_vertices, sizeof(s_vertices) / sizeof(s_vertices[0])},
        m_ebo{s_indices, sizeof(s_indices) / sizeof(s_indices[0])},
        m_shaderProgram{std::make_unique<ShaderProgram>("assets/shaders/TestShader.vert.glsl", m_fragmentShaderPath)},
        m_rendererInstance{Renderer::GetInstance()}
    {
        // Setup vertex buffer layout
        m_layout.Push<float>(3); // position

        // Setup VAO
        m_vao.AttachVBO(m_vbo, m_layout);
        m_vao.AttachEBO(m_ebo);
    }

    TestShader::~TestShader()
    {}

    void TestShader::OnRender()
    {
        m_rendererInstance.DrawElements(m_vao, *m_shaderProgram);
    }

    void TestShader::OnImGuiRender()
    {
        ImGui::InputText("Shader path", &m_fragmentShaderPath);
        if(ImGui::Button("Reload"))
        {
            m_shaderProgram =
                std::make_unique<ShaderProgram>("assets/shaders/TestShader.vert.glsl", m_fragmentShaderPath);
        }
    }

    void TestShader::OnUpdate(float deltaTime)
    {
        // Update time
        m_time += deltaTime;
        m_shaderProgram->SetUniform1("u_time", m_time);

        // Update resolution
        auto [resolutionX, resolutionY] = m_rendererInstance.GetViewportSize();
        m_resolution                    = {resolutionX, resolutionY};
        m_shaderProgram->SetUniform2("u_resolution", m_resolution);

        // Update mouse
        double cursorX, cursorY;
        glfwGetCursorPos(m_rendererInstance.GetWindow(), &cursorX, &cursorY);
        m_mouse = {cursorX, resolutionY - cursorY};
        m_shaderProgram->SetUniform2("u_mouse", m_mouse);
    }
} // namespace Tests

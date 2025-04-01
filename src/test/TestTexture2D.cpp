#include "TestTexture2D.hpp"

#include <glm/glm.hpp>
#include <imgui.h>

namespace Tests
{
    TestTexture2D::TestTexture2D():
        m_vbo{s_vertices, sizeof(s_vertices)}, m_ebo{s_indices, sizeof(s_indices) / sizeof(s_indices[0])},
        m_shaderProgram{"assets/shaders/TestTexture2D.vert.glsl", "assets/shaders/TestTexture2D.frag.glsl"},
        m_texture1{"assets/textures/container.jpg"}, m_texture2{"assets/textures/awesomeface.png"},
        m_rendererInstance{Renderer::GetInstance()}
    {
        // Setup vertex buffer layout
        m_layout.Push<float>(3); // position
        m_layout.Push<float>(3); // color
        m_layout.Push<float>(2); // texture coords

        // Setup VAO
        m_vao.AttachVBO(m_vbo, m_layout);
        m_vao.AttachEBO(m_ebo);

        // Bind textures to samplers
        m_texture1.Bind(0);
        m_texture2.Bind(1);
        m_shaderProgram.SetUniform1("u_texture1", 0);
        m_shaderProgram.SetUniform1("u_texture2", 1);
    }

    TestTexture2D::~TestTexture2D()
    {}

    void TestTexture2D::OnRender()
    {
        // Bind textures to samplers
        m_texture1.Bind(0);
        m_texture2.Bind(1);
        m_shaderProgram.SetUniform1("u_texture1", 0);
        m_shaderProgram.SetUniform1("u_texture2", 1);

        m_shaderProgram.SetUniform1("u_mixCoefficient", m_mixCoefficient);
        m_rendererInstance.Draw(m_vao, m_shaderProgram);
    }

    void TestTexture2D::OnImGuiRender()
    {
        ImGui::Checkbox("Adjust the mix coefficient manually", &m_checkbox);
        if(!m_checkbox)
        {
            ImGui::BeginDisabled();
        }
        ImGui::DragFloat(
            "Mix coefficient",
            &m_mixCoefficient,
            0.001f,
            0.0f,
            1.0f,
            "%.5f",
            ImGuiSliderFlags_AlwaysClamp | (!m_checkbox ? ImGuiSliderFlags_NoInput : ImGuiSliderFlags_None)
        );
        if(!m_checkbox)
        {
            ImGui::EndDisabled();
        }
    }

    void TestTexture2D::OnUpdate(float deltaTime)
    {
        if(!m_checkbox)
        {
            m_mixCoefficient = glm::mod(m_mixCoefficient + deltaTime, 1.0f);
        }
    }
} // namespace Tests

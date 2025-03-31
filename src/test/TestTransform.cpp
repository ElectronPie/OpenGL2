#include "TestTransform.hpp"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <numeric>
#include <sstream>

namespace Tests
{
    TestTransform::TestTransform():
        m_vbo{s_vertices, sizeof(s_vertices)}, m_ebo{s_indices, sizeof(s_indices) / sizeof(s_indices[0])},
        m_shaderProgram{"assets/shaders/TestTransform.vert.glsl", "assets/shaders/TestTransform.frag.glsl"},
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

    TestTransform::~TestTransform()
    {}

    void TestTransform::OnRender()
    {
        m_shaderProgram.SetUniformMat4("u_transform", m_transform);

        m_rendererInstance.Draw(m_vao, m_shaderProgram);
    }

    void TestTransform::OnImGuiRender()
    {
        if(ImGui::BeginTable("Transform", 4))
        {
            size_t counter = 0;
            for(std::size_t i = 0; i < 16; ++i)
            {
                std::stringstream ss;
                ss << "##" << ++counter;
                ImGui::TableNextColumn();
                ImGui::InputFloat(ss.str().c_str(), &m_transform[i % 4][i / 4]);
            }
            ImGui::EndTable();
        }

        ImGui::InputFloat3("Translation", &m_translation[0]);
        if(ImGui::Button("Translate"))
        {
            m_transform = glm::translate(m_transform, m_translation);
        }

        ImGui::SliderFloat("Rotation", &m_rotation, 0.0f, 360.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
        if(ImGui::Button("Rotate"))
        {
            m_transform = glm::rotate(m_transform, glm::radians(m_rotation), glm::vec3{0.0f, 0.0f, 1.0f});
        }

        ImGui::InputFloat3("Scale", &m_scale[0]);
        if(ImGui::Button("Scale##2"))
        {
            m_transform = glm::scale(m_transform, m_translation);
        }
    }

    void TestTransform::OnUpdate(float deltaTime)
    {}
} // namespace Tests

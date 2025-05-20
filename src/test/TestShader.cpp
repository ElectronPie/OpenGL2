#include "TestShader.hpp"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_stdlib.h>

namespace Tests
{
    TestShader::TestShader():
        m_vbo{s_vertices, sizeof(s_vertices) / sizeof(s_vertices[0])},
        m_ebo{s_indices, sizeof(s_indices) / sizeof(s_indices[0])},
        m_shaderProgram{"assets/shaders/TestShader/TestShader.vert.glsl", m_fragmentShaderPath},
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
        m_rendererInstance.DrawElements(m_vao, m_shaderProgram);
    }

    void TestShader::OnImGuiRender()
    {
        ImGui::InputText("Shader path", &m_fragmentShaderPath);
        if(ImGui::Button("Reload"))
        {
            m_shaderProgram = ShaderProgram{"assets/shaders/TestShader/TestShader.vert.glsl", m_fragmentShaderPath};
            m_time          = 0.0f;
        }

        if(ImGui::Combo("Shader function", &m_functionID, s_functions))
        {
            m_shaderProgram.SetUniform1("u_functionID", m_functionID);
        }
        switch(m_functionID)
        {
        case 1:     // Blinn - Wyvil cosine approximation
            ImGui::InputFloat("Zoom", &m_zoom);
            m_shaderProgram.SetUniform1("u_zoom", m_zoom);
            break;
        case 2:     // Double cubic seat
        case 6:     // Quadratic through a given point
        case 15:    // Double elliptic seat
        case 16:    // Double elliptic sigmoid
        case 18:    // Circular arc through a given point
        case 19:    // Quadratic Bezier
        case 34:    // Power curve
        case 36:    // Cubic pulse
            ImGui::SliderFloat2("Point", &m_p1[0], 0.0f, 1.0f);
            m_shaderProgram.SetUniform2("u_p1", m_p1);
            break;
        case 3:     // Double cubic seat with linear blend
            ImGui::SliderFloat("Point", &m_point, 0.0f, 1.0f);
            ImGui::SliderFloat("Inflection", &m_inflection, 0.0f, 1.0f);
            m_shaderProgram.SetUniform1("u_point", m_point);
            m_shaderProgram.SetUniform1("u_inflection", m_inflection);
            break;
        case 4:     // Double odd polynomial seat
            ImGui::SliderFloat2("Point", &m_p1[0], 0.0f, 1.0f);
            ImGui::InputInt("Exponent", &m_exponent);
            m_shaderProgram.SetUniform2("u_p1", m_p1);
            m_shaderProgram.SetUniform1("u_exponent", m_exponent);
            break;
        case 5:     // Double polynomial sigmoid
        case 38:    // Exponential step
            ImGui::InputInt("Exponent", &m_exponent);
            m_shaderProgram.SetUniform1("u_exponent", m_exponent);
            break;
        case 7:     // Exponential easing
        case 8:     // Double exponential seat
        case 9:     // Double exponential sigmoid
        case 10:    // Exponential sigmoid
        case 32:    // Gain
        case 33:    // Parabola
        case 35:    // Tone
        case 37:    // Rational bump
            ImGui::SliderFloat("Inflection", &m_inflection, 0.0f, 1.0f);
            m_shaderProgram.SetUniform1("u_inflection", m_inflection);
            break;
        case 13:    // Double circle seat
        case 14:    // Double circle sigmoid
            ImGui::SliderFloat("Point", &m_point, 0.0f, 1.0f);
            m_shaderProgram.SetUniform1("u_point", m_point);
            break;
        case 17:    // Two lines joined with a circular arc fillet
            ImGui::SliderFloat2("Point", &m_p1[0], 0.0f, 1.0f);
            ImGui::SliderFloat("Radius", &m_radius, 0.0f, 1.0f);
            m_shaderProgram.SetUniform2("u_p1", m_p1);
            m_shaderProgram.SetUniform1("u_radius", m_radius);
            break;
        case 20:    // Cubic Bezier
        case 21:    // Cubic Bezier nearly through two points
            ImGui::SliderFloat2("Point 1", &m_p1[0], 0.0f, 1.0f);
            ImGui::SliderFloat2("Point 2", &m_p2[0], 0.0f, 1.0f);
            m_shaderProgram.SetUniform2("u_p1", m_p1);
            m_shaderProgram.SetUniform2("u_p2", m_p2);
            break;
        case 22:    // Almost identity
            ImGui::InputFloat("Zoom", &m_zoom);
            ImGui::SliderFloat("Threshold", &m_p1.x, 0.0f, 1.0f);
            ImGui::SliderFloat("Substitute value", &m_p1.y, 0.0f, 1.0f);
            m_shaderProgram.SetUniform1("u_zoom", m_zoom);
            m_shaderProgram.SetUniform2("u_p1", m_p1);
            break;
        case 23:    // Almost abs
        case 24:    // Smoothstep integral
        case 29:    // Sinc
        case 30:    // Truncated falloff
            ImGui::InputFloat("Zoom", &m_zoom);
            ImGui::SliderFloat("Point", &m_point, 0.0f, 1.0f);
            m_shaderProgram.SetUniform1("u_zoom", m_zoom);
            m_shaderProgram.SetUniform1("u_point", m_point);
            break;
        case 25:    // Exponential impulse
        case 26:    // Quadratic impulse
            ImGui::InputFloat("Zoom", &m_zoom);
            ImGui::SliderFloat("Inflection", &m_inflection, 0.0f, 1.0f);
            m_shaderProgram.SetUniform1("u_zoom", m_zoom);
            m_shaderProgram.SetUniform1("u_inflection", m_inflection);
            break;
        case 27:    // Polynomial impulse
            ImGui::InputFloat("Zoom", &m_zoom);
            ImGui::SliderFloat("Inflection", &m_inflection, 0.0f, 1.0f);
            ImGui::InputInt("Exponent", &m_exponent);
            m_shaderProgram.SetUniform1("u_zoom", m_zoom);
            m_shaderProgram.SetUniform1("u_inflection", m_inflection);
            m_shaderProgram.SetUniform1("u_exponent", m_exponent);
            break;
        case 28:    // Exponential sustained impulse
            ImGui::InputFloat("Zoom", &m_zoom);
            ImGui::SliderFloat("Attack", &m_p1.x, 0.0f, 1.0f);
            ImGui::SliderFloat("Falloff", &m_p1.y, 0.0f, 1.0f);
            m_shaderProgram.SetUniform1("u_zoom", m_zoom);
            m_shaderProgram.SetUniform2("u_p1", m_p1);
            break;
        }
    }

    void TestShader::OnUpdate(float deltaTime)
    {
        // Update time
        m_time += deltaTime;
        m_shaderProgram.SetUniform1("u_time", m_time);

        // Update resolution
        auto [resolutionX, resolutionY] = m_rendererInstance.GetViewportSize();
        m_resolution                    = {resolutionX, resolutionY};
        m_shaderProgram.SetUniform2("u_resolution", m_resolution);

        // Update mouse
        double cursorX, cursorY;
        glfwGetCursorPos(m_rendererInstance.GetWindow(), &cursorX, &cursorY);
        m_mouse = {cursorX, resolutionY - cursorY};
        m_shaderProgram.SetUniform2("u_mouse", m_mouse);
    }
} // namespace Tests

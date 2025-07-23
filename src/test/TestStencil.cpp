#include "TestStencil.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

namespace Tests
{
    TestStencil::TestStencil():
        m_planeVBO{
            s_planeVertices, sizeof(s_planeVertices) / sizeof(s_planeVertices[0])
    },
        m_planeEBO{s_planeIndices, sizeof(s_planeIndices) / sizeof(s_planeIndices[0])},
        m_planeTexture{"assets/textures/metal.jpg"},
        m_cubeVBO{s_cubeVertices, sizeof(s_cubeVertices) / sizeof(s_cubeVertices[0])},
        m_cubeTexture{"assets/textures/grey_marble.jpg"},
        m_objectShaderProgram{
            "assets/shaders/TestStencil/TestStencil.vert.glsl", "assets/shaders/TestStencil/TestStencil.frag.glsl"
        },
        m_colorShaderProgram{
            "assets/shaders/TestStencil/TestStencil.vert.glsl", "assets/shaders/TestStencil/SolidColor.frag.glsl"
        },
        m_camera{{0.0f, 1.0f, 3.0f}}
    {
        Renderer& r = Renderer::GetInstance();

        // Configure stencil buffer settings
        r.clearFlags |= Renderer::ClearFlags::StencilBuffer; // Clear stencil buffer every frame
        r.EnableFeatures(Renderer::FeatureFlags::StencilTest);
        r.SetStencilTestFunction(Renderer::StencilTestFunction::NotEqual, 1, 0xFF);
        r.SetStencilOperation(
            Renderer::StencilOperation::Keep, Renderer::StencilOperation::Keep, Renderer::StencilOperation::Replace
        );

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
        m_objectShaderProgram.SetUniform1("u_texture", 0);

        // Initialize camera
        m_camera.InitForGLFW();
    }

    TestStencil::~TestStencil()
    {
        Renderer& r = Renderer::GetInstance();

        // Reset stencil buffer/test configuration
        r.clearFlags &= ~Renderer::ClearFlags::StencilBuffer; // Don't clear the stencil buffer every frame
        r.SetStencilTestFunction(Renderer::StencilTestFunction::Always, 0, 0xFF); // Reset stencil test function
        r.DisableFeatures(Renderer::FeatureFlags::StencilTest);
    }

    void TestStencil::OnRender()
    {
        Renderer& r = Renderer::GetInstance();
        r.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Update view and projection matrices
        m_objectShaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_objectShaderProgram.SetUniformMat4("u_proj", m_camera.proj);
        m_colorShaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_colorShaderProgram.SetUniformMat4("u_proj", m_camera.proj);

        // Render plane
        r.SetStencilMask(0x00); // Don't write to the stencil buffer
        m_planeTexture.Bind();
        m_objectShaderProgram.SetUniformMat4(
            "u_model",
            glm::rotate(glm::scale(glm::mat4{1.0f}, glm::vec3{4.0f}), glm::radians(-90.0f), glm::vec3{1.0f, 0.0f, 0.0f})
        );
        r.DrawElements(m_planeVAO, m_objectShaderProgram);

        // Render cubes with the normal shader
        r.SetStencilTestFunction(Renderer::StencilTestFunction::Always, 1, 0xFF);
        r.SetStencilMask(0xFF); // Write to the stencil buffer
        m_cubeTexture.Bind();
        for(const glm::vec3& position : s_cubePositions)
        {
            glm::mat4 model = glm::translate(glm::mat4{1.0f}, position);
            m_objectShaderProgram.SetUniformMat4("u_model", model);
            r.DrawVertices(m_cubeVAO, m_objectShaderProgram);
        }

        r.SetStencilTestFunction(Renderer::StencilTestFunction::NotEqual, 1, 0xFF);
        r.SetStencilMask(0x00); // Disable writing to the stencil buffer
        r.SetDepthMask(false);  // Disable writing to the depth buffer

        // Render scaled-up cube outlines with the color shader
        m_colorShaderProgram.SetUniform3("u_color", m_outlineColor);
        for(const glm::vec3& position : s_cubePositions)
        {
            glm::mat4 model = glm::translate(glm::mat4{1.0f}, position);
            model           = glm::scale(model, glm::vec3{1.05f}); // Scale up the cube for the outline
            m_colorShaderProgram.SetUniformMat4("u_model", model);
            r.DrawVertices(m_cubeVAO, m_colorShaderProgram);
        }

        // Reset settings to normal
        r.SetStencilTestFunction(Renderer::StencilTestFunction::Always, 0, 0xFF); // Reset stencil test function
        r.SetStencilMask(0xFF);                                                   // Reset stencil mask
        r.SetDepthMask(true);                                                     // Reset depth mask
    }

    void TestStencil::OnImGuiRender()
    {
        ImGui::ColorEdit3("Outline color", &m_outlineColor[0]);
    }

    void TestStencil::OnUpdate(float deltaTime)
    {
        m_camera.OnUpdate(deltaTime);
    }
} // namespace Tests

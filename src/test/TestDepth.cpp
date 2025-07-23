#include "TestDepth.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

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

        // Initialize camera
        m_camera.InitForGLFW();
    }

    TestDepth::~TestDepth()
    {}

    void TestDepth::OnRender()
    {
        Renderer& r = Renderer::GetInstance();

        m_shaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_shaderProgram.SetUniformMat4("u_proj", m_camera.proj);
        m_shaderProgram.SetUniform1("u_near", m_camera.near);
        m_shaderProgram.SetUniform1("u_far", m_camera.far);

        // Render cubes
        m_cubeTexture.Bind();
        for(const glm::vec3& position : s_cubePositions)
        {
            glm::mat4 model = glm::translate(glm::mat4{1.0f}, position);
            m_shaderProgram.SetUniformMat4("u_model", model);
            r.DrawVertices(m_cubeVAO, m_shaderProgram);
        }

        // Render plane
        m_planeTexture.Bind();
        m_shaderProgram.SetUniformMat4(
            "u_model",
            glm::rotate(glm::scale(glm::mat4{1.0f}, glm::vec3{4.0f}), glm::radians(-90.0f), glm::vec3{1.0f, 0.0f, 0.0f})
        );
        r.DrawElements(m_planeVAO, m_shaderProgram);
    }

    void TestDepth::OnImGuiRender()
    {
        Renderer& r = Renderer::GetInstance();
        if(ImGui::Checkbox("Enable depth test", &m_depthTestEnabled))
        {
            if(m_depthTestEnabled)
            {
                r.EnableFeatures(Renderer::FeatureFlags::DepthTest);
            }
            else
            {
                r.DisableFeatures(Renderer::FeatureFlags::DepthTest);
            }
        }
        if(ImGui::Checkbox("Clear depth buffer every frame", &m_clearDepthBuffer))
        {
            if(m_clearDepthBuffer)
            {
                r.clearFlags |= Renderer::ClearFlags::DepthBuffer;
            }
            else
            {
                r.clearFlags &= ~Renderer::ClearFlags::DepthBuffer;
            }
        }
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
            r.SetDepthTestFunction(
                static_cast<Renderer::DepthTestFunction>(s_depthFuncs[m_currentDepthFuncIndex].first)
            );
        }
    }

    void TestDepth::OnUpdate(float deltaTime)
    {
        m_camera.OnUpdate(deltaTime);
    }
} // namespace Tests

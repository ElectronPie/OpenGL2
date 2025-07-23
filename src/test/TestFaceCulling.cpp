#include "TestFaceCulling.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Tests
{
    TestFaceCulling::TestFaceCulling():
        m_cubeVBO{
            s_cubeVertices, sizeof(s_cubeVertices) / sizeof(s_cubeVertices[0])
    },
        m_cubeTexture{"assets/textures/grey_marble.jpg"},
        m_shaderProgram{
            "assets/shaders/TestFaceCulling/TestFaceCulling.vert.glsl",
            "assets/shaders/TestFaceCulling/TestFaceCulling.frag.glsl"
        },
        m_camera{{0.0f, 0.0f, 5.0f}}
    {
        Renderer& r = Renderer::GetInstance();
        r.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Setup cube vertex buffer layout
        m_cubeLayout.Push<float>(3); // position
        m_cubeLayout.Push<float>(2); // texture coords

        // Setup cube VAO
        m_cubeVAO.AttachVBO(m_cubeVBO, m_cubeLayout);

        // Enable face culling
        r.EnableFeatures(Renderer::FeatureFlags::FaceCulling);
        r.SetCullFace(Renderer::CullFace::Back);
        r.SetFrontFace(Renderer::FrontFace::CCW);

        // Initialize camera
        m_camera.InitForGLFW();
    }

    TestFaceCulling::~TestFaceCulling()
    {
        // Disable face culling
        Renderer::GetInstance().DisableFeatures(Renderer::FeatureFlags::FaceCulling);
    }

    void TestFaceCulling::OnRender()
    {
        Renderer& r = Renderer::GetInstance();

        // Update view and projection matrices
        m_shaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_shaderProgram.SetUniformMat4("u_proj", m_camera.proj);

        // Render cube
        m_shaderProgram.SetUniformMat4("u_model", glm::scale(glm::mat4{1.0f}, glm::vec3{4.0f}));
        m_cubeTexture.Bind();
        r.DrawVertices(m_cubeVAO, m_shaderProgram);
    }

    void TestFaceCulling::OnImGuiRender()
    {
        Renderer& r = Renderer::GetInstance();

        if(ImGui::Checkbox("Enable face culling", &m_enableFaceCulling))
        {
            if(m_enableFaceCulling)
                r.EnableFeatures(Renderer::FeatureFlags::FaceCulling);
            else
                r.DisableFeatures(Renderer::FeatureFlags::FaceCulling);
        }

        if(ImGui::Combo(
               "Cull faces",
               &m_currentCullFaceIdx,
               [](void*, int idx) { return s_cullFaceValues[idx].second; },
               nullptr,
               s_numCullFaceValues
           ))
        {
            r.SetCullFace(static_cast<Renderer::CullFace>(s_cullFaceValues[m_currentCullFaceIdx].first));
        }

        if(ImGui::Combo(
               "Front faces",
               &m_currentFrontFaceIdx,
               [](void*, int idx) { return s_frontFaceValues[idx].second; },
               nullptr,
               s_numFrontFaceValues
           ))
        {
            r.SetFrontFace(static_cast<Renderer::FrontFace>(s_frontFaceValues[m_currentFrontFaceIdx].first));
        }
    }

    void TestFaceCulling::OnUpdate(float deltaTime)
    {
        m_camera.OnUpdate(deltaTime);
    }
} // namespace Tests

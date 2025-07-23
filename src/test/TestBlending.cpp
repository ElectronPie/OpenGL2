#include "TestBlending.hpp"

#include <imgui.h>

#include <map>

namespace Tests
{
    TestBlending::TestBlending():
        m_planeVBO{
            s_planeVertices, sizeof(s_planeVertices) / sizeof(s_planeVertices[0])
    },
        m_planeTexture{"assets/textures/metal.jpg"},
        m_cubeVBO{s_cubeVertices, sizeof(s_cubeVertices) / sizeof(s_cubeVertices[0])},
        m_cubeTexture{"assets/textures/grey_marble.jpg"},
        m_quadVBO{s_quadVertices, sizeof(s_quadVertices) / sizeof(s_quadVertices[0])},
        m_grassTexture{
            "assets/textures/grass.png",
            Texture::Type::None,
            Texture::WrapMode::ClampToEdge,
            Texture::WrapMode::ClampToEdge
        },
        m_windowTexture{
            "assets/textures/window.png",
            Texture::Type::None,
            Texture::WrapMode::ClampToEdge,
            Texture::WrapMode::ClampToEdge
        },
        m_shaderProgram{
            "assets/shaders/TestBlending/TestBlending.vert.glsl", "assets/shaders/TestBlending/TestBlending.frag.glsl"
        },
        m_camera{{0.0f, 1.0f, 3.0f}}
    {
        Renderer& r = Renderer::GetInstance();

        // Setup plane vertex buffer layout
        m_planeLayout.Push<float>(3); // position
        m_planeLayout.Push<float>(2); // texture coords

        // Setup plane VAO
        m_planeVAO.AttachVBO(m_planeVBO, m_planeLayout);

        // Setup cube vertex buffer layout
        m_cubeLayout.Push<float>(3); // position
        m_cubeLayout.Push<float>(2); // texture coords

        // Setup cube VAO
        m_cubeVAO.AttachVBO(m_cubeVBO, m_cubeLayout);

        // Setup grass quad's vertex buffer layout
        m_quadLayout.Push<float>(3); // position
        m_quadLayout.Push<float>(2); // texture coords

        // Setup grass quad VAO
        m_quadVAO.AttachVBO(m_quadVBO, m_quadLayout);

        // Setup shader uniforms
        m_shaderProgram.SetUniform1("u_texture", 0);

        // Enable blending
        r.EnableFeatures(Renderer::FeatureFlags::Blending);
        r.SetBlendingFunctionFactor(
            Renderer::BlendingFunctionFactor::SourceAlpha, Renderer::BlendingFunctionFactor::OneMinusSourceAlpha
        );

        // Initialize camera
        m_camera.InitForGLFW();
    }

    TestBlending::~TestBlending()
    {}

    void TestBlending::OnRender()
    {
        Renderer& r = Renderer::GetInstance();

        // Update view and projection matrices
        m_shaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_shaderProgram.SetUniformMat4("u_proj", m_camera.proj);

        // Render plane
        m_planeTexture.Bind();
        m_shaderProgram.SetUniformMat4("u_model", glm::mat4{1.0f});
        r.DrawVertices(m_planeVAO, m_shaderProgram);

        // Render cubes
        m_cubeTexture.Bind();
        for(const glm::vec3& position : s_cubePositions)
        {
            glm::mat4 model = glm::translate(glm::mat4{1.0f}, position);
            m_shaderProgram.SetUniformMat4("u_model", model);
            r.DrawVertices(m_cubeVAO, m_shaderProgram);
        }

        // Render vegetation
        if(m_renderWindows)
            m_windowTexture.Bind();
        else
            m_grassTexture.Bind();
        std::map<float, glm::vec3> positionsSorted;
        for(const glm::vec3& position : s_quadsPositions)
        {
            float distance            = glm::distance(m_camera.position, position);
            positionsSorted[distance] = position;
        }
        for(auto it = positionsSorted.rbegin(); it != positionsSorted.rend(); ++it)
        {
            glm::mat4 model = glm::translate(glm::mat4{1.0f}, it->second);
            m_shaderProgram.SetUniformMat4("u_model", model);
            r.DrawVertices(m_quadVAO, m_shaderProgram);
        }
    }

    void TestBlending::OnImGuiRender()
    {
        Renderer& r = Renderer::GetInstance();

        ImGui::Checkbox("Render semi-transparent windows", &m_renderWindows);

        if(ImGui::Checkbox("Enable blending", &m_enableBlending))
        {
            if(m_enableBlending)
                r.EnableFeatures(Renderer::FeatureFlags::Blending);
            else
                r.DisableFeatures(Renderer::FeatureFlags::Blending);
        }

        if(ImGui::Combo(
               "Source factor",
               &m_currentSRCFactorIdx,
               [](void*, int idx) { return s_factorValues[idx].second; },
               nullptr,
               s_numFactors
           ))
        {
            r.SetBlendingFunctionFactor(
                static_cast<Renderer::BlendingFunctionFactor>(s_factorValues[m_currentSRCFactorIdx].first),
                static_cast<Renderer::BlendingFunctionFactor>(s_factorValues[m_currentDSTFactorIdx].first)
            );
        }

        if(ImGui::Combo(
               "Destination factor",
               &m_currentDSTFactorIdx,
               [](void*, int idx) { return s_factorValues[idx].second; },
               nullptr,
               s_numFactors
           ))
        {
            r.SetBlendingFunctionFactor(
                static_cast<Renderer::BlendingFunctionFactor>(s_factorValues[m_currentSRCFactorIdx].first),
                static_cast<Renderer::BlendingFunctionFactor>(s_factorValues[m_currentDSTFactorIdx].first)
            );
        }

        if(ImGui::ColorEdit4("Blending constant color", &m_blendingConstantColor[0]))
        {
            r.SetBlendingConstantColor(m_blendingConstantColor);
        }

        if(ImGui::Combo(
               "Blending equation",
               &m_currentBlendEquationIdx,
               [](void*, int idx) { return s_equationValues[idx].second; },
               nullptr,
               s_numEquations
           ))
        {
            r.SetBlendingEquation(
                static_cast<Renderer::BlendingEquation>(s_equationValues[m_currentBlendEquationIdx].first)
            );
        }
    }

    void TestBlending::OnUpdate(float deltaTime)
    {
        m_camera.OnUpdate(deltaTime);
    }
} //namespace Tests

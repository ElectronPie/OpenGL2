#include "TestFramebuffer.hpp"

#include "Format.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

namespace Tests
{
    using namespace std::literals::string_literals;

    TestFramebuffer::TestFramebuffer():
        m_planeVBO{
            s_planeVertices, sizeof(s_planeVertices) / sizeof(s_planeVertices[0])
    },
        m_planeEBO{s_planeIndices, sizeof(s_planeIndices) / sizeof(s_planeIndices[0])},
        m_planeTexture{"assets/textures/metal.jpg"},
        m_cubeVBO{s_cubeVertices, sizeof(s_cubeVertices) / sizeof(s_cubeVertices[0])},
        m_cubeTexture{"assets/textures/container.jpg"},
        m_sceneShaderProgram{
            "assets/shaders/TestFramebuffer/Scene.vert.glsl", "assets/shaders/TestFramebuffer/Scene.frag.glsl"
        },
        m_quadVBO{s_quadVertices, sizeof(s_quadVertices) / sizeof(s_quadVertices[0])},
        m_quadEBO{s_quadIndices, sizeof(s_quadIndices) / sizeof(s_quadIndices[0])},
        m_screenShaderProgram{
            "assets/shaders/TestFramebuffer/Screen.vert.glsl",
            "assets/shaders/TestFramebuffer/"s + s_shaderNames[m_currentShaderName] + ".frag.glsl"
        },
        m_camera{{0.0f, 1.0f, 3.0f}}, m_screenTexture{}, m_RBO{}
    {
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

        // Setup quad vertex buffer layout
        m_quadLayout.Push<float>(3); // position
        m_quadLayout.Push<float>(2); // texture coords

        // Setup quad VAO
        m_quadVAO.AttachVBO(m_quadVBO, m_quadLayout);
        m_quadVAO.AttachEBO(m_quadEBO);

        // Setup shader uniforms
        m_sceneShaderProgram.SetUniform1("u_texture", 0);
        m_screenShaderProgram.SetUniform1("u_texture", 0);

        // Setup the FBO
        m_FBO.AttachTexture(m_screenTexture, FBO::Attachment::Color);
        m_FBO.AttachRenderbuffer(m_RBO, FBO::Attachment::DepthStencil);

        // Ensure the framebuffer will draw to the color attachment we just set
        GLCall(glDrawBuffer(GL_COLOR_ATTACHMENT0));

        if(!m_FBO())
        {
            std::cout << "Framebuffer is not complete!" << std::endl;
        }
        m_FBO.Unbind();

        // Initialize camera
        m_camera.InitForGLFW();
    }

    TestFramebuffer::~TestFramebuffer()
    {}

    void TestFramebuffer::OnRender()
    {
        Renderer& r = Renderer::GetInstance();

        // First pass: render the scene to the framebuffer
        m_FBO.Bind();
        r.ClearColor(0.0f, 0.5f, 0.7f, 1.0f);
        r.clearFlags = Renderer::ClearFlags::ColorBuffer | Renderer::ClearFlags::DepthBuffer;
        r.Clear();
        r.EnableFeatures(Renderer::FeatureFlags::DepthTest);

        m_sceneShaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_sceneShaderProgram.SetUniformMat4("u_proj", m_camera.proj);

        // Render cubes
        m_cubeTexture.Bind();
        for(const glm::vec3& position : s_cubePositions)
        {
            glm::mat4 model = glm::translate(glm::mat4{1.0f}, position);
            m_sceneShaderProgram.SetUniformMat4("u_model", model);
            r.DrawVertices(m_cubeVAO, m_sceneShaderProgram);
        }

        // Render plane
        m_planeTexture.Bind();
        m_sceneShaderProgram.SetUniformMat4(
            "u_model",
            glm::rotate(glm::scale(glm::mat4{1.0f}, glm::vec3{4.0f}), glm::radians(-90.0f), glm::vec3{1.0f, 0.0f, 0.0f})
        );
        r.DrawElements(m_planeVAO, m_sceneShaderProgram);

        // Second pass: render the framebuffer texture to the default framebuffer
        m_FBO.Unbind();
        r.ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        r.clearFlags = Renderer::ClearFlags::ColorBuffer;
        r.Clear();
        r.DisableFeatures(Renderer::FeatureFlags::DepthTest);

        m_screenTexture.Bind();
        r.DrawElements(m_quadVAO, m_screenShaderProgram);
    }

    void TestFramebuffer::OnImGuiRender()
    {
        ImGui::Combo(
            "glPolygonMode face type",
            &m_currentFaceTypeIdx,
            [](void* user_data, int idx) -> const char* { return s_faceTypes[idx].second; },
            nullptr,
            s_faceTypesCount
        );
        ImGui::Combo(
            "Polygons draw mode",
            &m_currentPolygonModeIdx,
            [](void* user_data, int idx) -> const char* { return s_polygonModes[idx].second; },
            nullptr,
            s_polygonModesCount
        );
        if(ImGui::Button("Apply"))
        {
            GLCall(
                glPolygonMode(s_faceTypes[m_currentFaceTypeIdx].first, s_polygonModes[m_currentPolygonModeIdx].first)
            );
        }

        if(ImGui::Combo("Screen fragment shader", &m_currentShaderName, s_shaderNames, s_shaderNamesCount))
        {
            Renderer& r = Renderer::GetInstance();

            m_screenShaderProgram = ShaderProgram{
                "assets/shaders/TestFramebuffer/Screen.vert.glsl",
                "assets/shaders/TestFramebuffer/"s + s_shaderNames[m_currentShaderName] + ".frag.glsl"
            };
            // Setup shader uniforms
            m_sceneShaderProgram.SetUniform1("u_texture", 0);
            m_screenShaderProgram.SetUniform1("u_texture", 0);
            const auto [width, height] = r.GetViewportSize();
            m_screenShaderProgram.SetUniform2("u_offset", glm::vec2{2.0f / width, 2.0f / height});
        }
    }

    void TestFramebuffer::OnUpdate(float deltaTime)
    {
        m_camera.OnUpdate(deltaTime);
    }
} // namespace Tests

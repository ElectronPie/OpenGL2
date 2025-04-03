#include "TestMVP.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include <imgui.h>

#include <string>

static inline void EditMatrix4(const std::string& name, glm::mat4& matrix)
{
    if(ImGui::BeginTable(name.c_str(), 4))
    {
        size_t counter = 0;
        for(std::size_t i = 0; i < 16; ++i)
        {
            std::stringstream ss;
            ss << "##" << ++counter;
            ImGui::TableNextColumn();
            ImGui::InputFloat(ss.str().c_str(), &matrix[i % 4][i / 4]);
        }
        ImGui::EndTable();
    }
}

namespace Tests
{
    TestMVP::TestMVP():
        m_planeVbo{s_planeVertices, sizeof(s_planeVertices)},
        m_planeEbo{s_planeIndices, sizeof(s_planeIndices) / sizeof(s_planeIndices[0])},
        m_cubeVbo{s_cubeVertices, sizeof(s_cubeVertices)},
        m_cubeEbo{s_cubeIndices, sizeof(s_cubeIndices) / sizeof(s_cubeIndices[0])},
        m_shaderProgram{"assets/shaders/TestMVP.vert.glsl", "assets/shaders/TestMVP.frag.glsl"},
        m_texture1{"assets/textures/container.jpg"}, m_texture2{"assets/textures/awesomeface.png"},
        m_rendererInstance{Renderer::GetInstance()}, m_mode{0}
    {
        // Setup plane vertex buffer layout
        m_planeLayout.Push<float>(3); // position
        m_planeLayout.Push<float>(2); // texture coords

        // Setup plane VAO
        m_planeVao.AttachVBO(m_planeVbo, m_planeLayout);
        m_planeVao.AttachEBO(m_planeEbo);

        // Setup cube vertex buffer layout
        m_cubeLayout.Push<float>(3); // position
        m_cubeLayout.Push<float>(2); // texture coords

        // Setup cube VAO
        m_cubeVao.AttachVBO(m_cubeVbo, m_cubeLayout);
        m_cubeVao.AttachEBO(m_cubeEbo);

        // Bind textures to samplers
        m_texture1.Bind(0);
        m_texture2.Bind(1);
        m_shaderProgram.SetUniform1("u_texture1", 0);
        m_shaderProgram.SetUniform1("u_texture2", 1);

        // Set transform data to correct values
        for(TransformData& transformData : m_transforms)
        {
            UpdateTransformData(transformData);
        }
    }

    TestMVP::~TestMVP()
    {}

    void TestMVP::OnRender()
    {
        TransformData& transformData = m_transforms[m_mode];

        switch(m_mode)
        {
        case 0: // Plane
            m_shaderProgram.SetUniformMat4("u_model", transformData.model);
            m_shaderProgram.SetUniformMat4("u_view", transformData.view);
            m_shaderProgram.SetUniformMat4("u_proj", transformData.proj);
            m_rendererInstance.Draw(m_planeVao, m_shaderProgram);
            break;
        case 1: // Cube
            m_shaderProgram.SetUniformMat4("u_model", transformData.model);
            m_shaderProgram.SetUniformMat4("u_view", transformData.view);
            m_shaderProgram.SetUniformMat4("u_proj", transformData.proj);
            m_rendererInstance.Draw(m_cubeVao, m_shaderProgram);
            break;
        case 2:
            m_shaderProgram.SetUniformMat4("u_view", transformData.view);
            m_shaderProgram.SetUniformMat4("u_proj", transformData.proj);
            for(unsigned int i = 0; i < 10; ++i)
            {
                glm::mat4 model{1.0f};
                model       = glm::translate(model, s_cubePositions[i]);
                float angle = 20.0f * i * PartyModeAngleCoefficient();
                model       = glm::rotate(model, glm::radians(angle), glm::vec3{1.0f, 0.3f, 0.5f});
                m_shaderProgram.SetUniformMat4("u_model", model);
                m_rendererInstance.Draw(m_cubeVao, m_shaderProgram);
            }
        }
    }

    void TestMVP::OnImGuiRender()
    {
        ImGui::Text("Test mode");
        ImGui::RadioButton("Plane", &m_mode, 0);
        ImGui::RadioButton("Cube", &m_mode, 1);
        ImGui::RadioButton("Cubes", &m_mode, 2);

        TransformData& transformData = m_transforms[m_mode];

        switch(m_mode)
        {
        case 0: // Plane
        case 1: // Cube
            ImGui::Text("Model");
            EditMatrix4("Model", transformData.model);
            ImGui::InputFloat3("Translate##Model", &transformData.modelTranslation[0]);
            ImGui::SliderFloat3("Rotate (pitch/yaw/roll)##Model", &transformData.modelAngle[0], -180.0f, 180.0f);
            ImGui::InputFloat3("Scale##Model", &transformData.modelScale[0]);

            ImGui::Text("View");
            EditMatrix4("View", transformData.view);
            ImGui::InputFloat3("Translate (camera position)##View", &transformData.viewTranslation[0]);
            ImGui::SliderFloat3("Rotate (pitch/yaw/roll)##View", &transformData.viewAngle[0], 0.0f, 360.0f);

            ImGui::Text("Projection");
            EditMatrix4("Projection", transformData.proj);
            ImGui::RadioButton("Orthographic projection", (int*)&transformData.projType, false);
            ImGui::RadioButton("Perspective projection", (int*)&transformData.projType, true);
            if(transformData.projType)
            {
                ImGui::InputFloat("FOV", &transformData.projPerspFOV);
                ImGui::BeginDisabled(
                    ImGui::Checkbox("Use viewport aspect ratio", &transformData.projPerspUseViewportRatio)
                );
                ImGui::InputFloat("Width", &transformData.projPerspWidth);
                ImGui::InputFloat("Height", &transformData.projPerspHeight);
                ImGui::EndDisabled();
                ImGui::InputFloat("Near", &transformData.projOrthoFrustumNear);
                ImGui::InputFloat("Far", &transformData.projOrthoFrustumFar);
            }
            else
            {
                ImGui::InputFloat("Left", &transformData.projOrthoFrustumLeft);
                ImGui::InputFloat("Right", &transformData.projOrthoFrustumRight);
                ImGui::InputFloat("Top", &transformData.projOrthoFrustumTop);
                ImGui::InputFloat("Bottom", &transformData.projOrthoFrustumBottom);
                ImGui::BeginDisabled(ImGui::Checkbox("Use near/far planes", &transformData.projOrthoUseNearFarPlanes));
                ImGui::InputFloat("Near", &transformData.projOrthoFrustumNear);
                ImGui::InputFloat("Far", &transformData.projOrthoFrustumFar);
                ImGui::EndDisabled();
            }

            break;

        case 2: // Cubes
            ImGui::Text("View");
            EditMatrix4("View", transformData.view);
            ImGui::InputFloat3("Translate (camera position)##View", &transformData.viewTranslation[0]);
            ImGui::SliderFloat3("Rotate (pitch/yaw/roll)##View", &transformData.viewAngle[0], 0.0f, 360.0f);

            ImGui::Text("Projection");
            EditMatrix4("Projection", transformData.proj);
            ImGui::RadioButton("Orthographic projection", (int*)&transformData.projType, false);
            ImGui::RadioButton("Perspective projection", (int*)&transformData.projType, true);
            if(transformData.projType)
            {
                ImGui::InputFloat("FOV", &transformData.projPerspFOV);
                ImGui::BeginDisabled(
                    ImGui::Checkbox("Use viewport aspect ratio", &transformData.projPerspUseViewportRatio)
                );
                ImGui::InputFloat("Width", &transformData.projPerspWidth);
                ImGui::InputFloat("Height", &transformData.projPerspHeight);
                ImGui::EndDisabled();
                ImGui::InputFloat("Near", &transformData.projOrthoFrustumNear);
                ImGui::InputFloat("Far", &transformData.projOrthoFrustumFar);
            }
            else
            {
                ImGui::InputFloat("Left", &transformData.projOrthoFrustumLeft);
                ImGui::InputFloat("Right", &transformData.projOrthoFrustumRight);
                ImGui::InputFloat("Top", &transformData.projOrthoFrustumTop);
                ImGui::InputFloat("Bottom", &transformData.projOrthoFrustumBottom);
                ImGui::BeginDisabled(ImGui::Checkbox("Use near/far planes", &transformData.projOrthoUseNearFarPlanes));
                ImGui::InputFloat("Near", &transformData.projOrthoFrustumNear);
                ImGui::InputFloat("Far", &transformData.projOrthoFrustumFar);
                ImGui::EndDisabled();
            }
            ImGui::Checkbox("Party mode", &m_partyMode);
            if(ImGui::Button("Reset party"))
            {
                m_timeMark = 0.0f;
            }
        }

        UpdateTransformData(transformData);
    }

    void TestMVP::OnUpdate(float deltaTime)
    {
        if(m_partyMode)
        {
            m_timeMark += deltaTime;
        }
    }

    void TestMVP::UpdateTransformData(TestMVP::TransformData& transformData)
    {
        // Model
        {
            transformData.model = glm::mat4{1.0f};
            transformData.model = glm::scale(transformData.model, transformData.modelScale);
            glm::mat4 rotation  = glm::eulerAngleXYZ(
                glm::radians(transformData.modelAngle.x),
                glm::radians(transformData.modelAngle.y),
                glm::radians(transformData.modelAngle.z)
            );
            transformData.model = rotation * transformData.model;
            transformData.model = glm::translate(transformData.model, transformData.modelTranslation);
        }

        // View
        {
            transformData.view = glm::mat4{1.0f};
            glm::mat4 rotation = glm::eulerAngleXYZ(
                glm::radians(transformData.viewAngle.x),
                glm::radians(transformData.viewAngle.y),
                glm::radians(transformData.viewAngle.z)
            );
            transformData.view = rotation * transformData.view;
            transformData.view = glm::translate(transformData.view, -transformData.viewTranslation);
        }

        // Projection
        {
            if(transformData.projType)
            {
                if(transformData.projPerspUseViewportRatio)
                {
                    auto [width, height]          = m_rendererInstance.GetViewportSize();
                    transformData.projPerspWidth  = width;
                    transformData.projPerspHeight = height;
                }
                transformData.proj = glm::perspective(
                    glm::radians(transformData.projPerspFOV),
                    transformData.projPerspWidth / transformData.projPerspHeight,
                    transformData.projPerspFrustumNear,
                    transformData.projPerspFrustumFar
                );
            }
            else
            {
                if(transformData.projOrthoUseNearFarPlanes)
                {
                    transformData.proj = glm::ortho(
                        transformData.projOrthoFrustumLeft,
                        transformData.projOrthoFrustumRight,
                        transformData.projOrthoFrustumTop,
                        transformData.projOrthoFrustumBottom,
                        transformData.projOrthoFrustumNear,
                        transformData.projOrthoFrustumFar
                    );
                }
                else
                {
                    transformData.proj = glm::ortho(
                        transformData.projOrthoFrustumLeft,
                        transformData.projOrthoFrustumRight,
                        transformData.projOrthoFrustumTop,
                        transformData.projOrthoFrustumBottom
                    );
                }
            }
        }
    }

    float TestMVP::PartyModeAngleCoefficient()
    {
        float x = m_timeMark;
        return -2 * (1 - x) * glm::cos(glm::abs(x == 0 ? 0 : glm::sin(x) / x));
    }
} // namespace Tests

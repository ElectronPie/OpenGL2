#include "TestLighting.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

#include "Renderer.hpp"

namespace Tests
{
    TestLighting::TestLighting():
        m_vbo{
            s_vertices, sizeof(s_vertices) / sizeof(s_vertices[0])
    },
        m_objectShaderProgram{
            "assets/shaders/TestLighting/Object.vert.glsl", "assets/shaders/TestLighting/Object.frag.glsl"
        },
        m_lightShaderProgram{
            "assets/shaders/TestLighting/Light.vert.glsl", "assets/shaders/TestLighting/Light.frag.glsl"
        },
        m_diffuseMap{"assets/textures/container2.png"}, m_specularMap{"assets/textures/container2_specular.png"},
        //m_emissionTexture{"assets/textures/matrix.jpg"},
        m_camera{{0.0f, 0.0f, 3.0f}}
    {
        Renderer& r = Renderer::GetInstance();

        // Setup vertex buffer layout
        m_layout.Push<float>(3);
        m_layout.Push<float>(3);
        m_layout.Push<float>(2);

        // Setup object VAO
        m_objectVAO.AttachVBO(m_vbo, m_layout);

        // Setup light VAO
        m_lightVAO.AttachVBO(m_vbo, m_layout);

        r.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        m_diffuseMap.Bind(0);
        m_specularMap.Bind(1);
        //m_emissionMap.Bind(2);

        // Initialize camera
        m_camera.InitForGLFW();
    }

    TestLighting::~TestLighting()
    {}

    void TestLighting::OnRender()
    {
        Renderer& r = Renderer::GetInstance();

        r.ClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 1.0f);

        m_objectShaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_objectShaderProgram.SetUniformMat4("u_proj", m_camera.proj);
        m_objectShaderProgram.SetUniformMat3("u_normal", glm::transpose(glm::inverse(glm::mat3{m_camera.view})));

        m_objectShaderProgram.SetUniform1("u_material.diffuse", 0);
        m_objectShaderProgram.SetUniform1("u_material.specular", 1);
        m_objectShaderProgram.SetUniform1("u_material.shininess", m_shininess);

        m_objectShaderProgram.SetUniform3("u_dirLight.direction", m_dirLight.direction);
        m_objectShaderProgram.SetUniform3("u_dirLight.ambient", m_dirLight.ambient);
        m_objectShaderProgram.SetUniform3("u_dirLight.diffuse", m_dirLight.diffuse);
        m_objectShaderProgram.SetUniform3("u_dirLight.specular", m_dirLight.specular);

        for(unsigned int i = 0; i < sizeof(m_pointLights) / sizeof(m_pointLights[0]); ++i)
        {
            using namespace std::literals::string_literals;

            m_objectShaderProgram.SetUniform3(
                "u_pointLights["s + std::to_string(i) + "].position", m_pointLights[i].position
            );
            m_objectShaderProgram.SetUniform3(
                "u_pointLights["s + std::to_string(i) + "].ambient", m_pointLights[i].ambient
            );
            m_objectShaderProgram.SetUniform3(
                "u_pointLights["s + std::to_string(i) + "].diffuse", m_pointLights[i].diffuse
            );
            m_objectShaderProgram.SetUniform3(
                "u_pointLights["s + std::to_string(i) + "].specular", m_pointLights[i].specular
            );
            m_objectShaderProgram.SetUniform1(
                "u_pointLights["s + std::to_string(i) + "].attConst", m_pointLights[i].attConst
            );
            m_objectShaderProgram.SetUniform1(
                "u_pointLights["s + std::to_string(i) + "].attLinear", m_pointLights[i].attLinear
            );
            m_objectShaderProgram.SetUniform1(
                "u_pointLights["s + std::to_string(i) + "].attQuadratic", m_pointLights[i].attQuadratic
            );

            glm::mat4 model{1.0f};
            model = glm::translate(model, m_pointLights[i].position);
            model = glm::scale(model, glm::vec3(0.2f));
            m_lightShaderProgram.SetUniformMat4("u_model", model);
            m_lightShaderProgram.SetUniformMat4("u_view", m_camera.view);
            m_lightShaderProgram.SetUniformMat4("u_proj", m_camera.proj);
            m_lightShaderProgram.SetUniform3("u_pointLight.position", m_pointLights[i].position);
            m_lightShaderProgram.SetUniform1("u_pointLight.attConst", m_pointLights[i].attConst);
            m_lightShaderProgram.SetUniform1("u_pointLight.attLinear", m_pointLights[i].attLinear);
            m_lightShaderProgram.SetUniform1("u_pointLight.attQuadratic", m_pointLights[i].attQuadratic);
            m_lightShaderProgram.SetUniform3("u_pointLight.ambient", m_pointLights[i].ambient);
            m_lightShaderProgram.SetUniform3("u_pointLight.diffuse", m_pointLights[i].diffuse);
            m_lightShaderProgram.SetUniform3("u_pointLight.specular", m_pointLights[i].specular);

            r.DrawVertices(m_lightVAO, m_lightShaderProgram);
        }

        m_objectShaderProgram.SetUniform3("u_spotLight.position", m_camera.position);
        m_objectShaderProgram.SetUniform3("u_spotLight.direction", m_camera.front);

        m_objectShaderProgram.SetUniform3("u_spotLight.ambient", m_spotLight.ambient);
        m_objectShaderProgram.SetUniform3("u_spotLight.diffuse", m_spotLight.diffuse);
        m_objectShaderProgram.SetUniform3("u_spotLight.specular", m_spotLight.specular);
        m_objectShaderProgram.SetUniform1("u_spotLight.attConst", m_spotLight.attConst);
        m_objectShaderProgram.SetUniform1("u_spotLight.attLinear", m_spotLight.attLinear);
        m_objectShaderProgram.SetUniform1("u_spotLight.attQuadratic", m_spotLight.attQuadratic);
        m_objectShaderProgram.SetUniform1("u_spotLight.innerCutOffCos", m_spotLight.innerCutOffCos);
        m_objectShaderProgram.SetUniform1("u_spotLight.outerCutOffCos", m_spotLight.outerCutOffCos);

        for(unsigned int i = 0; i < sizeof(s_cubePositions) / sizeof(s_cubePositions[0]); ++i)
        {
            glm::mat4 model{1.0f};
            model       = glm::translate(model, s_cubePositions[i]);
            float angle = 20.0f * i;
            model       = glm::rotate(model, glm::radians(angle), glm::vec3{1.0f, 0.3f, 0.5f});
            m_objectShaderProgram.SetUniformMat4("u_model", model);
            r.DrawVertices(m_objectVAO, m_objectShaderProgram);
        }
    }

    void TestLighting::OnImGuiRender()
    {
        ImGui::ColorEdit3("Background color", &m_backgroundColor[0]);

        ImGui::Text("Directional light");
        ImGui::SliderFloat3("Light direction##dir", &m_dirLight.direction[0], -1.0f, 1.0f);
        if(ImGui::Button("Normalize##dir"))
        {
            m_dirLight.direction = glm::normalize(m_dirLight.direction);
        }
        ImGui::ColorEdit3("Ambient##dir", &m_dirLight.ambient[0]);
        ImGui::ColorEdit3("Diffuse##dir", &m_dirLight.diffuse[0]);
        ImGui::ColorEdit3("Specular##dir", &m_dirLight.specular[0]);

        for(unsigned int i = 0; i < sizeof(m_pointLights) / sizeof(m_pointLights[0]); ++i)
        {
            using namespace std::literals::string_literals;

            ImGui::Text("Point light "s.append(std::to_string(i)).c_str());

            ImGui::InputFloat3("Position##point"s.append(std::to_string(i)).c_str(), &m_pointLights[i].position[0]);
            ImGui::ColorEdit3("Ambient##point"s.append(std::to_string(i)).c_str(), &m_pointLights[i].ambient[0]);
            ImGui::ColorEdit3("Diffuse##point"s.append(std::to_string(i)).c_str(), &m_pointLights[i].diffuse[0]);
            ImGui::ColorEdit3("Specular##point"s.append(std::to_string(i)).c_str(), &m_pointLights[i].specular[0]);
            ImGui::InputFloat(
                "Attenuation constant term##point"s.append(std::to_string(i)).c_str(), &m_pointLights[i].attConst
            );
            ImGui::InputFloat(
                "Attenuation linear term##point"s.append(std::to_string(i)).c_str(), &m_pointLights[i].attLinear
            );
            ImGui::InputFloat(
                "Attenuation quadratic term##point"s.append(std::to_string(i)).c_str(), &m_pointLights[i].attQuadratic
            );
        }

        ImGui::Text("Spot light");
        ImGui::ColorEdit3("Ambient##spot", &m_spotLight.ambient[0]);
        ImGui::ColorEdit3("Diffuse##spot", &m_spotLight.diffuse[0]);
        ImGui::ColorEdit3("Specular##spot", &m_spotLight.specular[0]);
        ImGui::InputFloat("Attenuation constant term##spot", &m_spotLight.attConst);
        ImGui::InputFloat("Attenuation linear term##spot", &m_spotLight.attLinear);
        ImGui::InputFloat("Attenuation quadratic term##spot", &m_spotLight.attQuadratic);
        ImGui::SliderFloat("Inner cut off cosine##spot", &m_spotLight.innerCutOffCos, 0.0f, 1.0f);
        ImGui::SliderFloat("Outer cut off cosine##spot", &m_spotLight.outerCutOffCos, 0.0f, 1.0f);

        ImGui::Text("Material");
        ImGui::InputFloat("Shininess##mat", &m_shininess);

        ImGui::Text("Presets");
        if(ImGui::Combo("Presets", &m_currentPreset, s_presetNames))
        {
            ApplyPreset(s_presets[m_currentPreset]);
        }
    }

    void TestLighting::OnUpdate(float deltaTime)
    {
        m_camera.OnUpdate(deltaTime);
    }

    void TestLighting::ApplyPreset(const TestLighting::Preset& preset)
    {
        m_backgroundColor = preset.backgroundColor;
        m_dirLight        = preset.dirLight;
        for(unsigned int i = 0; i < sizeof(m_pointLights) / sizeof(m_pointLights[0]); ++i)
        {
            m_pointLights[i] = preset.pointLights[i];
        }
        m_spotLight = preset.spotLight;
    }
} // namespace Tests

#include "TestLighting.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

#include "Renderer.hpp"

static Camera* s_camera;
static GLFWscrollfun s_oldCallback;

static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    s_camera->ProcessMouseScroll(yOffset);
    s_oldCallback(window, xOffset, yOffset);
}

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
        m_material{
            std::filesystem::path{"assets/textures/container2.png"},
            std::filesystem::path{"assets/textures/container2_specular.png"},
            //std::filesystem::path{"assets/textures/matrix.jpg"},
            glm::vec3{0.0f},
            32.0f
        },
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

        std::get<Texture>(m_material.diffuse).Bind(0);
        std::get<Texture>(m_material.specular).Bind(1);
        //std::get<Texture>(m_material.emission).Bind(2);

        // Setup GLFW callback for camera zoom
        s_camera      = &m_camera;
        s_oldCallback = glfwSetScrollCallback(r.GetWindow(), ScrollCallback);
    }

    TestLighting::~TestLighting()
    {
        // Reset GLFW scroll callback
        glfwSetScrollCallback(Renderer::GetInstance().GetWindow(), s_oldCallback);
    }

    void TestLighting::OnRender()
    {
        Renderer& r = Renderer::GetInstance();

        r.ClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 1.0f);

        m_objectShaderProgram.SetUniformMat4("u_view", m_camera.view);
        m_objectShaderProgram.SetUniformMat4("u_proj", m_camera.proj);
        m_objectShaderProgram.SetUniformMat3("u_normal", glm::transpose(glm::inverse(glm::mat3{m_camera.view})));

        m_objectShaderProgram.SetUniform1("u_material.diffuse", 0);
        m_objectShaderProgram.SetUniform1("u_material.specular", 1);
        m_objectShaderProgram.SetUniform1("u_material.shininess", m_material.shininess);

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
            m_lightShaderProgram.SetUniform1("u_pointPointLight.attLinear", m_pointLights[i].attLinear);
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
        ImGui::InputFloat("Shininess##mat", &m_material.shininess);

        ImGui::Text("Presets");
        if(ImGui::Combo("Presets", &m_currentPreset, s_presetNames))
        {
            ApplyPreset(s_presets[m_currentPreset]);
        }
    }

    void TestLighting::OnUpdate(float deltaTime)
    {
        Renderer& r = Renderer::GetInstance();

        // Keyboard input
        GLFWwindow* window = r.GetWindow();
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Forward, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Backward, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Left, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Right, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Down, deltaTime);
        if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            m_camera.ProcessTranslation(Camera::Movement::Up, deltaTime);

        // Mouse movement
        double cursorX, cursorY;
        glfwGetCursorPos(window, &cursorX, &cursorY);
        float deltaX = cursorX - m_cursorPos.x;
        float deltaY = m_cursorPos.y - cursorY; // Reversed since y-coordinates range from bottom to top
        m_cursorPos  = {cursorX, cursorY};
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
        {
            if(!m_mouseButtonPressed)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                m_mouseButtonPressed = true;
            }
            m_camera.ProcessMouseMovement(deltaX, deltaY);
        }
        else if(m_mouseButtonPressed)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            m_mouseButtonPressed = false;
        }

        // Update camera projection dimensions
        auto [width, height] = r.GetViewportSize();
        m_camera.width       = width;
        m_camera.height      = height;
        m_camera.UpdateProj();
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

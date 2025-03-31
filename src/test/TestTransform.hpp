#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace Tests
{
    class TestTransform: public Test
    {
    public:
        TestTransform();
        virtual ~TestTransform();

        void OnRender() override;
        void OnImGuiRender() override;
        void OnUpdate(float deltaTime) override;

    private:
        // clang-format off
        static inline float s_vertices[32] = {
            // position             // color            // texture coords
            +0.5f, +0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,     // top right
            +0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,     // bottom right
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,     // bottom left
            -0.5f, +0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   0.0f, 1.0f,     // top left
        };
        static inline unsigned int s_indices[6] = {
            0, 1, 2,
            0, 2, 3,
        };
        // clang-format on
        VBO m_vbo;
        VBLayout m_layout;
        EBO m_ebo;
        VAO m_vao;
        ShaderProgram m_shaderProgram;
        Texture m_texture1;
        Texture m_texture2;
        Renderer& m_rendererInstance;

        glm::vec3 m_translation{0.0f, 0.0f, 0.0f};
        float m_rotation = 0.0f;
        glm::vec3 m_scale{1.0f, 1.0f, 1.0f};
        glm::mat4 m_transform{1.0f};
    };
} // namespace Tests

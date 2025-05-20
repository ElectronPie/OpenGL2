#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace Tests
{
    /**
     * @brief Test for \(mostly\) 2D transforms on a plane
     */
    class TestTransform2D: public Test
    {
    public:
        /**
         * @brief Construct a new TestTransform2D object
         */
        TestTransform2D();
        /**
         * @brief Destroy the TestTransform2D object
         */
        virtual ~TestTransform2D();

        /**
         * @copydoc Tests::Test::OnRender
         */
        void OnRender() override;
        /**
         * @copydoc Tests::Test::OnImGuiRender
         */
        void OnImGuiRender() override;

    private:
        // clang-format off
        /**
         * @brief Vertices of a plane
         */
        static inline float s_vertices[32] = {
            // position             // color            // texture coords
            +0.5f, +0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,     // top right
            +0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,     // bottom right
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,     // bottom left
            -0.5f, +0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   0.0f, 1.0f,     // top left
        };
        /**
         * @brief Indices for the plane's vertices
         */
        static inline unsigned int s_indices[6] = {
            0, 1, 2,
            0, 2, 3,
        };
        // clang-format on
        /**
         * @brief Vertex buffer object for the plane
         */
        VBO m_vbo;
        /**
         * @brief The vertex buffer's layout
         */
        VBLayout m_layout;
        /**
         * @brief Element buffer object for the plane's indices
         */
        EBO m_ebo;
        /**
         * @brief Plane's vertex array object
         */
        VAO m_vao;
        /**
         * @brief Shaders to display textures on a plane
         */
        ShaderProgram m_shaderProgram;
        /**
         * @brief A texture do display on a plane
         */
        Texture m_texture1;
        /**
         * @brief A texture do display on a plane
         */
        Texture m_texture2;

        /**
         * @brief How much translation should apply to the transform matrix each time the "Translate" button is pressed
         */
        glm::vec3 m_translation{0.0f, 0.0f, 0.0f};
        /**
         * @brief How much rotation should apply to the transform matrix each time the "Rotate" button is pressed
         */
        float m_rotation = 0.0f;
        /**
         * @brief How much scale should apply to the transform matrix each time the "Scale" button is pressed
         */
        glm::vec3 m_scale{1.0f, 1.0f, 1.0f};
        /**
         * @brief The transform matrix
         */
        glm::mat4 m_transform{1.0f};
    };
} // namespace Tests

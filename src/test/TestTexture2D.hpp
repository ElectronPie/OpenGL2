#pragma once

#include "Test.hpp"

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace Tests
{
    /**
     * @brief Test for textures on 2D objects
     */
    class TestTexture2D: public Test
    {
    public:
        /**
         * @brief Construct a new TestTexture2D object
         */
        TestTexture2D();
        /**
         * @brief Destroy the TestTexture2D object
         */
        virtual ~TestTexture2D();

        /**
         * @copydoc Tests::Test::OnRender
         */
        void OnRender() override;
        /**
         * @copydoc Tests::Test::OnImGuiRender
         */
        void OnImGuiRender() override;
        /**
         * @copydoc Tests::Test::OnUpdate
         */
        void OnUpdate(float deltaTime) override;

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
         * @brief Coefficient for mixing the two textures
         */
        float m_mixCoefficient = 0.0f;
        /**
         * @brief Whether m_mixCoefficient should be set manually
         */
        bool m_checkbox        = true;
    };
} // namespace Tests

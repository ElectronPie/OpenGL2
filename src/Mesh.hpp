#pragma once

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

/**
 * @brief Represents a 3D mesh with vertices, indices, and textures.
 */
class Mesh
{
public:
    /**
     * @brief Represents a vertex in the mesh.
     */
    struct Vertex
    {
        /**
         * @brief Position of the vertex in 3D space.
         */
        glm::vec3 position;
        /**
         * @brief Normal vector of the vertex.
         */
        glm::vec3 normal;
        /**
         * @brief Texture coordinates of the vertex.
         */
        glm::vec2 texCoords;
    };

public:
    /**
     * @brief Construct a new Mesh object with given vertices and indices.
     *
     * @param vertices Vector of vertices.
     * @param indices Vector of indices.
     * @param textures Vector of textures (optional).
     */
    Mesh(
        const std::vector<Mesh::Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        const std::vector<std::shared_ptr<Texture>>& textures = {}
    );
    /**
     * @brief Destroy the Mesh object
     */
    ~Mesh();

    /**
     * @brief Draws the mesh using the provided shader program.
     *
     * @param shaderProgram The shader program to use for rendering the mesh.
     */
    void Draw(const ShaderProgram& shaderProgram) const;

private:
    /**
     * @brief OpenGL vertex buffer object for storing the mesh's vertex data.
     */
    VBO m_vbo;
    /**
     * @brief Vertex buffer layout describing the structure of the vertex data.
     */
    VBLayout m_layout;
    /**
     * @brief OpenGL element buffer object for storing the mesh's index data.
     */
    EBO m_ebo;
    /**
     * @brief OpenGL vertex array object that encapsulates the vertex buffer and element buffer.
     */
    VAO m_vao;
    /**
     * @brief Vector of textures associated with the mesh.
     * Each texture is stored as a shared pointer to allow for shared ownership.
     * This allows multiple meshes to share the same texture without duplicating it.
     * Textures are optional; if no textures are provided, the mesh will render without them.
     */
    std::vector<std::shared_ptr<Texture>> m_textures;
};

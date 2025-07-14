#include "Mesh.hpp"

#include "Renderer.hpp"

Mesh::Mesh(
    const std::vector<Mesh::Vertex>& vertices,
    const std::vector<unsigned int>& indices,
    const std::vector<std::shared_ptr<Texture>>& textures
):
    m_vbo{vertices.data(), (unsigned int)(vertices.size())}, m_ebo{indices.data(), (unsigned int)(indices.size())},
    m_textures{textures}
{
    // Setup vertex buffer layout
    m_layout.Push<float>(3); // position
    m_layout.Push<float>(3); // normal
    m_layout.Push<float>(2); // texCoords

    // Setup VAO
    m_vao.AttachVBO(m_vbo, m_layout);
    m_vao.AttachEBO(m_ebo);
}

Mesh::~Mesh()
{}

void Mesh::Draw(const ShaderProgram& shaderProgram) const
{
    Renderer& r = Renderer::GetInstance();

    // Bind the VAO
    m_vao.Bind();

    unsigned int nrDiffuse  = 0;
    unsigned int nrSpecular = 0;
    for(int i = 0; i < (int)m_textures.size(); ++i)
    {
        // Bind each texture
        m_textures[i]->Bind(i);
        // Increment the texture count based on its type
        switch(m_textures[i]->GetType())
        {
        case Texture::Type::Diffuse:
            shaderProgram.SetUniform1("u_material.diffuse[" + std::to_string(nrDiffuse++) + "]", i);
            break;
        case Texture::Type::Specular:
            shaderProgram.SetUniform1("u_material.specular[" + std::to_string(nrSpecular++) + "]", i);
            break;
        default:
            break;
        }
    }

    // Draw the mesh using the shader program
    r.DrawElements(m_vao, shaderProgram);

    // Unbind the VAO
    m_vao.Unbind();
}

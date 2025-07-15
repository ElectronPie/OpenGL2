#include "Model.hpp"

#include <assimp/postprocess.h>

#include <iostream>
#include <sstream>

std::vector<std::weak_ptr<Texture>> Model::s_loadedTextures;

Model::Model(const std::filesystem::path& modelPath, bool fllipUVs): m_directory{modelPath.parent_path()}
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        modelPath.string(), aiProcess_Triangulate | aiProcess_GenNormals | (aiProcess_FlipUVs * fllipUVs)
    );

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

Model::~Model()
{}

void Model::Draw(const ShaderProgram& shaderProgram) const
{
    for(const auto& pMesh : m_meshes)
    {
        pMesh->Draw(shaderProgram);
    }
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // Process all meshes in this node (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.emplace_back(ProcessMesh(mesh, scene));
    }

    // Then recursively process each child node
    for(unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

std::unique_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    // Process vertices
    vertices.reserve(mesh->mNumVertices);
    for(unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Mesh::Vertex vertex;
        // Process vertex position, normals and texture coordinates
        vertex.position = glm::vec3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex.normal   = glm::vec3{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
        if(mesh->mTextureCoords[0]) // Check if the mesh has texture coordinates
        {
            vertex.texCoords = glm::vec2{mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        }
        else
        {
            vertex.texCoords = glm::vec2{0.0f, 0.0f}; // Set default texture coordinates
        }
        vertices.push_back(vertex);
    }

    // Process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        indices.reserve(indices.size() + face.mNumIndices);
        for(unsigned int j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process materials and textures
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<std::shared_ptr<Texture>> diffuseMaps =
            LoadMaterialTextures(material, aiTextureType_DIFFUSE, Texture::Type::Diffuse);
        textures.insert(
            textures.end(), std::make_move_iterator(diffuseMaps.begin()), std::make_move_iterator(diffuseMaps.end())
        );
        std::vector<std::shared_ptr<Texture>> specularMaps =
            LoadMaterialTextures(material, aiTextureType_SPECULAR, Texture::Type::Specular);
        textures.insert(
            textures.end(), std::make_move_iterator(specularMaps.begin()), std::make_move_iterator(specularMaps.end())
        );
    }

    return std::make_unique<Mesh>(vertices, indices, textures);
}

std::vector<std::shared_ptr<Texture>> Model::LoadMaterialTextures(
    aiMaterial* material, aiTextureType inType, Texture::Type outType
)
{
    std::vector<std::shared_ptr<Texture>> textures;
    for(unsigned int i = 0; i < material->GetTextureCount(inType); ++i)
    {
        aiString str;
        material->GetTexture(inType, i, &str);
        bool skip = false;

        // Check if the texture is already loaded
        for(const auto& wpTexture : s_loadedTextures)
        {
            auto pTexture = wpTexture.lock();
            if(!pTexture)
            {
                continue; // Skip expired weak pointers
            }
            if(pTexture->GetName() == str.C_Str() && pTexture->GetType() == outType)
            {
                textures.push_back(pTexture);
                if(std::find(m_textures.begin(), m_textures.end(), pTexture) == m_textures.end())
                {
                    m_textures.push_back(pTexture);
                }
                skip = true;
                break;
            }
        }

        if(!skip)
        {
            auto pTexture = std::make_shared<Texture>(m_directory / str.C_Str(), outType);
            textures.push_back(pTexture);
            // Store the texture to avoid duplicates
            m_textures.push_back(pTexture);
            s_loadedTextures.emplace_back(pTexture);
        }
    }

    // Clean up expired weak pointers
    s_loadedTextures.erase(
        std::remove_if(
            s_loadedTextures.begin(),
            s_loadedTextures.end(),
            [](const std::weak_ptr<Texture>& wpTexture) { return wpTexture.expired(); }
        ),
        s_loadedTextures.end()
    );

    return textures;
}

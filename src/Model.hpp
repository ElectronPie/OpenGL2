#pragma once

#include "ShaderProgram.hpp"
#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <filesystem>
#include <vector>

/**
 * @brief Represents a 3D model loaded from a file.
 */
class Model
{
public:
    /**
     * @brief Construct a new Model object from a file.
     *
     * @param modelPath Path to the model file.
     * @param flipUVs Whether to flip the UV coordinates (default is false).
     */
    Model(const std::filesystem::path& modelPath, bool flipUVs = false);
    /**
     * @brief Destroy the Model object.
     */
    ~Model();

    /**
     * @brief Draw the model using the provided shader program.
     *
     * @param shaderProgram
     */
    void Draw(const ShaderProgram& shaderProgram) const;

private:
    /**
     * @brief Directory where the model file is located.
     */
    std::filesystem::path m_directory;
    /**
     * @brief Meshes that the model contains.
     */
    std::vector<std::unique_ptr<Mesh>> m_meshes;
    /**
     * @brief Vector of loaded textures belonging to the model.
     */
    std::vector<std::shared_ptr<Texture>> m_textures;
    /**
     * @brief Static vector to store loaded textures.
     */
    static std::vector<std::weak_ptr<Texture>> s_loadedTextures;

private:
    /**
     * @brief Process a node in the model's scene graph.
     *
     * @param node Assimp node to process.
     * @param scene Assimp scene containing the node.
     */
    void ProcessNode(aiNode* node, const aiScene* scene);
    /**
     * @brief Process a mesh in the model's scene.
     *
     * @param mesh Assimp mesh to process.
     * @param scene Assimp scene containing the mesh.
     * @return std::unique_ptr<Mesh> Processed mesh.
     */
    std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
    /**
     * @brief Load textures from a material.
     *
     * @param material Assimp material to load textures from.
     * @param inTtype Assimp texture type to load.
     * @param outType Texture type to assign to the loaded textures.
     * @return std::vector<Texture> A vector of textures loaded from the material.
     */
    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(
        aiMaterial* material, aiTextureType inTtype, Texture::Type outType
    );
};

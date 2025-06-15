#pragma once

#include "Texture.hpp"

#include <glm/glm.hpp>

#include <optional>
#include <variant>

class Material
{
public:
    /**
     * @brief Construct a new Material object
     *
     * @param diffuse Path to a diffuse map texture file or a vec3 diffusion value
     * @param specular Path to a specular map texture file or a vec3 specular value
     * @param emission Path to a emission map texture file or a vec3 emission value
     * @param shininess Shininess value
     */
    Material(
        const std::variant<std::filesystem::path, glm::vec3> diffuse,
        const std::variant<std::filesystem::path, glm::vec3> specular,
        const std::variant<std::filesystem::path, glm::vec3> emission,
        float shininess,
        const std::optional<glm::vec3> ambient = std::nullopt
    );
    /**
     * @brief Destroy the Material object
     */
    ~Material();

public:
    // Material attributes
    std::optional<glm::vec3> ambient;
    std::variant<Texture, glm::vec3> diffuse = glm::vec3{0.0f};
    std::variant<Texture, glm::vec3> specular = glm::vec3{0.0f};
    std::variant<Texture, glm::vec3> emission = glm::vec3{0.0f};
    float shininess;
};

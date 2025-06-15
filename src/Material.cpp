#include "Material.hpp"

Material::Material(
    const std::variant<std::filesystem::path, glm::vec3> diffuse,
    const std::variant<std::filesystem::path, glm::vec3> specular,
    const std::variant<std::filesystem::path, glm::vec3> emission,
    float shininess,
    const std::optional<glm::vec3> ambient
)
{
    if(std::holds_alternative<glm::vec3>(diffuse))
    {
        this->diffuse = std::get<glm::vec3>(diffuse);
    }
    else
    {
        this->diffuse = Texture{std::get<std::filesystem::path>(diffuse)};
    }

    if(std::holds_alternative<glm::vec3>(specular))
    {
        this->specular = std::get<glm::vec3>(specular);
    }
    else
    {
        this->specular = Texture{std::get<std::filesystem::path>(specular)};
    }

    if(std::holds_alternative<glm::vec3>(emission))
    {
        this->emission = std::get<glm::vec3>(emission);
    }
    else
    {
        this->emission = Texture{std::get<std::filesystem::path>(emission)};
    }

    this->shininess = shininess;

    this->ambient = ambient;
}

Material::~Material()
{}

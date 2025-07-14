#pragma once

#include <filesystem>

/**
 * @brief Represents a 2D OpenGL texture
 */
class Texture
{
public:
    enum class Type
    {
        None = 0,
        Diffuse,
        Specular,
    };

public:
    /**
     * @brief Construct a new Texture object
     *
     * @param texturePath path to the image file
     */
    Texture(const std::filesystem::path& texturePath, Type type = Type::None);
    /**
     * @brief Destroy the Texture object
     */
    ~Texture();

    Texture(Texture&& other);
    Texture& operator=(Texture&& other);

    /**
     * @brief Bind the texture
     *
     * @param location Slot number to bind to
     */
    void Bind(unsigned int location = 0) const noexcept;
    /**
     * @brief Unbind the texture
     */
    void Unbind() const noexcept;

    /**
     * @brief Get the texture's type
     *
     * @return * Type
     */
    inline Type GetType() const noexcept
    {
        return m_type;
    }

    /**
     * @brief Get the texture image file path
     *
     * @return std::filesystem::path
     */
    inline const std::string& GetName() const noexcept
    {
        return m_name;
    }

private:
    /**
     * @brief OpenGL texture ID
     */
    unsigned int m_rendererID = 0;
    /**
     * @brief Type of the texture
     */
    Type m_type               = Type::None;
    /**
     * @brief Texture image file name
     */
    std::string m_name;
};

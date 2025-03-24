#pragma once

#include <filesystem>

/**
 * @brief Represents a 2D OpenGL texture
 *
 */
class Texture
{
public:
    /**
     * @brief Construct a new Texture object
     *
     * @param texturePath path to the image file
     */
    Texture(const std::filesystem::path& texturePath);
    /**
     * @brief Destroy the Texture object
     *
     */
    ~Texture();

    /**
     * @brief Bind the texture
     *
     * @param location Slot number to bind to
     */
    void Bind(unsigned int location = 0) const noexcept;
    /**
     * @brief Unbind the texture
     *
     */
    void Unbind() const noexcept;

private:
    /**
     * @brief OpenGL texture ID
     *
     */
    unsigned int m_rendererID = 0;
};

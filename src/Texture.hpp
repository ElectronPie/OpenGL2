#pragma once

#include "Renderer.hpp"

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

    enum class WrapMode
    {
        ClampToEdge    = GL_CLAMP_TO_EDGE,
        ClampToBorder  = GL_CLAMP_TO_BORDER,
        Repeat         = GL_REPEAT,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        //MirrorClampToBorder = GL_MIRROR_CLAMP_TO_BORDER,
    };

    enum class FilterFunction
    {
        Nearest              = GL_NEAREST,
        Linear               = GL_LINEAR,
        NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST,
        NearestMipMapLinear  = GL_NEAREST_MIPMAP_LINEAR,
        LinearMipMapNearest  = GL_LINEAR_MIPMAP_NEAREST,
        LinearMipMapLinear   = GL_LINEAR_MIPMAP_LINEAR,
    };

public:
    /**
     * @brief Construct a new Texture object
     *
     * @param texturePath path to the image file
     * @param wrapModeS Horizontal wrap mode
     * @param wrapModeT Vertical wrap mode
     * @param minFilter Minimization filter function (also controls MipMaps)
     * @param magFilter Magnification filter function
     */
    Texture(
        const std::filesystem::path& texturePath,
        Type type                = Type::None,
        WrapMode wrapModeS       = WrapMode::Repeat,
        WrapMode wrapModeT       = WrapMode::Repeat,
        FilterFunction minFilter = FilterFunction::LinearMipMapLinear,
        FilterFunction magFilter = FilterFunction::Linear
    );
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

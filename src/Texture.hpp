#pragma once

#include "Renderer.hpp"

#include "Format.hpp"

#include <filesystem>

/**
 * @brief Represents a 2D OpenGL texture
 */
class Texture
{
    friend class FBO;

public:
    /**
     * @brief Intended use of texture
     */
    enum class Type
    {
        None = 0, ///< Any texture
        Diffuse,  ///< Diffuse texture
        Specular, ///< Specular texture
    };

    /**
     * @brief Texture wrap mode to use when texel coordinate lands outside the texture
     */
    enum class WrapMode
    {
        ClampToEdge    = GL_CLAMP_TO_EDGE,
        ClampToBorder  = GL_CLAMP_TO_BORDER,
        Repeat         = GL_REPEAT,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        //MirrorClampToBorder = GL_MIRROR_CLAMP_TO_BORDER,
    };

    /**
     * @brief Filter function to use when texel coordinate lands in between actual texels
     * (Also controls mipmaps)
     */
    enum class FilterFunction
    {
        Nearest              = GL_NEAREST,
        Linear               = GL_LINEAR,
        NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
        NearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
        LinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
        LinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR,
    };

public:
    /**
     * @brief Construct a new Texture object
     *
     * @param width Texture width (-1 means use Viewport width)
     * @param height Texture height (-1 means use Viewport height)
     * @param type Intended use of the texture
     * @param wrapModeS Horizontal wrap mode
     * @param wrapModeT Vertical wrap mode
     * @param minFilter Minimization filter function (also controls Mipmaps)
     * @param magFilter Magnification filter function
     * @param internalFormat Internal format of the image data
     * @param generateMipmap Whether to generate a mipmap
     */
    Texture(
        int width                  = -1,
        int height                 = -1,
        Type type                  = Type::None,
        WrapMode wrapModeS         = WrapMode::Repeat,
        WrapMode wrapModeT         = WrapMode::Repeat,
        FilterFunction minFilter   = FilterFunction::Linear,
        FilterFunction magFilter   = FilterFunction::Linear,
        ImageFormat internalFormat = ImageFormat::RGBA,
        bool generateMipmap        = false
    );
    /**
     * @brief Construct a new Texture from an image file
     *
     * @param texturePath path to the image file
     * @param type Intended use of the texture
     * @param wrapModeS Horizontal wrap mode
     * @param wrapModeT Vertical wrap mode
     * @param minFilter Minimization filter function (also controls Mipmaps)
     * @param magFilter Magnification filter function
     * @param internalFormat Internal format of the image data
     * @param generateMipmap Whether to generate a mipmap
     */
    Texture(
        const std::filesystem::path& texturePath,
        Type type                  = Type::None,
        WrapMode wrapModeS         = WrapMode::Repeat,
        WrapMode wrapModeT         = WrapMode::Repeat,
        FilterFunction minFilter   = FilterFunction::LinearMipmapLinear,
        FilterFunction magFilter   = FilterFunction::Linear,
        ImageFormat internalFormat = ImageFormat::RGBA,
        bool generateMipmap        = true
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
     * @brief Texture Constructors' common functionality
     *
     * @param data Raw image data
     * @param width Texture width (default value of -1 for Viewport width)
     * @param height Texture height (default value of -1 for Viewport height)
     * @param type Intended use of the texture
     * @param wrapModeS Horizontal wrap mode
     * @param wrapModeT Vertical wrap mode
     * @param minFilter Minimization filter function (also controls Mipmaps)
     * @param magFilter Magnification filter function
     * @param internalFormat Internal format of the image data
     * @param generateMipmap Whether to generate a mipmap
     */
    void InitializeTexture(
        void* data,
        int width,
        int height,
        Type type,
        WrapMode wrapModeS,
        WrapMode wrapModeT,
        FilterFunction minFilter,
        FilterFunction magFilter,
        ImageFormat internalFormat,
        bool generateMipmap
    );

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

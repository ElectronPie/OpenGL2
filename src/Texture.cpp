#include "Texture.hpp"

#include "Renderer.hpp"

extern "C"
{
#include <stb_image.h>
}

#include <iostream>

Texture::Texture(
    const std::filesystem::path& texturePath,
    Texture::Type type,
    Texture::WrapMode wrapModeS,
    Texture::WrapMode wrapModeT,
    Texture::FilterFunction minFilter,
    Texture::FilterFunction magFilter,
    ImageFormat internalFormat,
    bool generateMipmap
): m_rendererID{0}, m_type{type}, m_name{texturePath.filename().string()}
{
    // Load the image
    int width, height, numChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath.string().c_str(), &width, &height, &numChannels, 4);
    if(data)
    {
        InitializeTexture(
            data, width, height, type, wrapModeS, wrapModeT, minFilter, magFilter, internalFormat, generateMipmap
        );
    }
    else
    {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
        debug_break();
    }
    stbi_image_free(data);
}

Texture::Texture(
    int width,
    int height,
    Texture::Type type,
    Texture::WrapMode wrapModeS,
    Texture::WrapMode wrapModeT,
    Texture::FilterFunction minFilter,
    Texture::FilterFunction magFilter,
    ImageFormat internalFormat,
    bool generateMipmap
): m_rendererID{0}, m_type{type}
{
    Renderer& r   = Renderer::GetInstance();
    auto [vw, vh] = r.GetViewportSize();
    if(width == -1)
        width = vw;
    if(height == -1)
        height = vh;

    InitializeTexture(
        nullptr, width, height, type, wrapModeS, wrapModeT, minFilter, magFilter, internalFormat, generateMipmap
    );
}

void Texture::InitializeTexture(
    void* data,
    int width,
    int height,
    Texture::Type type,
    Texture::WrapMode wrapModeS,
    Texture::WrapMode wrapModeT,
    Texture::FilterFunction minFilter,
    Texture::FilterFunction magFilter,
    ImageFormat internalFormat,
    bool generateMipmap
)
{
    GLCall(glGenTextures(1, &m_rendererID));
    Bind();

    // Set the texture wrapping/filtering options
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(wrapModeS)));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(wrapModeT)));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(minFilter)));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(magFilter)));

    GLCall(glTexImage2D(
        GL_TEXTURE_2D, 0, static_cast<GLenum>(internalFormat), width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
    ));
    if(generateMipmap)
    {
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }
}

Texture::~Texture() noexcept
{
    GLCall(glDeleteTextures(1, &m_rendererID));
}

Texture::Texture(Texture&& other)
{
    m_rendererID = other.m_rendererID;

    other.m_rendererID = 0;
}

Texture& Texture::operator=(Texture&& other)
{
    m_rendererID = other.m_rendererID;

    other.m_rendererID = 0;

    return *this;
}

void Texture::Bind(unsigned int location) const noexcept
{
    GLCall(glActiveTexture(GL_TEXTURE0 + location));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::Unbind() const noexcept
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

#include "Texture.hpp"

#include "Renderer.hpp"

#include <stb_image.h>

#include <iostream>

Texture::Texture(const std::filesystem::path& texturePath)
{
    GLCall(glGenTextures(1, &m_rendererID));
    Bind();

    // Set the texture wrapping/filtering options
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // Load and generate the texture
    int width, height, numChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &numChannels, 4);
    if(data)
    {
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
        debug_break();
    }
    stbi_image_free(data);
}

Texture::~Texture()
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

#pragma once

#include <filesystem>

class Texture
{
public:
    Texture(const std::filesystem::path& texturePath);
    ~Texture();

    void Bind(unsigned int location = 0) const noexcept;
    void Unbind() const noexcept;

private:
    unsigned int m_rendererID = 0;
};

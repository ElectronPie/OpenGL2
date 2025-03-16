#include "VBO.hpp"

#include "Renderer.hpp"

VBO::VBO(const void* data, std::size_t size)
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &m_rendererID);
}

void VBO::Bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VBO::Unbind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#include "VBO.hpp"

#include "Renderer.hpp"

VBO::VBO(const void* data, std::size_t size)
{
    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VBO::~VBO()
{
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void VBO::Bind() const noexcept
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VBO::Unbind() const noexcept
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

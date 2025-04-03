#include "VBO.hpp"

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

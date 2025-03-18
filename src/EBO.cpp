#include "EBO.hpp"

EBO::~EBO()
{
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void EBO::Bind() const noexcept
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void EBO::Unbind() const noexcept
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

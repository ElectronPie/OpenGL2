#include "EBO.hpp"

EBO::~EBO()
{
    glDeleteBuffers(1, &m_rendererID);
}

void EBO::Bind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void EBO::Unbind() const noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

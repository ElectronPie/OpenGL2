#include "VBO.hpp"

VBO::~VBO()
{
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

VBO::VBO(VBO&& other)
{
    m_rendererID = other.m_rendererID;
    m_count      = other.m_count;

    other.m_rendererID = 0;
}

VBO& VBO::operator=(VBO&& other)
{
    m_rendererID = other.m_rendererID;
    m_count      = other.m_count;

    other.m_rendererID = 0;

    return *this;
}

void VBO::Bind() const noexcept
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VBO::Unbind() const noexcept
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

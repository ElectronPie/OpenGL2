#include "EBO.hpp"

EBO::~EBO()
{
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

EBO::EBO(EBO&& other)
{
    m_rendererID = other.m_rendererID;
    m_count      = other.m_count;
    m_dataType   = other.m_dataType;

    other.m_rendererID = 0;
}

EBO& EBO::operator=(EBO&& other)
{
    m_rendererID = other.m_rendererID;
    m_count      = other.m_count;
    m_dataType   = other.m_dataType;

    other.m_rendererID = 0;

    return *this;
}

void EBO::Bind() const noexcept
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void EBO::Unbind() const noexcept
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

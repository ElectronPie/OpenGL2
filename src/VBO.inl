#include "Renderer.hpp"

template<typename T>
VBO::VBO(const T* data, unsigned int count)
{
    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW));
    m_count = count;
}

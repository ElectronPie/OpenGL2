#include "Renderer.hpp"

#include <type_traits>

template<typename T>
EBO::EBO(const T* data, unsigned int count)
{
    if constexpr(std::is_same_v<T, unsigned int>)
    {
        m_dataType = GL_UNSIGNED_INT;
    }
    else if constexpr(std::is_same_v<T, unsigned short>)
    {
        m_dataType = GL_UNSIGNED_SHORT;
    }
    else if constexpr(std::is_same_v<T, unsigned char>)
    {
        m_dataType = GL_UNSIGNED_BYTE;
    }
    else
    {
        static_assert(false);
    }
    m_count = count;
    GLCall(glGenBuffers(1, &m_rendererID));
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW));
}

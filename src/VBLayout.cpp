#include "VBLayout.hpp"

#include "Renderer.hpp"

unsigned int VBElement::GetTypeSize(GLenum type) noexcept
{
    switch(type)
    {
    case GL_FLOAT:
        return sizeof(float);
    case GL_DOUBLE:
        return sizeof(double);
    case GL_UNSIGNED_INT:
        return sizeof(unsigned int);
    case GL_INT:
        return sizeof(int);
    case GL_UNSIGNED_SHORT:
        return sizeof(unsigned short);
    case GL_SHORT:
        return sizeof(short);
    case GL_UNSIGNED_BYTE:
        return sizeof(unsigned char);
    case GL_BYTE:
        return sizeof(char);
    }
    return 0;
}

VBLayout::VBLayout()
{}

VBLayout::~VBLayout()
{}

template<typename T>
void VBLayout::Push(unsigned int count)
{
    static_assert(false, "Not a defined vertex buffer layout element type");
}

template<>
void VBLayout::Push<float>(unsigned int count)
{
    ASSERT(count > 0);
    ASSERT(count <= 4);
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * VBElement::GetTypeSize(GL_FLOAT);
}

template<>
void VBLayout::Push<double>(unsigned int count)
{
    ASSERT(count > 0);
    ASSERT(count <= 4);
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * VBElement::GetTypeSize(GL_FLOAT);
}

template<>
void VBLayout::Push<unsigned int>(unsigned int count)
{
    ASSERT(count > 0);
    ASSERT(count <= 4);
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += count * VBElement::GetTypeSize(GL_UNSIGNED_INT);
}

template<>
void VBLayout::Push<int>(unsigned int count)
{
    ASSERT(count > 0);
    ASSERT(count <= 4);
    m_elements.push_back({GL_INT, count, GL_FALSE});
    m_stride += count * VBElement::GetTypeSize(GL_INT);
}

template<>
void VBLayout::Push<unsigned short>(unsigned int count)
{
    ASSERT(count > 0);
    ASSERT(count <= 4);
    m_elements.push_back({GL_UNSIGNED_SHORT, count, GL_FALSE});
    m_stride += count * VBElement::GetTypeSize(GL_UNSIGNED_SHORT);
}

template<>
void VBLayout::Push<short>(unsigned int count)
{
    ASSERT(count > 0);
    ASSERT(count <= 4);
    m_elements.push_back({GL_SHORT, count, GL_FALSE});
    m_stride += count * VBElement::GetTypeSize(GL_SHORT);
}

template<>
void VBLayout::Push<unsigned char>(unsigned int count)
{
    ASSERT(count > 0);
    ASSERT(count <= 4);
    m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_FALSE});
    m_stride += count * VBElement::GetTypeSize(GL_UNSIGNED_BYTE);
}

template<>
void VBLayout::Push<char>(unsigned int count)
{
    ASSERT(count > 0);
    ASSERT(count <= 4);
    m_elements.push_back({GL_BYTE, count, GL_FALSE});
    m_stride += count * VBElement::GetTypeSize(GL_BYTE);
}

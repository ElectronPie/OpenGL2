#include "VAO.hpp"

#include "Renderer.hpp"

VAO::VAO()
{
    GLCall(glGenVertexArrays(1, &m_rendererID));
}

VAO::~VAO()
{
    GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

VAO::VAO(VAO&& other)
{
    m_rendererID       = other.m_rendererID;
    m_verticesCount    = other.m_verticesCount;
    m_elementsCount    = other.m_elementsCount;
    m_elementsDataType = other.m_elementsDataType;

    other.m_rendererID = 0;
}

VAO& VAO::operator=(VAO&& other)
{
    m_rendererID       = other.m_rendererID;
    m_verticesCount    = other.m_verticesCount;
    m_elementsCount    = other.m_elementsCount;
    m_elementsDataType = other.m_elementsDataType;

    other.m_rendererID = 0;
}

void VAO::Bind() const noexcept
{
    GLCall(glBindVertexArray(m_rendererID));
}

void VAO::Unbind() const noexcept
{
    GLCall(glBindVertexArray(0));
}

void VAO::AttachVBO(const VBO& vbo, const VBLayout& layout) noexcept
{
    Bind();
    vbo.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset  = 0;
    for(unsigned int i = 0; i < elements.size(); ++i)
    {
        const auto& element = elements[i];
        GLCall(glVertexAttribPointer(
            i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(uintptr_t)offset
        ));
        GLCall(glEnableVertexAttribArray(i));
        offset += element.count * VBElement::GetTypeSize(element.type);
    }
    m_verticesCount = vbo.GetCount();
}

void VAO::AttachEBO(const EBO& ebo) noexcept
{
    Bind();
    ebo.Bind();
    m_elementsDataType = ebo.GetDataType();
    m_elementsCount    = ebo.GetCount();
}

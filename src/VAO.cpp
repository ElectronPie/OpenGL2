#include "VAO.hpp"

#include "Renderer.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &m_rendererID);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_rendererID);
}

void VAO::Bind() const noexcept
{
    glBindVertexArray(m_rendererID);
}

void VAO::Unbind() const noexcept
{
    glBindVertexArray(0);
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
        glVertexAttribPointer(
            i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(uintptr_t)offset
        );
        glEnableVertexAttribArray(i);
        offset += element.count * VBElement::GetTypeSize(element.type);
    }
}

void VAO::AttachEBO(const EBO& ebo) noexcept
{
    Bind();
    ebo.Bind();
    m_elementsDataType = ebo.GetDataType();
    m_elementsCount    = ebo.GetCount();
}

#pragma once

#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"

/**
 * @brief Represents a OpenGL vertex array object
 *
 */
class VAO
{
public:
    /**
     * @brief Construct a new VAO object
     *
     */
    VAO();
    /**
     * @brief Destroy the VAO object
     *
     */
    ~VAO();

    /**
     * @brief Bind the VAO
     *
     */
    void Bind() const noexcept;
    /**
     * @brief Unbind the VAO
     *
     */
    void Unbind() const noexcept;

    /**
     * @brief Attach a VBO to a VAO
     *
     * @param vbo vertex buffer object
     * @param layout vertex buffer layout
     */
    void AttachVBO(const VBO& vbo, const VBLayout& layout) noexcept;
    /**
     * @brief Attach a EBO to a VAO
     *
     * @param ebo element buffer object
     */
    void AttachEBO(const EBO& ebo) noexcept;

    /**
     * @brief Get the OpenGL enum for the underlying type of data in the attached element buffer
     *
     * @return unsigned int
     */
    inline unsigned int GetElementsDataType() const noexcept
    {
        return m_elementsDataType;
    }

    /**
     * @brief Get the number of elements in the attached element buffer
     *
     * @return unsigned int
     */
    inline unsigned int GetElementsCount() const noexcept
    {
        return m_elementsCount;
    }

private:
    /**
     * @brief OpenGL vertex array object ID
     *
     */
    unsigned int m_rendererID = 0;
    /**
     * @brief OpenGL enum for the underlying type of data in the attached element buffer
     *
     */
    unsigned int m_elementsDataType;
    /**
     * @brief Number of elements in the attached element buffer
     *
     */
    unsigned int m_elementsCount = 0;
};

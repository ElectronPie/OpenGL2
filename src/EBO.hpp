#pragma once

/**
 * @brief Represents a OpenGL element buffer object
 */
class EBO
{
public:
    /**
     * @brief Construct a new EBO object
     *
     * @tparam T type of underlying data
     * @param data Pointer to raw vertex intex data
     * @param count Number of elements in the buffer
     */
    template<typename T>
    EBO(const T* data, unsigned int count);
    /**
     * @brief Destroy the EBO object
     */
    ~EBO();

    /**
     * @brief Bind the EBO
     */
    void Bind() const noexcept;
    /**
     * @brief Unbind the EBO
     */
    void Unbind() const noexcept;

    /**
     * @brief Get the OpenGL enum for the underlying typ of data in the element buffer
     *
     * @return unsigned int
     */
    inline unsigned int GetDataType() const noexcept
    {
        return m_dataType;
    }

    /**
     * @brief Get the number of elements in the element buffer
     *
     * @return unsigned int
     */
    inline unsigned int GetCount() const noexcept
    {
        return m_count;
    }

private:
    /**
     * @brief OpenGL buffer ID
     */
    unsigned int m_rendererID = 0;
    /**
     * @brief OpenGL enum for the underlying type of data in the element buffer
     */
    unsigned int m_dataType;
    /**
     * @brief Number of elements in the element buffer
     */
    unsigned int m_count = 0;
};

#include "EBO.inl"

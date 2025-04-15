#pragma once

#include <cstddef>

/**
 * @brief Represents a OpenGL vertex buffer object
 */
class VBO
{
public:
    /**
     * @brief Construct a new VBO object
     *
     * @tparam T Type of underlying data
     * @param data Pointer to raw vertex data
     * @param count Number of elements in the buffer
     */
    template<typename T>
    VBO(const T* data, unsigned int count);
    /**
     * @brief Destroy the VBO object
     */
    ~VBO();

    VBO(VBO&& other);
    VBO& operator=(VBO&& other);

    /**
     * @brief Bind the VBO
     */
    void Bind() const noexcept;
    /**
     * @brief Unbind the VBO
     */
    void Unbind() const noexcept;

    /**
     * @brief Get the nuumber of vertices stored in the VBO
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
     * @brief Number of vertices in the VBO
     */
    unsigned int m_count      = 0;
};

#include "VBO.inl"

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
     * @param data Pointer to raw vertex data
     * @param size Size of data
     */
    VBO(const void* data, std::size_t size);
    /**
     * @brief Destroy the VBO object
     */
    ~VBO();

    /**
     * @brief Bind the VBO
     */
    void Bind() const noexcept;
    /**
     * @brief Unbind the VBO
     */
    void Unbind() const noexcept;

private:
    /**
     * @brief OpenGL buffer ID
     */
    unsigned int m_rendererID = 0;
};

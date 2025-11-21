#pragma once

#include "Format.hpp"

/**
 * @brief Represents a OpenGL renderbuffer object
 */
class RBO
{
    friend class FBO;

public:
    /**
     * @brief Construct a new RBO object
     *
     * @param width Rebderbuffer width (-1 means use Viewport width)
     * @param height Renderbuffer height (-1 means use Viewport height)
     * @param internalformat Renderbuffer internal format
     */
    RBO(int width = -1, int height = -1, ImageFormat internalformat = ImageFormat::Depth24Stencil8);
    /**
     * @brief Destroy the RBO object
     */
    ~RBO() noexcept;

    /**
     * @brief Bind the RBO
     */
    void Bind() const noexcept;
    /**
     * @brief Unbind the RBO
     */
    void Unbind() const noexcept;

private:
    /**
     * @brief OpenGL renderbuffer ID
     */
    unsigned int m_rendererID = 0;
};

#pragma once

#include "Renderer.hpp"

#include "Texture.hpp"
#include "RBO.hpp"

#include <memory>

/**
 * @brief Represents a OpenGL framebuffer object
 */
class FBO
{
public:
    /**
     * @brief Construct a new FBO object
     */
    FBO();
    /**
     * @brief Destroy the FBO object
     */
    ~FBO();

    FBO(FBO&& other);
    FBO& operator=(FBO&& other);

    /**
     * @brief Framebuffer bind targets
     */
    enum class BindTarget
    {
        Read      = GL_READ_FRAMEBUFFER,
        Write     = GL_DRAW_FRAMEBUFFER,
        ReadWrite = GL_FRAMEBUFFER,
    };

    /**
     * @brief Bind the FBO
     */
    void Bind(BindTarget target = BindTarget::ReadWrite) const noexcept;
    /**
     * @brief Unbind the FBO
     */
    void Unbind(BindTarget target = BindTarget::ReadWrite) const noexcept;

    /**
     * @brief Framebuffer status
     */
    enum class Status
    {
        Complete                    = GL_FRAMEBUFFER_COMPLETE,
        Undefined                   = GL_FRAMEBUFFER_UNDEFINED,
        IncompleteAttachment        = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
        IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
        IncompleteDrawBuffer        = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
        IncompleteReadBuffer        = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
        Unsupported                 = GL_FRAMEBUFFER_UNSUPPORTED,
        IncompleteMultisample       = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
        IncompleteLayerTargets      = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
    };
    /**
     * @brief Check the framebuffer status
     *
     * @return Status
     */
    Status GetStatus(BindTarget target = BindTarget::ReadWrite) const noexcept;
    /**
     * @brief Check if the framebuffer is complete
     *
     * @param target Framebuffer bind target
     * @return bool Whether the framebuffer is complete
     */
    bool operator()(BindTarget target = BindTarget::ReadWrite) const noexcept;

    /**
     * @brief Framebuffer attachment points
     */
    enum class Attachment
    {
        Color        = GL_COLOR_ATTACHMENT0,
        Depth        = GL_DEPTH_ATTACHMENT,
        Stencil      = GL_STENCIL_ATTACHMENT,
        DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,
    };
    /**
     * @brief Attach a texture to the framebuffer
     *
     * @param texture Texture to attach
     * @param attachment Attachment point
     * @param colorAttachmentIdx Color attachment index (only used if attachment is Color)
     * @param target Framebuffer bind target
     */
    void AttachTexture(
        const Texture& texture,
        Attachment attachment,
        unsigned int colorAttachmentIdx = 0,
        BindTarget target               = BindTarget::ReadWrite
    ) noexcept;
    /**
     * @brief Attach a renderbuffer to the framebuffer
     *
     * @param texture Renderbuffer to attach
     * @param attachment Attachment point
     * @param colorAttachmentIdx Color attachment index (only used if attachment is Color)
     * @param target Framebuffer bind target
     */
    void AttachRenderbuffer(
        const RBO& rbo,
        Attachment attachment,
        unsigned int colorAttachmentIdx = 0,
        BindTarget target               = BindTarget::ReadWrite
    ) noexcept;

private:
    /**
     * @brief OpenGL framebuffer ID
     */
    unsigned int m_rendererID = 0;
};

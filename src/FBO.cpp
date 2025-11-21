#include "FBO.hpp"

FBO::FBO()
{
    GLCall(glGenFramebuffers(1, &m_rendererID));
}

FBO::~FBO()
{
    GLCall(glDeleteFramebuffers(1, &m_rendererID));
}

FBO::FBO(FBO&& other)
{
    m_rendererID = other.m_rendererID;

    other.m_rendererID = 0;
}

FBO& FBO::operator=(FBO&& other)
{
    m_rendererID = other.m_rendererID;

    other.m_rendererID = 0;

    return *this;
}

void FBO::Bind(BindTarget target) const noexcept
{
    GLCall(glBindFramebuffer(static_cast<GLuint>(target), m_rendererID));
}

void FBO::Unbind(BindTarget target) const noexcept
{
    GLCall(glBindFramebuffer(static_cast<GLuint>(target), 0));
}

FBO::Status FBO::GetStatus(BindTarget target) const noexcept
{
    GLCall(auto status = static_cast<FBO::Status>(glCheckFramebufferStatus(static_cast<GLenum>(target))));
    return status;
}

bool FBO::operator()(BindTarget target) const noexcept
{
    return GetStatus(target) == Status::Complete;
}

void FBO::AttachTexture(
    const Texture& texture, Attachment attachment, unsigned int colorAttachmentIdx, BindTarget target
) noexcept
{
    Bind();
    GLenum att = static_cast<GLenum>(attachment) + ((attachment == Attachment::Color) ? colorAttachmentIdx : 0);
    GLCall(glFramebufferTexture2D(static_cast<GLenum>(target), att, GL_TEXTURE_2D, texture.m_rendererID, 0));
}

void FBO::AttachRenderbuffer(
    const RBO& rbo, Attachment attachment, unsigned int colorAttachmentIdx, BindTarget target
) noexcept
{
    Bind();
    GLenum att = static_cast<GLenum>(attachment) + ((attachment == Attachment::Color) ? colorAttachmentIdx : 0);
    GLCall(glFramebufferRenderbuffer(static_cast<GLenum>(target), att, GL_RENDERBUFFER, rbo.m_rendererID));
}

#include "RBO.hpp"

RBO::RBO(int width, int height, ImageFormat internalformat)
{
    GLCall(glGenRenderbuffers(1, &m_rendererID));
    Bind();

    Renderer& r   = Renderer::GetInstance();
    auto [vw, vh] = r.GetViewportSize();
    if(width == -1)
        width = vw;
    if(height == -1)
        height = vh;

    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(internalformat), width, height));
}

RBO::~RBO()
{
    GLCall(glDeleteRenderbuffers(1, &m_rendererID));
}

void RBO::Bind() const noexcept
{
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rendererID));
}

void RBO::Unbind() const noexcept
{
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

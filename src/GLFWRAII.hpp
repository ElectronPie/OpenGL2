#pragma once

class GLFWRAII
{
public:
    GLFWRAII();

    ~GLFWRAII() noexcept;

    inline operator bool() const noexcept
    {
        return m_initialized;
    }

private:
    bool m_initialized;
};

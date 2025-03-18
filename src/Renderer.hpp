#pragma once

#include <debugbreak.h>
#include <glad/glad.h>

// Forward declarations
namespace std
{
    template<typename T>
    class shared_ptr;
}
class GLFWRAII;
class VAO;
class ShaderProgram;
struct GLFWwindow;

#ifdef DEBUG
    #define ASSERT(x)      \
        if(!(x))           \
        {                  \
            debug_break(); \
        }
#else
    #define ASSERT(x)
#endif

#if defined(DEBUG) && !defined(ENABLE_FANCY_DEBUG_OUTPUT)
    #define GLCall(x)    \
        GLClearErrors(); \
        x;               \
        ASSERT(GLCheckError(#x, __FILE__, __LINE__))
#else
    #define GLCall(x) x
#endif

#if defined(DEBUG) && !defined(ENABLE_FANCY_DEBUG_OUTPUT)
void GLClearErrors();

bool GLCheckError(const char* function, const char* file, int line);
#endif

/**
 * @brief Represents the OpenGL renderer along with a GLFW window it renders to
 *
 */
class Renderer
{
public:
    /**
     * @brief Construct a new Renderer object
     *
     * @note At time of construction GLFW must be initialized
     */
    Renderer();
    /**
     * @brief Destroy the Renderer object
     *
     */
    ~Renderer();

    /**
     * @brief Check if the renderer was initialized correctly
     *
     * @return bool
     */
    inline operator bool() const noexcept
    {
        return m_initialized;
    }

    /**
     * @brief Draws the vertex array object using the provided shader program
     *
     * @param vao
     * @param shaderProgram
     */
    void Draw(const VAO& vao, const ShaderProgram& shaderProgram) noexcept;
    /**
     * @brief Clear the color buffer/screen
     *
     */
    void Clear() noexcept;
    /**
     * @brief Set the clear color
     *
     * @param r Red channel
     * @param g Green channel
     * @param b Blue channel
     * @param a Alpha (opacity) channel
     */
    void ClearColor(float r, float g, float b, float a) noexcept;

    /**
     * @brief Check whether the renderer should remain in use
     *
     * @return bool
     */
    bool ShouldClose() const noexcept;
    /**
     * @brief Tell the renderer that it should finish drawing the current frame
     *
     */
    void FinishFrame() noexcept;

private:
    GLFWwindow* m_window;
    bool m_initialized = false;

    static std::shared_ptr<GLFWRAII> s_g;
};

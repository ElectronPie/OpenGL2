#pragma once

#include <debugbreak.h>
#include <glad/glad.h>

// Forward declarations
class VAO;
class ShaderProgram;
struct GLFWwindow;

#ifdef DEBUG
    /**
     * @brief if \a x doesn't evaluate to true breaks at the execution point
     *
     * @param x Statement to be asserted
     */
    #define ASSERT(x)      \
        if(!(x))           \
        {                  \
            debug_break(); \
        }
#else
    /**
     * @brief if \a x doesn't evaluate to true breaks at the execution point
     *
     * @param x Statement to be asserted
     */
    #define ASSERT(x)
#endif

#if defined(DEBUG) && !defined(ENABLE_FANCY_DEBUG_OUTPUT)
    /**
     * @brief evaluates \a x and reports GL errors produced if any
     *
     * @param x Statement cantaining a GL call
     */
    #define GLCall(x)              \
        Renderer::ClearGLErrors(); \
        x;                         \
        ASSERT(Renderer::CheckGLError(#x, __FILE__, __LINE__))
#else
    /**
     * @brief evaluates \a x and reports GL errors produced if any
     *
     * @param x Statement cantaining a GL call
     */
    #define GLCall(x) x
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

#if defined(DEBUG) && !defined(ENABLE_FANCY_DEBUG_OUTPUT)
    /**
     * @brief Clears all OpenGL errors accumulated
     *
     */
    static void ClearGLErrors() noexcept;

    /**
     * @brief For each OpenGL error currently accumulated in the stack reports it
     *
     * @note Gets called automatically by GLCall if ENABLE_FANCY_DEBUG_OUTPUT is defined
     *
     * @param function Stringified statement containing a GL call that was executed prior to calling this function
     * @param file File in which the statement is situated
     * @param line Line in file on which the statement is situated
     * @return true If no errors were accumulated
     * @return false If any error was accumulated and processed
     */
    static bool CheckGLError(const char* function, const char* file, int line);
#endif

private:
    GLFWwindow* m_window;
    bool m_initialized = false;
};

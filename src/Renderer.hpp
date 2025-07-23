#pragma once

#include <debugbreak.h>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <imgui.h>

#include <epics/enums_as_flags11.hpp>

#include <utility>

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
 * @brief Represents the OpenGL renderer along with a GLFW window it renders to as a singleton
 */
class Renderer
{
public:
    /**
     * @brief Obtain a reference to a renderer instance
     *
     * @return Renderer&
     */
    static Renderer& GetInstance();
    /**
     * @brief Destroy the Renderer object
     */
    ~Renderer();

    Renderer(const Renderer& other)           = delete;
    Renderer operator=(const Renderer& other) = delete;

    Renderer(Renderer&& other)           = delete;
    Renderer operator=(Renderer&& other) = delete;

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
     * @brief Get a global reference to the ImGuiIO struct
     *
     * @return ImGuiIO&
     */
    inline ImGuiIO& GetImGuiIO() const noexcept
    {
        return *m_ImGuiIO;
    }

    /**
     * @brief Set the Viewport size
     *
     * @param width New width of the viewport
     * @param height New height of the viewport
     */
    void SetViewportSize(unsigned int width, unsigned int height);

    /**
     * @brief Get the Viewport size
     *
     * @return std::pair<unsigned int, unsigned int>
     */
    inline std::pair<unsigned int, unsigned int> GetViewportSize() const
    {
        return {m_viewportWidth, m_viewportHeight};
    }

    /**
     * @brief Get the underlying window
     *
     * @return GLFWwindow*
     */
    inline GLFWwindow* GetWindow() const
    {
        return m_window;
    }

    /**
     * @brief Draws the vertex array object's vertices using the provided shader program
     *
     * @param vao
     * @param shaderProgram
     */
    void DrawVertices(const VAO& vao, const ShaderProgram& shaderProgram) noexcept;
    /**
     * @brief Draws the vertex array object's elements using the provided shader program
     *
     * @param vao
     * @param shaderProgram
     */
    void DrawElements(const VAO& vao, const ShaderProgram& shaderProgram) noexcept;

    /**
     * @brief Clear the color buffer/screen
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
     * @brief Set the clear color
     *
     * @param color The clear color to set
     */
    void ClearColor(glm::vec4 color) noexcept;

    /**
     * @brief Check whether the renderer should remain in use
     *
     * @return bool
     */
    bool ShouldClose() const noexcept;
    /**
     * @brief Tell the renderer to start drawing a new frame
     *
     * @return true If one should continue rendering to the current frame
     * @return false If one should finish the frame with Renderer::FinishFrame immediately
     */
    bool StartFrame() noexcept;
    /**
     * @brief Tell the renderer that it should finish drawing the current frame
     */
    void FinishFrame() noexcept;

    /**
     * @brief Feature flags for the renderer
     */
    enum class FeatureFlags
    {
        DepthTest   = 1 << 0, ///< Enable depth testing
        StencilTest = 1 << 1, ///< Enable stencil testing
        Blending    = 1 << 2, ///< Enable blending
        FaceCulling = 1 << 3, ///< Enable face culling
    };

    /**
     * @brief Enable features of the renderer
     *
     * @param features Features to enable
     */
    void EnableFeatures(FeatureFlags features) noexcept;
    /**
     * @brief Disable features of the renderer
     *
     * @param features Features to disable
     */
    void DisableFeatures(FeatureFlags features) noexcept;

    /**
     * @brief Set the depth mask
     *
     * @param mask Mask to set for the depth buffer
     */
    void SetDepthMask(bool mask) noexcept;

    /**
     * @brief Depth test functions
     */
    enum class DepthTestFunction
    {
        Never          = GL_NEVER,
        Less           = GL_LESS,
        Equal          = GL_EQUAL,
        LessOrEqual    = GL_LEQUAL,
        Greater        = GL_GREATER,
        NotEqual       = GL_NOTEQUAL,
        GreaterOrEqual = GL_GEQUAL,
        Always         = GL_ALWAYS,
    };

    /**
     * @brief Set the depth test function
     *
     * @param func Depth test function to set
     */
    void SetDepthTestFunction(DepthTestFunction func) noexcept;

    /**
     * @brief Set the stencil mask
     *
     * @param mask Mask to set for the stencil buffer
     */
    void SetStencilMask(unsigned int mask) noexcept;

    /**
     * @brief Stencil test functions
     */
    enum class StencilTestFunction
    {
        Never          = GL_NEVER,
        Less           = GL_LESS,
        Equal          = GL_EQUAL,
        LessOrEqual    = GL_LEQUAL,
        Greater        = GL_GREATER,
        NotEqual       = GL_NOTEQUAL,
        GreaterOrEqual = GL_GEQUAL,
        Always         = GL_ALWAYS,
    };

    /**
     * @brief Set the stencil test function
     *
     * @param func Stencil test function to set
     * @param referenceValue Reference value for the stencil test
     * @param mask Mask to apply to the stencil test operands
     */
    void SetStencilTestFunction(
        StencilTestFunction func, int referenceValue = 0, unsigned int mask = 0xFFFFFFFF
    ) noexcept;

    /**
     * @brief Stencil operations
     */
    enum class StencilOperation
    {
        Keep          = GL_KEEP,
        Zero          = GL_ZERO,
        Replace       = GL_REPLACE,
        Invert        = GL_INVERT,
        Increment     = GL_INCR,
        Decrement     = GL_DECR,
        IncrementWrap = GL_INCR_WRAP,
        DecrementWrap = GL_DECR_WRAP,
    };

    /**
     * @brief Set the stencil operations to execute
     *
     * @param sfail Stencil operation to execute when stencil test fails
     * @param dpfail Stencil operation to execute when stencil test passes but depth test fails
     * @param dppass Stencil operation to execute when both stencil test and depth test pass
     */
    void SetStencilOperation(StencilOperation sfail, StencilOperation dpfail, StencilOperation dppass) noexcept;

    /**
     * @brief Blending function factors
     */
    enum class BlendingFunctionFactor
    {
        Zero                     = GL_ZERO,
        One                      = GL_ONE,
        SourceColor              = GL_SRC_COLOR,
        OneMinusSourceColor      = GL_ONE_MINUS_SRC_COLOR,
        DestinationColor         = GL_DST_COLOR,
        OneMinusDestinationColor = GL_ONE_MINUS_DST_COLOR,
        SourceAlpha              = GL_SRC_ALPHA,
        OneMinusSourceAlpha      = GL_ONE_MINUS_SRC_ALPHA,
        DestinationAlpha         = GL_DST_ALPHA,
        OneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
        ConstantColor            = GL_CONSTANT_COLOR,
        OneMinusConstantColor    = GL_ONE_MINUS_CONSTANT_COLOR,
        ConstantAlpha            = GL_CONSTANT_ALPHA,
        OneMinusConstantAlpha    = GL_ONE_MINUS_CONSTANT_ALPHA,
    };

    /**
     * @brief Set the blending function factors
     *
     * @param sfactor Factor applied to the source color
     * @param dfactor Factor applied to the destination color
     */
    void SetBlendingFunctionFactor(BlendingFunctionFactor sfactor, BlendingFunctionFactor dfactor) noexcept;

    /**
     * @brief Set the constant color used for calculating the blend function
     *
     * @param r Red channel
     * @param g Green channel
     * @param b Blue channel
     * @param a Alpha (opacity) channel
     */
    void SetBlendingConstantColor(float r, float g, float b, float a) noexcept;
    /**
     * @brief Set the constant color used for calculating the blend function
     *
     * @param color The constant color to set
     */
    void SetBlendingConstantColor(glm::vec4 color) noexcept;

    /**
     * @brief Blending equations
     */
    enum class BlendingEquation
    {
        Add             = GL_FUNC_ADD,
        Subtract        = GL_FUNC_SUBTRACT,
        ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
        Min             = GL_MIN,
        Max             = GL_MAX,
    };

    /**
     * @brief Set the blending equation
     *
     * @param equation The blending equation to set
     */
    void SetBlendingEquation(BlendingEquation equation) noexcept;

    /**
     * @brief Types of faces to cull
     */
    enum class CullFace
    {
        Front = GL_FRONT,          ///< Only cull front faces
        Back  = GL_BACK,           ///< Only cull back faces
        All   = GL_FRONT_AND_BACK, ///< Cull both front and back faces
    };

    /**
     * @brief Set the face type to cull
     *
     * @param cullFace The type of faces to cull
     */
    void SetCullFace(CullFace cullFace) noexcept;

    /**
     * @brief Type of vertex winding a face has to have to be considered a front face
     */
    enum class FrontFace
    {
        CW  = GL_CW,  ///< Clockwise
        CCW = GL_CCW, ///< Counter-clockwise
    };

    /**
     * @brief Set the type of face considered to be a front face
     *
     * @param frontFace The type of vertex winding of a face
     */
    void SetFrontFace(FrontFace frontFace) noexcept;

#if defined(DEBUG) && !defined(ENABLE_FANCY_DEBUG_OUTPUT)
    /**
     * @brief Clears all OpenGL errors accumulated
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
public:
    /**
     * @brief OpenGL clear flags used by Renderer::Clear
     */
    enum class ClearFlags
    {
        ColorBuffer   = GL_COLOR_BUFFER_BIT,
        DepthBuffer   = GL_DEPTH_BUFFER_BIT,
        StencilBuffer = GL_STENCIL_BUFFER_BIT,
    };
    ClearFlags clearFlags;

private:
    /**
     * @brief Construct a new Renderer object
     */
    Renderer();

private:
    /**
     * @brief The window rendered to
     */
    GLFWwindow* m_window = nullptr;
    /**
     * @brief The ImGui IO
     */
    ImGuiIO* m_ImGuiIO   = nullptr;
    /**
     * @brief If the renderer is correctly initialized
     */
    bool m_initialized   = false;

    /**
     * @brief Viewport width
     */
    unsigned int m_viewportWidth;
    /**
     * @brief Viewport height
     */
    unsigned int m_viewportHeight;
};

EPS_ENUM_AS_FLAGS(Renderer::FeatureFlags)
EPS_ENUM_AS_FLAGS(Renderer::ClearFlags)

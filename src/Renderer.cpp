#include "Renderer.hpp"

#include <GLFW/glfw3.h>

#include "GLFWRAII.hpp"
#include "VAO.hpp"
#include "ShaderProgram.hpp"

#include <iostream>
#include <iomanip>
#include <memory>

#if defined(DEBUG) && !defined(ENABLE_FANCY_DEBUG_OUTPUT)
void GLClearErrors()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLCheckError(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << std::showbase << std::hex << error
                  << std::resetiosflags(std::ios_base::showbase | std::ios_base::hex) << "): " << function << " "
                  << file << ":" << line << std::endl;
        return false;
    }
    return true;
}
#endif

std::shared_ptr<GLFWRAII> Renderer::s_g;

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

#if defined(DEBUG) && defined(ENABLE_FANCY_DEBUG_OUTPUT)
static void APIENTRY GLDebugOutput(
    GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam
)
{
    // Ignore non-significant error/warning codes
    switch(id)
    {
    case 131169:
    case 131185:
    case 131218:
    case 131204:
        return;
    }

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch(source)
    {
    case GL_DEBUG_SOURCE_API:
        std::cout << "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        std::cout << "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        std::cout << "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        std::cout << "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        std::cout << "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        std::cout << "Source: Other";
        break;
    }
    std::cout << std::endl;

    switch(type)
    {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "Type: Performance";
        break;
    case GL_DEBUG_TYPE_MARKER:
        std::cout << "Type: Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        std::cout << "Type: Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        std::cout << "Type: Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "Type: Other";
        break;
    }
    std::cout << std::endl;

    switch(severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "Severity: high";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "Severity: medium";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "Severity: low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        std::cout << "Severity: notification";
        break;
    }
    std::cout << std::endl;

    std::cout << std::endl;
}
#endif

Renderer::Renderer()
{
    if(s_g.get() == nullptr)
    {
        s_g = std::make_shared<GLFWRAII>();
    }

    // OpenGL version 4.3, no legacy functions support
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    // If in debug mode initialize a debug context
#if defined(DEBUG) && defined(ENABLE_FANCY_DEBUG_OUTPUT)
    glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#endif

    // Create a window
    m_window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
    if(!m_window)
    {
        std::cout << "Failed to create a GLFW window!" << std::endl;
        return;
    }

    // Make the window context current
    glfwMakeContextCurrent(m_window);

    // Force V-Sync so that the CPU/GPU usage doesn't skyrocket
    glfwSwapInterval(1);

    // Load OpenGL with GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Can't load GLAD!" << std::endl;
        return;
    }

    // Output OpenGL version
    GLCall(std::cout << glGetString(GL_VERSION) << std::endl);

    // Set the viewport size and framebuffer size callback
    GLCall(glViewport(0, 0, 800, 600));
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

    // Set key callback
    glfwSetKeyCallback(m_window, KeyCallback);

#if defined(DEBUG) && defined(ENABLE_FANCY_DEBUG_OUTPUT)
    int flags;
    GLCall(glGetIntegerv(GL_CONTEXT_FLAGS, &flags));
    if(flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        GLCall(glEnable(GL_DEBUG_OUTPUT));
        GLCall(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
        GLCall(glDebugMessageCallback(GLDebugOutput, nullptr));
        GLCall(glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE));
    }
#endif

    m_initialized = true;
}

Renderer::~Renderer()
{
    glfwDestroyWindow(m_window);
}

void Renderer::Draw(const VAO& vao, const ShaderProgram& shaderProgram) noexcept
{
    shaderProgram.Bind();
    vao.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, vao.GetElementsCount(), vao.GetElementsDataType(), NULL));
}

void Renderer::Clear() noexcept
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::ClearColor(float r, float g, float b, float a) noexcept
{
    GLCall(glClearColor(r, g, b, a));
}

bool Renderer::ShouldClose() const noexcept
{
    return glfwWindowShouldClose(m_window);
}

void Renderer::FinishFrame() noexcept
{
    // Swap front and back buffers
    glfwSwapBuffers(m_window);

    // Poll and process events
    glfwPollEvents();
}

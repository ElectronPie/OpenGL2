#include "Renderer.hpp"

#include <GLFW/glfw3.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "VAO.hpp"
#include "ShaderProgram.hpp"

#include <iostream>
#include <iomanip>
#include <memory>

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Renderer::GetInstance().SetViewportSize(width, height);
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

    debug_break();
}
#endif

Renderer& Renderer::GetInstance()
{
    static Renderer instance;
    return instance;
}

Renderer::Renderer(): clearFlags{Renderer::ClearFlags::ColorBuffer | Renderer::ClearFlags::DepthBuffer}
{
    // Initialize GLFW
    if(!glfwInit())
    {
        std::cout << "Couldn't initialize GLFW library!" << std::endl;
        return;
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
    m_viewportWidth  = 800;
    m_viewportHeight = 600;

    // Make the window context current
    glfwMakeContextCurrent(m_window);

    // Force V-Sync so that the CPU/GPU usage doesn't skyrocket
    glfwSwapInterval(1);

    // Setup Dear imGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_ImGuiIO = &ImGui::GetIO();
    m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // If using docking branch
    //m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    //m_ImGuiIO->ConfigViewportsNoAutoMerge = true;
    //m_ImGuiIO->ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
    // ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if(m_ImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding              = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();

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

    // Enable depth testing and blending
    EnableFeatures(Renderer::FeatureFlags::DepthTest & Renderer::FeatureFlags::Blending);

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
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Renderer::DrawVertices(const VAO& vao, const ShaderProgram& shaderProgram) noexcept
{
    shaderProgram.Bind();
    vao.Bind();
#ifdef DEBUG
    shaderProgram.Validate();
#endif
    GLCall(glDrawArrays(GL_TRIANGLES, 0, vao.GetVerticesCount()));
}

void Renderer::DrawElements(const VAO& vao, const ShaderProgram& shaderProgram) noexcept
{
    shaderProgram.Bind();
    vao.Bind();
#ifdef DEBUG
    shaderProgram.Validate();
#endif
    GLCall(glDrawElements(GL_TRIANGLES, vao.GetElementsCount(), vao.GetElementsDataType(), NULL));
}

void Renderer::Clear() noexcept
{
    GLCall(glClear(static_cast<int>(clearFlags)));
}

void Renderer::ClearColor(float r, float g, float b, float a) noexcept
{
    GLCall(glClearColor(r, g, b, a));
}

void Renderer::ClearColor(glm::vec4 color) noexcept
{
    GLCall(glClearColor(color.r, color.g, color.b, color.a));
}

bool Renderer::ShouldClose() const noexcept
{
    return glfwWindowShouldClose(m_window);
}

bool Renderer::StartFrame() noexcept
{
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your
    // inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite
    // your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or
    // clear/overwrite your copy of the keyboard data. Generally you may always pass all inputs to dear imgui, and hide
    // them from your application based on those two flags.
    glfwPollEvents();
    if(glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
    {
        ImGui_ImplGlfw_Sleep(10);
        return false;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    return true;
}

void Renderer::FinishFrame() noexcept
{
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this
    // code elsewhere.
    if(m_ImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    // Swap front and back buffers
    glfwSwapBuffers(m_window);
}

void Renderer::SetViewportSize(unsigned int width, unsigned int height)
{
    GLCall(glViewport(0, 0, width, height));
    m_viewportWidth  = width;
    m_viewportHeight = height;
}

void Renderer::EnableFeatures(FeatureFlags features) noexcept
{
    if(static_cast<bool>(features & FeatureFlags::DepthTest))
        GLCall(glEnable(GL_DEPTH_TEST));
    if(static_cast<bool>(features & FeatureFlags::StencilTest))
        GLCall(glEnable(GL_STENCIL_TEST));
    if(static_cast<bool>(features & FeatureFlags::Blending))
        GLCall(glEnable(GL_BLEND));
}

void Renderer::DisableFeatures(FeatureFlags features) noexcept
{
    if(static_cast<bool>(features & FeatureFlags::DepthTest))
        GLCall(glDisable(GL_DEPTH_TEST));
    if(static_cast<bool>(features & FeatureFlags::StencilTest))
        GLCall(glDisable(GL_STENCIL_TEST));
    if(static_cast<bool>(features & FeatureFlags::Blending))
        GLCall(glDisable(GL_BLEND));
}

void Renderer::SetDepthMask(bool mask) noexcept
{
    GLCall(glDepthMask(mask ? GL_TRUE : GL_FALSE));
}

void Renderer::SetDepthTestFunction(DepthTestFunction func) noexcept
{
    GLCall(glDepthFunc(static_cast<GLenum>(func)));
}

void Renderer::SetStencilMask(unsigned int mask) noexcept
{
    GLCall(glStencilMask(mask));
}

void Renderer::SetStencilTestFunction(StencilTestFunction func, int referenceValue, unsigned int mask) noexcept
{
    GLCall(glStencilFunc(static_cast<GLenum>(func), referenceValue, mask));
}

void Renderer::SetStencilOperation(
    StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass
) noexcept
{
    GLCall(glStencilOp(static_cast<GLenum>(stencilFail), static_cast<GLenum>(depthFail), static_cast<GLenum>(pass)));
}

void Renderer::SetBlendingFunctionFactor(BlendingFunctionFactor sfactor, BlendingFunctionFactor dfactor) noexcept
{
    GLCall(glBlendFunc(static_cast<GLenum>(sfactor), static_cast<GLenum>(dfactor)));
}

void Renderer::SetBlendingConstantColor(float r, float g, float b, float a) noexcept
{
    GLCall(glBlendColor(r, g, b, a));
}

void Renderer::SetBlendingConstantColor(glm::vec4 color) noexcept
{
    GLCall(glBlendColor(color.r, color.g, color.b, color.a));
}

void Renderer::SetBlendingEquation(BlendingEquation equation) noexcept
{
    GLCall(glBlendEquation(static_cast<GLenum>(equation)));
}

#if defined(DEBUG) && !defined(ENABLE_FANCY_DEBUG_OUTPUT)
void Renderer::ClearGLErrors() noexcept
{
    while(glGetError() != GL_NO_ERROR);
}

bool Renderer::CheckGLError(const char* function, const char* file, int line)
{
    bool result = true;
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << std::showbase << std::hex << error
                  << std::resetiosflags(std::ios_base::showbase | std::ios_base::hex) << "): " << function << " "
                  << file << ":" << line << std::endl;
        result = false;
    }
    return result;
}
#endif

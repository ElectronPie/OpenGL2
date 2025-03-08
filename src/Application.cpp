#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

int main(int argc, char** argv)
{
    GLFWwindow* window;

    // Initialize GLFW
    if(!glfwInit())
    {
        std::cout << "Couldn't initialize GLFW library!" << std::endl;
        return 1;
    }

    // OpenGL version 4.3, no legacy functions support
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Create a window
    window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
    if(!window)
    {
        std::cout << "Failed to create a GLFW window!" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Make the window context current
    glfwMakeContextCurrent(window);

    // Force V-Sync so that the CPU/GPU usage doesn't skyrocket
    glfwSwapInterval(1);

    // Load OpenGL with GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Can't load GLAD!" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Output OpenGL version
    std::cout << glGetString(GL_VERSION) << std::endl;

    // Set the viewport size and framebuffer size callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // Set key callback
    glfwSetKeyCallback(window, KeyCallback);

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        // Clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
}

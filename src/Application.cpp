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
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
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

    // Create a vertex array object on the GPU to store used vertex attributes, VBOs and EBOs
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // clang-format off

    // Instead of doing something like
    /*
    // Vertices of two triangles
    float vertices[] = {
        // First triangle
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f,  0.5f, 0.0f, // top left
        // Second triangle
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, // top left
    };
    // clang-format on
    */

    // clang-format off

    // We can
    float vertices[] = {
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, // top left
    };
    unsigned int indices[] = {
        0, 1, 3,    // first triangle
        1, 2, 3,    // second triangle
    };
    // So that we only use 4 vertices instead of 6
    // The difference is much more apparent with bigger models

    // clang-format on

    // Create a vertex buffer object on the GPU to store the vertices data
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Allocate the memory and load the vertices data
    // GL_STATIC_DRAW hints that we only load it once, but draw many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    // Specify that the first vertex attribute (index 0) in the currently bound VBO
    // is a vec3 (3 floats) that are tightly packed (0 stride or in this case 3 * sizeof(float) stride)
    // with the first element having an offset of 0 in the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
    // Enable that vertex attribute specifying that it's allowed to use
    glEnableVertexAttribArray(0);

    // Create an element buffer object on the GPU to store the vertex indices
    GLuint EBO;
    glGenBuffers(1, &EBO);

    // Bind the EBO and load the elements (vertex indices) data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    const char* vertexShaderSource =
        "#version 430 core\n"
        "\n"
        "layout (location = 0) in vec3 aPos;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.xyz, 1.0);\n"
        "}\n";

    // Create a shader object for the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Specify the shader's source code and compile it
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check if vertex shader compilation was successful
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        // Get shader info log length
        GLint length;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
        // Allocate that amount of memory on the stack with alloca
        // It will be freed automatically when returning from the function
        GLchar* message = (GLchar*)alloca(length * sizeof(GLchar));
        // Get shader info log
        glGetShaderInfoLog(vertexShader, length, &length, message);
        std::cout << "Failed to compile vertex shader!" << std::endl;
        std::cout << message << std::endl;
    }

    const char* fragmentShaderSource =
        "#version 430 core\n"
        "\n"
        "out vec4 FragColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
        "}\n";

    // Create a shader object for the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Specify the shader's source code and compile it
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check if vertex shader compilation was successful
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        // Get shader info log length
        GLint length;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
        // Allocate that amount of memory on the stack with alloca
        // It will be freed automatically when returning from the function
        GLchar* message = (GLchar*)alloca(length * sizeof(GLchar));
        // Get shader info log
        glGetShaderInfoLog(fragmentShader, length, &length, message);
        std::cout << "Failed to compile fragment shader!" << std::endl;
        std::cout << message << std::endl;
    }

    // Create a shader program object
    GLuint shaderProgram = glCreateProgram();

    // Attach the previously compiled shaders to the program and link them
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check if program linkage was successful
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(success == GL_FALSE)
    {
        // Get program info log length
        GLint length;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
        // Allocate that amount of memory on the stack with alloca
        // It will be freed automatically when returning from the function
        GLchar* message = (GLchar*)alloca(length * sizeof(GLchar));
        // Get program info log
        glGetProgramInfoLog(shaderProgram, length, &length, message);
        std::cout << "Failed to link shader program!" << std::endl;
        std::cout << message << std::endl;
    }

    // Activate the shader program
    glUseProgram(shaderProgram);

    // Delete the shader objects since we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        // Clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Activate the shader program
        glUseProgram(shaderProgram);

        // Bind the VAO
        glBindVertexArray(VAO);

        // The render call itself
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
}

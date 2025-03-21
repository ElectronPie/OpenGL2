#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "ShaderProgram.hpp"

int main(int argc, char** argv)
{
    Renderer r;
    if(!r)
    {
        return 1;
    }

    int numAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
    std::cout << "Max number of vertex attributes is " << numAttribs << std::endl;

    // Create the VAO
    VAO vao;
    vao.Bind();

    // clang-format off

    // Vertex data
    float vertices[] = {
        0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,// top right
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,// bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,// top left
    };
    // Element data
    unsigned int indices[] = {
        0, 1, 3,    // first triangle
        1, 2, 3,    // second triangle
    };

    // clang-format on

    // Create a VBO
    VBO vbo{vertices, sizeof(vertices)};
    vbo.Bind();

    // Create the layout for the VBO
    VBLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);

    // Attach the VBO to the VAO
    vao.AttachVBO(vbo, layout);

    // Create a EBO
    EBO ebo{indices, sizeof(indices) / sizeof(indices[0])};

    // Attach the EBO to the VAO
    vao.AttachEBO(ebo);

    ShaderProgram shaderProgram{"assets/shaders/Vertex.glsl", "assets/shaders/Fragment.glsl"};

    // Main loop
    while(!r.ShouldClose())
    {
        // Clear color
        r.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        r.Clear();

        // Draw the VAO using our shader program
        r.Draw(vao, shaderProgram);

        r.FinishFrame();
    }
}

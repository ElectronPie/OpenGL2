#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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

    // Create the VAO
    VAO vao;
    vao.Bind();

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

    // Create a VBO
    VBO vbo{vertices, sizeof(vertices)};
    vbo.Bind();

    // Create the layout for the VBO
    VBLayout layout;
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

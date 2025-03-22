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
#include "Texture.hpp"

int main(int argc, char** argv)
{
    Renderer r;
    if(!r)
    {
        return 1;
    }
    r.ClearColor(0.0f, 0.5f, 0.7f, 1.0f);

    // Create the VAO
    VAO vao;
    vao.Bind();

    // clang-format off

    // Vertex data
    float vertices[] = {
        // positions            // colors           // texture coords
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   // top left
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
    layout.Push<float>(2);

    // Attach the VBO to the VAO
    vao.AttachVBO(vbo, layout);

    // Create a EBO
    EBO ebo{indices, sizeof(indices) / sizeof(indices[0])};

    // Attach the EBO to the VAO
    vao.AttachEBO(ebo);

    ShaderProgram shaderProgram{"assets/shaders/Vertex.glsl", "assets/shaders/Fragment.glsl"};
    shaderProgram.Bind();

    Texture texture1{"assets/textures/container.jpg"};
    Texture texture2{"assets/textures/awesomeface.png"};
    texture1.Bind(0);
    texture2.Bind(1);

    shaderProgram.SetUniform1("u_texture1", 0);
    shaderProgram.SetUniform1("u_texture2", 1);

    // Main loop
    while(!r.ShouldClose())
    {
        // Clear color
        r.Clear();

        // Draw the VAO using our shader program
        r.Draw(vao, shaderProgram);

        r.FinishFrame();
    }
}

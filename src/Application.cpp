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

    // Set Sampler2D #0 to texture1
    shaderProgram.SetUniform1("u_texture1", 0);
    // Set Sampler2D #1 to texture2
    shaderProgram.SetUniform1("u_texture2", 1);

    // ImGui state
    ImGuiIO& io            = r.GetImGuiIO();
    bool showDemoWindow    = true;
    bool showAnotherWindow = false;
    glm::vec4 clearColor{0.0f, 0.5f, 0.7f, 1.0f};

    // Main loop
    while(!r.ShouldClose())
    {
        if(r.StartFrame())
        {
            // Rendering
            // Clear color
            r.ClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            r.Clear();

            // Draw the VAO using our shader program
            r.Draw(vao, shaderProgram);

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its
            // code to learn more about Dear ImGui!).
            if(showDemoWindow)
            {
                ImGui::ShowDemoWindow(&showDemoWindow);
            }

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {
                static float f     = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");        // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &showDemoWindow); // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &showAnotherWindow);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);      // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit4("clear color", &clearColor[0]); // Edit 4 floats representing a color

                if(ImGui::Button("Button"
                   )) // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if(showAnotherWindow)
            {
                ImGui::Begin(
                    "Another Window", &showAnotherWindow
                ); // Pass a pointer to our bool variable (the window will have a closing button that will clear the
                   // bool when clicked)
                ImGui::Text("Hello from another window!");
                if(ImGui::Button("Close Me"))
                    showAnotherWindow = false;
                ImGui::End();
            }
        }
        r.FinishFrame();
    }
}

#include <iostream>
#include <optional>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "VBLayout.hpp"
#include "EBO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#include "test/Test.hpp"
#include "test/TestClearColor.hpp"
#include "test/TestTexture2D.hpp"
#include "test/TestTransform2D.hpp"
#include "test/TestMVP.hpp"
#include "test/TestCamera.hpp"
#include "test/TestLighting.hpp"

static std::optional<std::string> GetTestNameFromArgs(int argc, char** argv)
{
    for(int i = 1; i < argc - 1; ++i)
    {
        if(std::string t{argv[i]}; t == "-t" || t == "--test")
        {
            return std::make_optional<std::string>(argv[i + 1]);
        }
    }
    return std::nullopt;
}

int main(int argc, char** argv)
{
    Renderer& r = Renderer::GetInstance();
    if(!r)
    {
        return 1;
    }
    r.ClearColor(0.0f, 0.5f, 0.7f, 1.0f);

    //Tests
    Tests::Test* currentTest  = nullptr;
    Tests::TestMenu* testMenu = new Tests::TestMenu{currentTest};
    currentTest               = testMenu;

    testMenu->RegisterTest<Tests::TestClearColor>("Clear color");
    testMenu->RegisterTest<Tests::TestTexture2D>("Texture (2D)");
    testMenu->RegisterTest<Tests::TestTransform2D>("Transforms (2D)");
    testMenu->RegisterTest<Tests::TestMVP>("MVP");
    testMenu->RegisterTest<Tests::TestCamera>("Camera");
    testMenu->RegisterTest<Tests::TestLighting>("Lighting");

    testMenu->UseTest(GetTestNameFromArgs(argc, argv).value_or(""));

    float timeMark = glfwGetTime();

    // Main loop
    while(!r.ShouldClose())
    {
        if(r.StartFrame())
        {
            r.Clear();

            if(currentTest)
            {
                float deltaTime = glfwGetTime() - timeMark;
                timeMark += deltaTime;
                currentTest->OnUpdate(deltaTime);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if(currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }
        }
        r.FinishFrame();
    }

    delete currentTest;
    if(currentTest != testMenu)
    {
        delete testMenu;
    }
}

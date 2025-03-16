#include "GLFWRAII.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

GLFWRAII::GLFWRAII()
{
    // Initialize GLFW
    if(!glfwInit())
    {
        std::cout << "Couldn't initialize GLFW library!" << std::endl;
        return;
    }
    m_initialized = true;
}

GLFWRAII::~GLFWRAII()
{}

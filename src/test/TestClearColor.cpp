#include "TestClearColor.hpp"

#include "Renderer.hpp"

#include <imgui.h>

namespace Tests
{
    TestClearColor::TestClearColor()
    {}

    TestClearColor::~TestClearColor()
    {}

    void TestClearColor::OnRender()
    {
        GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    }

    void TestClearColor::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear color", m_clearColor);
    }
} // namespace Tests

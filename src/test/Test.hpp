#pragma once

#include <functional>
#include <string>
#include <vector>

/**
 * @brief Namespace for all related to testing of the render engine
 *
 */
namespace Tests
{
    /**
     * @brief Abstract class representing a test for the render engine
     *
     */
    class Test
    {
    public:
        /**
         * @brief Construct a new Test object
         *
         */
        Test()
        {}
        /**
         * @brief Destroy the Test object
         *
         */
        virtual ~Test()
        {}

        /**
         * @brief To be called each frame for state update purposes
         *
         * @param deltaTime Time elapsed in between frames in seconds
         */
        virtual void OnUpdate(float deltaTime)
        {}
        /**
         * @brief To be called each frame for OpenGL rendering purposes
         *
         */
        virtual void OnRender()
        {}
        /**
         * @brief To be called each frame for ImGui rendering purposes
         *
         */
        virtual void OnImGuiRender()
        {}
    };

    class TestMenu: public Test
    {
    public:
        TestMenu(Test*& currentTestPointer);

        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name);

        void UseTest(const std::string& name);

    private:
        Test*& m_currentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
} // namespace Tests

#include "Test.inl"

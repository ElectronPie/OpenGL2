#pragma once

#include <functional>
#include <string>
#include <vector>

/**
 * @brief Namespace for all related to testing of the render engine
 */
namespace Tests
{
    /**
     * @brief Abstract class representing a test for the render engine
     */
    class Test
    {
    public:
        /**
         * @brief Construct a new Test object
         */
        Test()
        {}

        /**
         * @brief Destroy the Test object
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
         */
        virtual void OnRender()
        {}

        /**
         * @brief To be called each frame for ImGui rendering purposes
         */
        virtual void OnImGuiRender()
        {}
    };

    class TestMenu: public Test
    {
    public:
        /**
         * @brief Construct a new Test Menu object
         *
         * @param currentTestPointer Reference to a pointer which stores the currently used test
         */
        TestMenu(Test*& currentTestPointer);

        /**
         * @copydoc Tests::Test::OnImGuiRender
         */
        void OnImGuiRender() override;

        /**
         * @brief Register a test to be accessible from the test menu
         *
         * @tparam T Test type
         * @param name Displayed name of the test
         */
        template<typename T>
        void RegisterTest(const std::string& name);

        /**
         * @brief Use a registered test
         *
         * @param name Name of the test
         */
        void UseTest(const std::string& name);

    private:
        /**
         * @brief Reference to a pointer which stores the currently used test
         */
        Test*& m_currentTest;
        /**
         * @brief Stores the registered tests
         */
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
} // namespace Tests

#include "Test.inl"

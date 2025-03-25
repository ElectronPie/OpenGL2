#pragma once

#include "Test.hpp"

namespace Tests
{
    class TestClearColor: public Test
    {
    public:
        /**
         * @brief Construct a new Test Clear Color object
         */
        TestClearColor();
        /**
         * @brief Destroy the Test Clear Color object
         */
        ~TestClearColor();

        /**
         * @copydoc Tests::Test::OnRender
         */
        void OnRender() override;
        /**
         * @copydoc Tests::Test::OnImGuiRender
         */
        void OnImGuiRender() override;

    private:
        /**
         * @brief Stores the clear color
         */
        float m_clearColor[4] = {0.0f, 0.5f, 0.7f, 1.0f};
    };
} // namespace Tests

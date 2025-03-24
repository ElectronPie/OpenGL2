#include <iostream>
#include <iomanip>

namespace Tests
{
    template<typename T>
    void TestMenu::RegisterTest(const std::string& name)
    {
        std::cout << "Registering test " << std::quoted(name) << std::endl;
        m_Tests.emplace_back(name, []() { return new T; });
    }
} // namespace Tests

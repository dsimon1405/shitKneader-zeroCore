#include <ZC/ErrorLogger/ZC_EL_Console.h>

void ZC_EL_Console::LogError(const std::string& msg)
{
    std::cout << "=> ERROR: " << msg << std::endl;
}

void ZC_EL_Console::LogWarning(const std::string& msg)
{
    std::cout << "=> Warning: " << msg << std::endl;
}
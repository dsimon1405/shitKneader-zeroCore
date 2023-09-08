#pragma once

#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

class ZC_EL_AndroidConsole : public ZC_ErrorLogger
{
public:
    ZC_EL_AndroidConsole() = default;
private:
    virtual void LogError(const std::string& msg) override;
    virtual void LogWarning(const std::string& msg) override;
};
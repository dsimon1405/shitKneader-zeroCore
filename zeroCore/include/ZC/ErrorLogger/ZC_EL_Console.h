#pragma once

#include <ZC/ErrorLogger/ZC_ErroLogger.h>
#include <iostream>

class ZC_EL_Console : public ZC_ErrorLogger
{
public:
    ZC_EL_Console() = default;
private:
    virtual void LogError(const std::string& msg) override;
    virtual void LogWarning(const std::string& msg) override;
};
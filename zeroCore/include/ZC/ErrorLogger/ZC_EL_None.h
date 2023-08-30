#pragma once

#include <ZC/ErrorLogger/ZC_ErroLogger.h>
#include <ZC_string.h>

class ZC_EL_None : public ZC_ErrorLogger
{
public:
    ZC_EL_None() = default;
private:
    virtual void LogError(const std::string& msg) override {}
    virtual void LogWarning(const std::string& msg) override {}
};
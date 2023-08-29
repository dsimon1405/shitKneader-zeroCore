#pragma once

#include <ZC/ZC_Noncopyable.h>
#include <memory>

void ZC_Err(const std::string& msg);
void ZC_Wrn(const std::string& msg);

class ZC_ErrorLogger;
using ZC_pErrorLogger = std::shared_ptr<ZC_ErrorLogger>;

class ZC_ErrorLogger : public ZC_Noncopyable
{
public:
    static void Error(const std::string& msg);
    static void Warning(const std::string& msg);
    static void SetLogger(ZC_pErrorLogger lgr);

protected:
    ZC_ErrorLogger() = default;

private:
    static inline ZC_pErrorLogger logger = nullptr;

    virtual void LogError(const std::string& msg) = 0;
    virtual void LogWarning(const std::string& msg) = 0;
};
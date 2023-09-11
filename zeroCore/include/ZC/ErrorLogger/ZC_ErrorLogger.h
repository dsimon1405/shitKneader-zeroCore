#pragma once

#include <ZC/ZC_Noncopyable.h>
#include <ZC_string.h>
#include <memory>

class ZC_ErrorLogger;
using ZC_pErrorLogger = std::shared_ptr<ZC_ErrorLogger>;

class ZC_ErrorLogger : public ZC_Noncopyable
{
public:
    ZC_ErrorLogger() = default;
    static void Error(const std::string& msg);
    static void Warning(const std::string& msg);
    static bool Init();

private:
    static inline ZC_pErrorLogger logger = nullptr;

    // static inline bool init = Init();

    static void SetLogger(ZC_pErrorLogger lgr);

    virtual void LogError(const std::string& msg);
    virtual void LogWarning(const std::string& msg);
};
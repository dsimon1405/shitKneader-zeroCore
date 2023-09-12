#include <ZC/ErrorLogger/ZC_EL_AndroidConsole.h>

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

void ZC_EL_AndroidConsole::LogError(const std::string& msg)
{
    LOGI("%s", ("=> ERROR: " + msg).c_str());
}

void ZC_EL_AndroidConsole::LogWarning(const std::string& msg)
{
    LOGI("%s", ("=> Warning: " + msg).c_str());
}
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

#include <ZC_EL.h>

void ZC_ErrorLogger::Error(const std::string& msg)
{
    logger->LogError(msg);
}

void ZC_ErrorLogger::Warning(const std::string& msg)
{
    logger->LogWarning(msg);
}

void ZC_ErrorLogger::SetLogger(ZC_pErrorLogger lgr)
{
    if (logger == nullptr)
    {
        logger = lgr;
    }
    else
    {
        ZC_Wrn("Error Logger is already settled. It can only be seated once!");
    }

}

void ZC_ErrorLogger::LogError(const std::string& msg) {}
void ZC_ErrorLogger::LogWarning(const std::string& msg) {}
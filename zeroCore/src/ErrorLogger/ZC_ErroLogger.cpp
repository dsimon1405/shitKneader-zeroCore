#include <ZC/ErrorLogger/ZC_ErroLogger.h>

void ZC_Err(const std::string& msg)
{
    ZC_ErrorLogger::Error(msg);
}

void ZC_Wrn(const std::string& msg)
{
    ZC_ErrorLogger::Warning(msg);
}

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
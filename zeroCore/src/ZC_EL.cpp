#include <ZC_EL.h>

#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

void ZC_Err(const std::string& msg)
{
    ZC_ErrorLogger::Error(msg);
}

void ZC_Wrn(const std::string& msg)
{
    ZC_ErrorLogger::Warning(msg);
}
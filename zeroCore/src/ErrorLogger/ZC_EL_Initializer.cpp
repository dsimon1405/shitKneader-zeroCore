#include <ZC_Config.h>
#include <ZC/ErrorLogger/ZC_EL_Console.h>
#include <ZC/ErrorLogger/ZC_EL_None.h>

bool EL_Initializer()
{
    int a = 3;
    if (ZC_ERROR_LOGGER_TYPE == "console")
    {
        ZC_ErrorLogger::SetLogger(std::dynamic_pointer_cast<ZC_ErrorLogger>(std::make_shared<ZC_EL_Console>()));
        return true;
    }
    if (ZC_ERROR_LOGGER_TYPE == "database")
    {
        return true;
    }
    if (ZC_ERROR_LOGGER_TYPE == "none")
    {
        ZC_ErrorLogger::SetLogger(std::dynamic_pointer_cast<ZC_ErrorLogger>(std::make_shared<ZC_EL_None>()));
        return true;
    }
}

static bool initialize = EL_Initializer();
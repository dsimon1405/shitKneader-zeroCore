#pragma once

//#include <ZC_Config.h>

#ifdef ZC_EL_console
// #ifdef ZC_API_android
// #include <ZC/ErrorLogger/ZC_EL_AndroidConsole.h>
// bool ZC_ErrorLogger::Init()
// {
//         ZC_ErrorLogger::SetLogger(std::dynamic_pointer_cast<ZC_ErrorLogger>(std::make_shared<ZC_EL_AndroidConsole>()));
//         return true;
// }
// #endif /*#ifdef ZC_API_android*/

// #ifndef ZC_API_android
#include <ZC/ErrorLogger/ZC_EL_Console.h>
bool ZC_ErrorLogger::Init()
{
        ZC_ErrorLogger::SetLogger(std::dynamic_pointer_cast<ZC_ErrorLogger>(std::make_shared<ZC_EL_Console>()));
        return true;
}
// #endif /*#ifndef ZC_API_android*/
#endif  /*#ifdef ZC_EL_console*/


#ifdef ZC_EL_none
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>
bool ZC_ErrorLogger::Init()
{
        ZC_ErrorLogger::SetLogger(std::make_shared<ZC_ErrorLogger>());
        return true;
}
#endif /*#ifdef ZC_EL_none*/
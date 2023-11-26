#pragma once

#include "ZC_Window.h"
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>
#include <ZC/Tools/ZC_uptr.h>

using ZC_upWindow = ZC_uptr<ZC_Window>;

class ZC_Video
{
public:
    ZC_Video() = delete;

    /*
    Create window.

    Params:
    name - window name (no action in ZC_ANDROID build).
    width - window width (no action in ZC_ANDROID build).
    height - window height (no action in ZC_ANDROID build).

    Return:
    On success unique pointer of ZC_Window, otherwise nullptr (in second case ZC_ErrorLogger::ErrorMessage() - for more information).
    */
    static ZC_upWindow MakeWindow(const char* name = "", int width = 0, int height = 0);
};
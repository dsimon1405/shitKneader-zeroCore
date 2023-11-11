#pragma once

#include "ZC_Window.h"
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

using ZC_upWindow = std::unique_ptr<ZC_Window>;

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
    static ZC_upWindow MakeWindow(const char* const& name = "", const int& width = 0, const int& height = 0);

private:
    template<typename TWindow>
    static ZC_upWindow MakeWin(const char* const& name, const int& width, const int& height)
    {
        ZC_ErrorLogger::Clear();
        TWindow* pZC_SDL_Window = new TWindow(name, width, height);
        if (ZC_ErrorLogger::WasError())
        {
            delete pZC_SDL_Window;
            return nullptr;
        }
        
        return std::unique_ptr<ZC_Window>(dynamic_cast<ZC_Window*>(pZC_SDL_Window));
    }
};
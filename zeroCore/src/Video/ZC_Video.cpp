#include <ZC/Video/ZC_Video.h>

#include <ZC_Config.h>

#include <memory>

#if defined(ZC_SDL_VIDEO)
    #include "PC/SDL/ZC_SDL_Window.h"
    ZC_upWindow ZC_Video::MakeWindow(const char* const& name, const int& width, const int& height)
    {
        return MakeWin<ZC_SDL_Window>(name, width, height);
    }
#elif defined(ZC_ANDROID_NATIVE_APP_GLUE)
    #include <ZC/Video/ZC_AndroidNativeAppGlue_Window.h>
    ZC_upWindow ZC_Video::MakeWindow(const char* const& name, const int& width, const int& height)
    {
        return MakeWin<ZC_AndroidNativeAppGlue_Window>(name, width, height);
    }
#endif
#include <ZC/ZC_APIFactory.h>
#include <ZC_Config.h>

#ifdef ZC_API_sdl
    #include <ZC/API/PC/SDL/ZC_API_SDL.h>
    ZC_pAPIFactory ZC_APIFactory::GetApiFactory()
    {
        return ZC_API_SDL::GetAPI();
    }
#elif ZC_API_android
    //  initialized in ZC/API/Android/ZC_A_main.h
#endif
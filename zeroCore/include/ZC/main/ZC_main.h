#pragma once

/*
Program entry point.
*/
int ZC_main();

#include <ZC_Config.h>

#if defined(ZC_OBOE) || defined(ZC_SDL_AUDIO)
#include <ZC/Audio/ZC_Audio.h>
#endif

#ifdef ZC_PC
int main(int argv, char** args)
{
    return ZC_main();
#if defined(ZC_OBOE) || defined(ZC_SDL_AUDIO)
    ZC_Audio::CloseAudioStream();
#endif
}
#elif defined ZC_ANDROID_NATIVE_APP_GLUE
    #include <ZC/main/ZC_AndroidNativeAppGlue_main.h>
#endif
#pragma once

#include <ZC/main/ZC_main.h>
#include <ZC/Video/ZC_android_app.h>

#include <android/sensor.h>

#include <fstream>

void android_main(android_app* pAndroidApp)
{
//    ASensorEventQueue_getEvents

    ZC_android_app AndroidApp(pAndroidApp);
    ZC_main();
#if defined(ZC_OBOE) || defined(ZC_SDL_AUDIO)
    ZC_Audio::CloseAudioStream();
#endif
}
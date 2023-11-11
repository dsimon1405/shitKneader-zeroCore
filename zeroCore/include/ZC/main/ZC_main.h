#pragma once

/*
Program entry point.
*/
int ZC_main();

#include <ZC_Config.h>

#ifdef ZC_ANDROID_NATIVE_APP_GLUE
    #include <ZC/main/ZC_AndroidNativeAppGlue_main.h>
#endif
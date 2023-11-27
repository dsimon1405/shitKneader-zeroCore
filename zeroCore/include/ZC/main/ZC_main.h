#pragma once

/*
Program entry point.
*/
int ZC_main();

#include <ZC_Config.h>

#ifdef ZC_PC
int main(int argv, char** args)
{
    return ZC_main();
}
#elif defined ZC_ANDROID_NATIVE_APP_GLUE
    #include <ZC/main/ZC_AndroidNativeAppGlue_main.h>
#endif
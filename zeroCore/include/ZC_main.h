#pragma once

#include <ZC_Config.h>

#ifdef ZC_API_android
    #include <ZC/API/Android/ZC_A_main.h>
#endif
#ifndef ZC_API_android
    #include <ZC/API/PC/ZC_PC_main.h>
#endif
#pragma once

#include <ZC_Config.h>

#if defined(ZC_API_sdl)
#   include <ZC/API/PC/SDL/ZC_SDL_OpenGL.h>
#elif defined(ZC_API_android)
//#   include <GLES3/gl3.h>
#   include <GLES3/gl32.h>
#endif
#include <ZC/API/PC/SDL/ZC_SDL_OpenGL.h>

#include <SDL3/SDL.h>
#include <ZC_EL.h>

void ZC_SDL_LoadOpenGL()
{
    static bool initiated = false;
    if (!initiated)
    {
        if (SDL_GL_LoadLibrary(NULL) != 0) { ZC_Err("SDL_GL_LoadLibrary faild!"); }
        pglClear = (PFNGLCLEARPROC)SDL_GL_GetProcAddress("glClear");
        if (!pglClear) { ZC_Wrn("glClear SDL_GL_GetProcAddress faild!"); }
        pglClearColor = (PFNGLCLEARCOLORPROC)SDL_GL_GetProcAddress("glClearColor");
        if (!pglClearColor) { ZC_Wrn("glClearColor SDL_GL_GetProcAddress faild!"); }
        initiated = true;
    }
    else ZC_Wrn("SDL_OpenGL allready initiated!");
}

PFNGLCLEARPROC pglClear = nullptr;
PFNGLCLEARCOLORPROC pglClearColor = nullptr;
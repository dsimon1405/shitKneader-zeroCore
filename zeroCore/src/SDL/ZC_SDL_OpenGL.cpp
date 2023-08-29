#include <ZC/SDL/ZC_SDL_OpenGL.h>

void LoadOpenGL()
{
    if (SDL_GL_LoadLibrary(NULL) != 0) { ZC_Err("SDL_GL_LoadLibrary faild!"); }
    pglClear = (PFNGLCLEARPROC)SDL_GL_GetProcAddress("glClear");
    if (!pglClear) { ZC_Wrn("pglClear SDL_GL_GetProcAddress faild!"); }
    pglClearColor = (PFNGLCLEARCOLORPROC)SDL_GL_GetProcAddress("glClearColor");
    if (!pglClearColor) { ZC_Wrn("pglClearColor SDL_GL_GetProcAddress faild!"); }
}

PFNGLCLEARPROC pglClear = nullptr;
PFNGLCLEARCOLORPROC pglClearColor = nullptr;
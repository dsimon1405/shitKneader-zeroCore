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
        pglGetString = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        if (!pglGetString) { ZC_Wrn("glGetString SDL_GL_GetProcAddress faild!"); }
        pglEnable = (PFNGLENABLEPROC)SDL_GL_GetProcAddress("glEnable");
        if (!pglEnable) { ZC_Wrn("glEnable SDL_GL_GetProcAddress faild!"); }
        pglGetIntegerv = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        if (!pglGetIntegerv) { ZC_Wrn("glGetIntegerv SDL_GL_GetProcAddress faild!"); }
        pglDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)SDL_GL_GetProcAddress("glDebugMessageCallback");
        if (!pglDebugMessageCallback) { ZC_Wrn("glDebugMessageCallback SDL_GL_GetProcAddress faild!"); }
        pglDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)SDL_GL_GetProcAddress("glDebugMessageControl");
        if (!pglDebugMessageControl) { ZC_Wrn("glDebugMessageControl SDL_GL_GetProcAddress faild!"); }

        // ZC_Wrn(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
        // ZC_Wrn(reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
        // ZC_Wrn(reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS)));

        initiated = true;
    }
    else ZC_Wrn("SDL_OpenGL allready initiated!");
}

//  clear buffer
PFNGLCLEARPROC pglClear = nullptr;
PFNGLCLEARCOLORPROC pglClearColor = nullptr;

//  get resource
PFNGLGETSTRINGPROC pglGetString = nullptr;
PFNGLGETINTEGERVPROC pglGetIntegerv = nullptr;

//  enble
PFNGLENABLEPROC pglEnable = nullptr;

//  debug
PFNGLDEBUGMESSAGECALLBACKPROC pglDebugMessageCallback = nullptr;
PFNGLDEBUGMESSAGECONTROLPROC pglDebugMessageControl = nullptr;
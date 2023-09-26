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
        pglCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
        if (!pglCreateProgram) { ZC_Wrn("glCreateProgram SDL_GL_GetProcAddress faild!"); }
        pglAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
        if (!pglAttachShader) { ZC_Wrn("glAttachShader SDL_GL_GetProcAddress faild!"); }
        pglLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
        if (!pglLinkProgram) { ZC_Wrn("glLinkProgram SDL_GL_GetProcAddress faild!"); }
        pglGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");
        if (!pglGetProgramiv) { ZC_Wrn("glGetProgramiv SDL_GL_GetProcAddress faild!"); }
        pglGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
        if (!pglGetProgramInfoLog) { ZC_Wrn("glGetProgramInfoLog SDL_GL_GetProcAddress faild!"); }
        pglDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
        if (!pglDeleteShader) { ZC_Wrn("glDeleteShader SDL_GL_GetProcAddress faild!"); }
        pglCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
        if (!pglCreateShader) { ZC_Wrn("glCreateShader SDL_GL_GetProcAddress faild!"); }
        pglShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
        if (!pglShaderSource) { ZC_Wrn("glShaderSource SDL_GL_GetProcAddress faild!"); }
        pglCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
        if (!pglCompileShader) { ZC_Wrn("glCompileShader SDL_GL_GetProcAddress faild!"); }
        pglGetShaderiv = (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv");
        if (!pglGetShaderiv) { ZC_Wrn("glGetShaderiv SDL_GL_GetProcAddress faild!"); }
        pglGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");
        if (!pglGetShaderInfoLog) { ZC_Wrn("glGetShaderInfoLog SDL_GL_GetProcAddress faild!"); }
        pglDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");
        if (!pglDeleteProgram) { ZC_Wrn("glDeleteProgram SDL_GL_GetProcAddress faild!"); }
        pglUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
        if (!pglUseProgram) { ZC_Wrn("glUseProgram SDL_GL_GetProcAddress faild!"); }
        pglGenBuffers = (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers");
        if (!pglGenBuffers) { ZC_Wrn("glGenBuffers SDL_GL_GetProcAddress faild!"); }
        pglDeleteBuffers = (PFNGLDELETEBUFFERSPROC)SDL_GL_GetProcAddress("glDeleteBuffers");
        if (!pglDeleteBuffers) { ZC_Wrn("glDeleteBuffers SDL_GL_GetProcAddress faild!"); }
        pglBindBuffer = (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer");
        if (!pglBindBuffer) { ZC_Wrn("glBindBuffer SDL_GL_GetProcAddress faild!"); }
        pglGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glGenVertexArrays");
        if (!pglGenVertexArrays) { ZC_Wrn("glGenVertexArrays SDL_GL_GetProcAddress faild!"); }
        pglDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glDeleteVertexArrays");
        if (!pglDeleteVertexArrays) { ZC_Wrn("glDeleteVertexArrays SDL_GL_GetProcAddress faild!"); }
        pglBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)SDL_GL_GetProcAddress("glBindVertexArray");
        if (!pglBindVertexArray) { ZC_Wrn("glBindVertexArray SDL_GL_GetProcAddress faild!"); }
        pglBufferData = (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData");
        if (!pglBufferData) { ZC_Wrn("glBufferData SDL_GL_GetProcAddress faild!"); }
        pglEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glEnableVertexAttribArray");
        if (!pglEnableVertexAttribArray) { ZC_Wrn("glEnableVertexAttribArray SDL_GL_GetProcAddress faild!"); }
        pglVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)SDL_GL_GetProcAddress("glVertexAttribPointer");
        if (!pglVertexAttribPointer) { ZC_Wrn("glVertexAttribPointer SDL_GL_GetProcAddress faild!"); }
        pglDrawArrays = (PFNGLDRAWARRAYSPROC)SDL_GL_GetProcAddress("glDrawArrays");
        if (!pglDrawArrays) { ZC_Wrn("glDrawArrays SDL_GL_GetProcAddress faild!"); }

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

//  shader
PFNGLCREATEPROGRAMPROC pglCreateProgram = nullptr;
PFNGLATTACHSHADERPROC pglAttachShader = nullptr;
PFNGLLINKPROGRAMPROC pglLinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC pglGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC pglGetProgramInfoLog = nullptr;
PFNGLDELETESHADERPROC pglDeleteShader = nullptr;
PFNGLCREATESHADERPROC pglCreateShader = nullptr;
PFNGLSHADERSOURCEPROC pglShaderSource = nullptr;
PFNGLCOMPILESHADERPROC pglCompileShader = nullptr;
PFNGLGETSHADERIVPROC pglGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC pglGetShaderInfoLog = nullptr;
PFNGLDELETEPROGRAMPROC pglDeleteProgram = nullptr;
PFNGLUSEPROGRAMPROC pglUseProgram = nullptr;

//  buffer
PFNGLGENBUFFERSPROC pglGenBuffers = nullptr;
PFNGLDELETEBUFFERSPROC pglDeleteBuffers = nullptr;
PFNGLBINDBUFFERPROC pglBindBuffer = nullptr;

//  VAO
PFNGLGENVERTEXARRAYSPROC pglGenVertexArrays = nullptr;
PFNGLDELETEVERTEXARRAYSPROC pglDeleteVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC pglBindVertexArray = nullptr;
PFNGLBUFFERDATAPROC pglBufferData = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC pglEnableVertexAttribArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC pglVertexAttribPointer = nullptr;
PFNGLDRAWARRAYSPROC pglDrawArrays = nullptr;
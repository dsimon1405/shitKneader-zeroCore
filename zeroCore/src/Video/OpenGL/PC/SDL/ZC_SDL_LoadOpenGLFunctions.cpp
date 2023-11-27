#include "ZC_SDL_LoadOpenGLFunctions.h"

#include <ZC/Video/OpenGL/ZC_OpenGL.h>
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

#include <SDL3/SDL_video.h>

bool ZC_SDL_LoadOpenGLFunctions()
{
    if (SDL_GL_LoadLibrary(NULL) != 0) { ZC_ErrorLogger::Err("SDL_GL_LoadLibrary() faild! " + std::string(SDL_GetError()), __FILE__, __LINE__); return false;}

    //  clear buffer
    pglClear = (PFNGLCLEARPROC)SDL_GL_GetProcAddress("glClear");
    if (!pglClear) { ZC_ErrorLogger::Err("glClear SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglClearColor = (PFNGLCLEARCOLORPROC)SDL_GL_GetProcAddress("glClearColor");
    if (!pglClearColor) { ZC_ErrorLogger::Err("glClearColor SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    //  get resource
    pglGetString = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    if (!pglGetString) { ZC_ErrorLogger::Err("glGetString SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglGetIntegerv = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
    if (!pglGetIntegerv) { ZC_ErrorLogger::Err("glGetIntegerv SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    //  enble
    pglEnable = (PFNGLENABLEPROC)SDL_GL_GetProcAddress("glEnable");
    if (!pglEnable) { ZC_ErrorLogger::Err("glEnable SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    //  debug
    pglDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)SDL_GL_GetProcAddress("glDebugMessageCallback");
    if (!pglDebugMessageCallback) { ZC_ErrorLogger::Err("glDebugMessageCallback SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)SDL_GL_GetProcAddress("glDebugMessageControl");
    if (!pglDebugMessageControl) { ZC_ErrorLogger::Err("glDebugMessageControl SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    //  shader
    pglCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
    if (!pglCreateProgram) { ZC_ErrorLogger::Err("glCreateProgram SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
    if (!pglAttachShader) { ZC_ErrorLogger::Err("glAttachShader SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
    if (!pglLinkProgram) { ZC_ErrorLogger::Err("glLinkProgram SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");
    if (!pglGetProgramiv) { ZC_ErrorLogger::Err("glGetProgramiv SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
    if (!pglGetProgramInfoLog) { ZC_ErrorLogger::Err("glGetProgramInfoLog SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
    if (!pglDeleteShader) { ZC_ErrorLogger::Err("glDeleteShader SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
    if (!pglCreateShader) { ZC_ErrorLogger::Err("glCreateShader SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
    if (!pglShaderSource) { ZC_ErrorLogger::Err("glShaderSource SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
    if (!pglCompileShader) { ZC_ErrorLogger::Err("glCompileShader SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglGetShaderiv = (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv");
    if (!pglGetShaderiv) { ZC_ErrorLogger::Err("glGetShaderiv SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");
    if (!pglGetShaderInfoLog) { ZC_ErrorLogger::Err("glGetShaderInfoLog SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");
    if (!pglDeleteProgram) { ZC_ErrorLogger::Err("glDeleteProgram SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
    if (!pglUseProgram) { ZC_ErrorLogger::Err("glUseProgram SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)SDL_GL_GetProcAddress("glGetUniformLocation");
    if (!pglGetUniformLocation) { ZC_ErrorLogger::Err("glGetUniformLocation SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)SDL_GL_GetProcAddress("glUniformMatrix4fv");
    if (!pglUniformMatrix4fv) { ZC_ErrorLogger::Err("glUniformMatrix4fv SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    //  buffer
    pglGenBuffers = (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers");
    if (!pglGenBuffers) { ZC_ErrorLogger::Err("glGenBuffers SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglDeleteBuffers = (PFNGLDELETEBUFFERSPROC)SDL_GL_GetProcAddress("glDeleteBuffers");
    if (!pglDeleteBuffers) { ZC_ErrorLogger::Err("glDeleteBuffers SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglBindBuffer = (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer");
    if (!pglBindBuffer) { ZC_ErrorLogger::Err("glBindBuffer SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglBufferData = (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData");
    if (!pglBufferData) { ZC_ErrorLogger::Err("glBufferData SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglBufferSubData = (PFNGLBUFFERSUBDATAPROC)SDL_GL_GetProcAddress("glBufferSubData");
    if (!pglBufferSubData) { ZC_ErrorLogger::Err("glBufferSubData SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    //  vbo
    pglBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)SDL_GL_GetProcAddress("glBindVertexBuffer");
    if (!pglBindVertexBuffer) { ZC_ErrorLogger::Err("glBindVertexBuffer SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    //  vao
    pglGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glGenVertexArrays");
    if (!pglGenVertexArrays) { ZC_ErrorLogger::Err("glGenVertexArrays SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glDeleteVertexArrays");
    if (!pglDeleteVertexArrays) { ZC_ErrorLogger::Err("glDeleteVertexArrays SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)SDL_GL_GetProcAddress("glBindVertexArray");
    if (!pglBindVertexArray) { ZC_ErrorLogger::Err("glBindVertexArray SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glEnableVertexAttribArray");
    if (!pglEnableVertexAttribArray) { ZC_ErrorLogger::Err("glEnableVertexAttribArray SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glDisableVertexAttribArray");
    if (!pglDisableVertexAttribArray) { ZC_ErrorLogger::Err("glDisableVertexAttribArray SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)SDL_GL_GetProcAddress("glVertexAttribPointer");
    if (!pglVertexAttribPointer) { ZC_ErrorLogger::Err("glVertexAttribPointer SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglDrawArrays = (PFNGLDRAWARRAYSPROC)SDL_GL_GetProcAddress("glDrawArrays");
    if (!pglDrawArrays) { ZC_ErrorLogger::Err("glDrawArrays SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)SDL_GL_GetProcAddress("glVertexAttribFormat");
    if (!pglVertexAttribFormat) { ZC_ErrorLogger::Err("glVertexAttribFormat SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    pglVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)SDL_GL_GetProcAddress("glVertexAttribBinding");
    if (!pglVertexAttribBinding) { ZC_ErrorLogger::Err("glVertexAttribBinding SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    // //  va
    // pglCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glCreateVertexArrays");
    // if (!pglCreateVertexArrays) { ZC_ErrorLogger::Err("glCreateVertexArrays SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    // pglEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC)SDL_GL_GetProcAddress("glEnableVertexArrayAttrib");
    // if (!pglEnableVertexArrayAttrib) { ZC_ErrorLogger::Err("glEnableVertexArrayAttrib SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    // pglVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC)SDL_GL_GetProcAddress("glVertexArrayAttribFormat");
    // if (!pglVertexArrayAttribFormat) { ZC_ErrorLogger::Err("glVertexArrayAttribFormat SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    // pglVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC)SDL_GL_GetProcAddress("glVertexArrayAttribBinding");
    // if (!pglVertexArrayAttribBinding) { ZC_ErrorLogger::Err("glVertexArrayAttribBinding SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}
    // pglVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC)SDL_GL_GetProcAddress("glVertexArrayVertexBuffer");
    // if (!pglVertexArrayVertexBuffer) { ZC_ErrorLogger::Err("glVertexArrayVertexBuffer SDL_GL_GetProcAddress faild!", __FILE__, __LINE__); return false;}

    // auto q = glGetString(GL_VERSION);
    // std::string a(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    // std::string b(reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    // std::string c(reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS)));

    return true;
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
PFNGLGETUNIFORMLOCATIONPROC pglGetUniformLocation = nullptr;
PFNGLUNIFORMMATRIX4FVPROC pglUniformMatrix4fv = nullptr;

//  buffer
PFNGLGENBUFFERSPROC pglGenBuffers = nullptr;
PFNGLDELETEBUFFERSPROC pglDeleteBuffers = nullptr;
PFNGLBINDBUFFERPROC pglBindBuffer = nullptr;
PFNGLBUFFERDATAPROC pglBufferData = nullptr;
PFNGLBUFFERSUBDATAPROC pglBufferSubData = nullptr;

//  vbo
PFNGLBINDVERTEXBUFFERPROC pglBindVertexBuffer = nullptr;

//  vao
PFNGLGENVERTEXARRAYSPROC pglGenVertexArrays = nullptr;
PFNGLDELETEVERTEXARRAYSPROC pglDeleteVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC pglBindVertexArray = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC pglEnableVertexAttribArray = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC pglDisableVertexAttribArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC pglVertexAttribPointer = nullptr;
PFNGLDRAWARRAYSPROC pglDrawArrays = nullptr;
PFNGLVERTEXATTRIBFORMATPROC pglVertexAttribFormat = nullptr;
PFNGLVERTEXATTRIBBINDINGPROC pglVertexAttribBinding = nullptr;

// //  va
// PFNGLCREATEVERTEXARRAYSPROC pglCreateVertexArrays = nullptr;
// PFNGLENABLEVERTEXARRAYATTRIBPROC pglEnableVertexArrayAttrib = nullptr;
// PFNGLVERTEXARRAYATTRIBFORMATPROC pglVertexArrayAttribFormat = nullptr;
// PFNGLVERTEXARRAYATTRIBBINDINGPROC pglVertexArrayAttribBinding = nullptr;
// PFNGLVERTEXARRAYVERTEXBUFFERPROC pglVertexArrayVertexBuffer = nullptr;
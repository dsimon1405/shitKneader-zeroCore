#pragma once

#include <SDL3/SDL_opengl.h>
// #include <GL/glcorearb.h>

void ZC_SDL_LoadOpenGL();

//  clear
typedef void (* PFNGLCLEARPROC) (GLbitfield mask);
extern PFNGLCLEARPROC pglClear;
#define glClear pglClear

typedef void (* PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern PFNGLCLEARCOLORPROC pglClearColor;
#define glClearColor pglClearColor

//  get
typedef const GLubyte* (* PFNGLGETSTRINGPROC) (GLenum name);
extern PFNGLGETSTRINGPROC pglGetString;
#define glGetString pglGetString

typedef void (* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *data);
extern PFNGLGETINTEGERVPROC pglGetIntegerv;
#define glGetIntegerv pglGetIntegerv

//  enable
typedef void (* PFNGLENABLEPROC) (GLenum cap);
extern PFNGLENABLEPROC pglEnable;
#define glEnable pglEnable

//  debug
typedef void (* PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);
extern PFNGLDEBUGMESSAGECALLBACKPROC pglDebugMessageCallback;
#define glDebugMessageCallback pglDebugMessageCallback

typedef void (* PFNGLDEBUGMESSAGECONTROLPROC) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
extern PFNGLDEBUGMESSAGECONTROLPROC pglDebugMessageControl;
#define glDebugMessageControl pglDebugMessageControl
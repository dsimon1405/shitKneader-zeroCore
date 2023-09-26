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

//  shader
typedef GLuint (* PFNGLCREATEPROGRAMPROC) (void);
extern PFNGLCREATEPROGRAMPROC pglCreateProgram;
#define glCreateProgram pglCreateProgram

typedef void (* PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
extern PFNGLATTACHSHADERPROC pglAttachShader;
#define glAttachShader pglAttachShader

typedef void (* PFNGLLINKPROGRAMPROC) (GLuint program);
extern PFNGLLINKPROGRAMPROC pglLinkProgram;
#define glLinkProgram pglLinkProgram

typedef void (* PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
extern PFNGLGETPROGRAMIVPROC pglGetProgramiv;
#define glGetProgramiv pglGetProgramiv

typedef void (* PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
extern PFNGLGETPROGRAMINFOLOGPROC pglGetProgramInfoLog;
#define glGetProgramInfoLog pglGetProgramInfoLog

typedef void (* PFNGLDELETESHADERPROC) (GLuint shader);
extern PFNGLDELETESHADERPROC pglDeleteShader;
#define glDeleteShader pglDeleteShader

typedef GLuint (* PFNGLCREATESHADERPROC) (GLenum type);
extern PFNGLCREATESHADERPROC pglCreateShader;
#define glCreateShader pglCreateShader

typedef void (* PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
extern PFNGLSHADERSOURCEPROC pglShaderSource;
#define glShaderSource pglShaderSource

typedef void (* PFNGLCOMPILESHADERPROC) (GLuint shader);
extern PFNGLCOMPILESHADERPROC pglCompileShader;
#define glCompileShader pglCompileShader

typedef void (* PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
extern PFNGLGETSHADERIVPROC pglGetShaderiv;
#define glGetShaderiv pglGetShaderiv

typedef void (* PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
extern PFNGLGETSHADERINFOLOGPROC pglGetShaderInfoLog;
#define glGetShaderInfoLog pglGetShaderInfoLog

typedef void (* PFNGLDELETEPROGRAMPROC) (GLuint program);
extern PFNGLDELETEPROGRAMPROC pglDeleteProgram;
#define glDeleteProgram pglDeleteProgram

typedef void (* PFNGLUSEPROGRAMPROC) (GLuint program);
extern PFNGLUSEPROGRAMPROC pglUseProgram;
#define glUseProgram pglUseProgram

//  buffer
typedef void (* PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
extern PFNGLGENBUFFERSPROC pglGenBuffers;
#define glGenBuffers pglGenBuffers

typedef void (* PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
extern PFNGLDELETEBUFFERSPROC pglDeleteBuffers;
#define glDeleteBuffers pglDeleteBuffers

typedef void (* PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
extern PFNGLBINDBUFFERPROC pglBindBuffer;
#define glBindBuffer pglBindBuffer

//  VAO
typedef void (* PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
extern PFNGLGENVERTEXARRAYSPROC pglGenVertexArrays;
#define glGenVertexArrays pglGenVertexArrays

typedef void (* PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
extern PFNGLDELETEVERTEXARRAYSPROC pglDeleteVertexArrays;
#define glDeleteVertexArrays pglDeleteVertexArrays

typedef void (* PFNGLBINDVERTEXARRAYPROC) (GLuint array);
extern PFNGLBINDVERTEXARRAYPROC pglBindVertexArray;
#define glBindVertexArray pglBindVertexArray

typedef void (* PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
extern PFNGLBUFFERDATAPROC pglBufferData;
#define glBufferData pglBufferData

typedef void (* PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
extern PFNGLENABLEVERTEXATTRIBARRAYPROC pglEnableVertexAttribArray;
#define glEnableVertexAttribArray pglEnableVertexAttribArray

typedef void (* PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
extern PFNGLVERTEXATTRIBPOINTERPROC pglVertexAttribPointer;
#define glVertexAttribPointer pglVertexAttribPointer

typedef void (* PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
extern PFNGLDRAWARRAYSPROC pglDrawArrays;
#define glDrawArrays pglDrawArrays
#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
// #include <GL/glcorearb.h>
#include <ZC/ErrorLogger/ZC_ErroLogger.h>

void LoadOpenGL();

typedef void (* PFNGLCLEARPROC) (GLbitfield mask);
extern PFNGLCLEARPROC pglClear;
#define glClear pglClear
typedef void (* PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern PFNGLCLEARCOLORPROC pglClearColor;
#define glClearColor pglClearColor

#include <ZC/Renderer/ZC_Buffer.h>

#include <ZC/ZC_OpenGL.h>

ZC_Buffer::ZC_Buffer()
{
    glGenBuffers(1, &id);
}
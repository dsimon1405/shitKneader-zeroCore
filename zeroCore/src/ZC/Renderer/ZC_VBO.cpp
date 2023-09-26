#include <ZC/Renderer/ZC_VBO.h>

#include <ZC/ZC_OpenGL.h>

ZC_VBO::~ZC_VBO()
{
    Unbind();
    glDeleteBuffers(1, &id);
}

void ZC_VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void ZC_VBO::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
#include <ZC/Renderer/ZC_VAO.h>

#include <ZC/ZC_OpenGL.h>

ZC_VAO::ZC_VAO()
{
    glGenVertexArrays(1, &id);
}

ZC_VAO::~ZC_VAO()
{
    Unbind();
    glDeleteVertexArrays(1, &id);
}

void ZC_VAO::Bind() const
{
    glBindVertexArray(id);
}

void ZC_VAO::Unbind() const
{
    glBindVertexArray(0);
}
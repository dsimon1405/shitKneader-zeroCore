#include <ZC/ZC_Window.h>

#include <ZC/ZC_OpenGL.h>

void ZC_Window::SetClearColor(const float& r, const float& g, const float& b)
{
    red = r;
    green = g;
    blue = b;
    glClearColor(red, green, blue, 1);
}    

void ZC_Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
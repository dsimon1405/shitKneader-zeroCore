#include <ZC/Video/ZC_Window.h>

int ZC_Window::GetWidth() const noexcept
{
    return width;
}

int ZC_Window::GetHeight() const noexcept
{
    return height;
}

void ZC_Window::SetClearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1);
}    

void ZC_Window::Clear(GLbitfield mask)
{
    glClear(mask);
}
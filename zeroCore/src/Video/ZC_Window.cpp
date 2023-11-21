#include <ZC/Video/ZC_Window.h>

void ZC_Window::SetClearColor(const float& r, const float& g, const float& b) noexcept
{
    glClearColor(r, g, b, 1);
}    

void ZC_Window::Clear(const GLbitfield& mask) noexcept
{
    glClear(mask);
}

int ZC_Window::GetWidth() const noexcept
{
    return width;
}

int ZC_Window::GetHeight() const noexcept
{
    return height;
}

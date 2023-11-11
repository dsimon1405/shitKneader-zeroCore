#include <ZC/Video/ZC_Window.h>

void ZC_Window::SetClearColor(const float& r, const float& g, const float& b)
{
    glClearColor(r, g, b, 1);
}    

void ZC_Window::Clear(const GLbitfield& mask)
{
    glClear(mask);
}
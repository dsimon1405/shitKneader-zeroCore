#include <ZC/API/PC/SDL/ZC_SDL_Window.h>

#include <ZC/API/PC/SDL/ZC_SDL_OpenGL.h>

ZC_SDL_Window::ZC_SDL_Window(const char* name, const int& width, const int& height)
{
    if (width <= 0 && height <= 0)
    {
        window = SDL_CreateWindow(name, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        window = SDL_CreateWindowWithPosition(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    }
    
    glContext = SDL_GL_CreateContext(window);
}

ZC_SDL_Window::~ZC_SDL_Window()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
}

void ZC_SDL_Window::Clear()
{
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool ZC_SDL_Window::HandleEvents()
{
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return false;
        }
    }

    return true;
}

void ZC_SDL_Window::SwapBuffer()
{
    SDL_GL_SwapWindow(window);  
}
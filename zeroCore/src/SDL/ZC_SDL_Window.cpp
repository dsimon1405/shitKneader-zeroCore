#include <ZC/SDL/ZC_SDL_Window.h>

ZC_SDL_Window::ZC_SDL_Window(const int& width, const int& height, const int& xPos, const int& yPos, const char* name)
{
    window = SDL_CreateWindowWithPosition(name, xPos, yPos, width, height,  SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
}

ZC_SDL_Window::ZC_SDL_Window(const int& width, const int& height, const char* name)
{
    LoadOpenGL();
    window = SDL_CreateWindowWithPosition(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
}

ZC_SDL_Window::ZC_SDL_Window(const char* name)
{
    window = SDL_CreateWindow(name, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
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

void ZC_SDL_Window::MainLoop(void(*pGameLoop)())
{
    SDL_Event event;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        if (running)
        {
            Clear();

            pGameLoop();

            SDL_GL_SwapWindow(window);  
        }
    }
}
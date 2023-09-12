#pragma once

#include <ZC/ZC_Window.h>
#include <SDL3/SDL.h>

class ZC_SDL_Window : public ZC_Window
{
public:
    ZC_SDL_Window(const char* name = "", const int& width = 0, const int& height = 0);
    ~ZC_SDL_Window();
    virtual bool HandleEvents() override;
    virtual void SwapBuffer() override;

private:
    SDL_Window* window;
    SDL_GLContext glContext;
};


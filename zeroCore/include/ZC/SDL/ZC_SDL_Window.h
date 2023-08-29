#pragma once

#include <ZC/ZC_Window.h>
#include <ZC/ErrorLogger/ZC_ErroLogger.h>
#include <SDL3/SDL.h>
#include <ZC/SDL/ZC_SDL_OpenGL.h>

class ZC_SDL_Window : public ZC_Window
{
public:
    ZC_SDL_Window(const int& width, const int& height, const int& xPos, const int& yPos, const char* name = "");
    ZC_SDL_Window(const int& width, const int& height, const char* name = "");
    ZC_SDL_Window(const char* name = "");
    ~ZC_SDL_Window();
    virtual void Clear() override;
    virtual void MainLoop(void(*pGameLoop)()) override;

    SDL_Window* window;
private:
    SDL_GLContext glContext;
};


#pragma once

#include <ZC/Video/ZC_Window.h>
#include <ZC/Video/OpenGL/ZC_OpenGL.h>

#include <SDL3/SDL_video.h>

class ZC_SDL_Window : public ZC_Window
{
public:
    ZC_SDL_Window(const char* name = "", int width = 0, int height = 0);

    ~ZC_SDL_Window() override;

    bool HandleEvents() override;
    void SwapBuffer() override;

private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;

    bool SetOpenGLAttributes();
};
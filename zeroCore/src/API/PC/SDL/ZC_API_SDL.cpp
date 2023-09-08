#include <ZC/API/PC/SDL/ZC_API_SDL.h>

#include <ZC/API/PC/SDL/ZC_SDL_Window.h>
#include <ZC_EL.h>
#include <ZC/API/PC/SDL/ZC_SDL_OpenGL.h>

ZC_API_SDL::ZC_API_SDL()
{
    static bool initiated = false;
    if (!initiated)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            ZC_Err("SDL_Init - " + std::string(SDL_GetError()));
        
        ZC_SDL_LoadOpenGL();
    }
    else
    {
        ZC_Wrn("SDL allready initiated!");
    }
}

ZC_pWindow ZC_API_SDL::CreateWindow(const char* name, const int& width, const int& height)
{
    return std::dynamic_pointer_cast<ZC_Window>(std::make_shared<ZC_SDL_Window>(name, width, height));
}

ZC_pAPIFactory ZC_API_SDL::GetAPI()
{
    return std::dynamic_pointer_cast<ZC_APIFactory>(std::make_shared<ZC_API_SDL>());
}
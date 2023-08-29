#include <ZC/SDL/ZC_API_SDL.h>

ZC_API_SDL::ZC_API_SDL()
{
    static bool initiated = false;
    if (!initiated)
    {
        if(!initiated && SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
           ZC_Err("SDL_Init - " + std::string(SDL_GetError()));
        }
    }
    else
    {
        ZC_Wrn("SDL allready initiated!");
    }
}

ZC_pWindow ZC_API_SDL::CreateWindowPositioned(const int& width, const int& height, const int& xPos, const int& yPos, const char* name)
{
    return std::dynamic_pointer_cast<ZC_Window>(std::make_shared<ZC_SDL_Window>(width, height, xPos, yPos, name));
}

ZC_pWindow ZC_API_SDL::CreateWindowCentered(const int& width, const int& height, const char* name)
{
    return std::dynamic_pointer_cast<ZC_Window>(std::make_shared<ZC_SDL_Window>(width, height, name));
}

ZC_pWindow ZC_API_SDL::CreateWindowFullScrean(const char* name)
{
    return std::dynamic_pointer_cast<ZC_Window>(std::make_shared<ZC_SDL_Window>(name));
}

ZC_pAPIFactory ZC_GetAPI_SDL()
{
    return std::dynamic_pointer_cast<ZC_APIFactory>(std::make_shared<ZC_API_SDL>());
}
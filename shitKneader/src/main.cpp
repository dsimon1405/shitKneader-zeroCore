#include <ZC/SDL/ZC_API_SDL.h>

void GameLoop();

int main(int argv, char** args)
{
    ZC_pAPIFactory api = ZC_GetAPI_SDL();
    ZC_pWindow window = api->CreateWindowCentered(640, 480, "lolka");

    window->MainLoop(GameLoop);

    return 0;
}

void GameLoop()
{
    
}
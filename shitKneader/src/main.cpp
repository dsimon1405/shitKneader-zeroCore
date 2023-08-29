
#include <ZC/SDL/ZC_API_SDL.h>
#include <ZC/ErrorLogger/ZC_ErroLogger.h>
#include <thread>
#include <chrono>
#include <ZC_Config.h>
#include <iostream>
#include <string_view>

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
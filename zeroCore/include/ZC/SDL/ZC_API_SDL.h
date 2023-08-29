#pragma once

#include <ZC/ZC_APIFactory.h>
#include <ZC/SDL/ZC_SDL_Window.h>
#include <ZC/ErrorLogger/ZC_ErroLogger.h>

class ZC_API_SDL : public ZC_APIFactory
{
public:
    ZC_API_SDL();
    virtual ZC_pWindow CreateWindowPositioned(const int& width, const int& height, const int& xPos, const int& yPos, const char* name = "") override;
    virtual ZC_pWindow CreateWindowCentered(const int& width, const int& height, const char* name = "") override;
    virtual ZC_pWindow CreateWindowFullScrean(const char* name = "") override;
};

ZC_pAPIFactory ZC_GetAPI_SDL();

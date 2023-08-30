#pragma once

#include <ZC/ZC_Window.h>
#include <memory>

class ZC_APIFactory
{
public:
    virtual ZC_pWindow CreateWindowPositioned(const int& width, const int& height, const int& xPos, const int& yPos, const char* name = "") = 0;
    virtual ZC_pWindow CreateWindowCentered(const int& width, const int& height, const char* name = "") = 0;
    virtual ZC_pWindow CreateWindowFullScrean(const char* name = "") = 0;
};

using ZC_pAPIFactory = std::shared_ptr<ZC_APIFactory>;
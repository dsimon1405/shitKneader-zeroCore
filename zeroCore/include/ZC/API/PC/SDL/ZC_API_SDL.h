#pragma once

#include <ZC/ZC_APIFactory.h>

class ZC_API_SDL : public ZC_APIFactory
{
public:
    ZC_API_SDL();
    virtual ZC_pWindow CreateWindow(const char* name = "", const int& width = 0, const int& height = 0) override;

    static ZC_pAPIFactory GetAPI();
};

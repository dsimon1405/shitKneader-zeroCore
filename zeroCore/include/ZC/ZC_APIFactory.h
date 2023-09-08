#pragma once

#include <ZC/ZC_Window.h>
#include <memory>

class ZC_APIFactory;
using ZC_pAPIFactory = std::shared_ptr<ZC_APIFactory>;

class ZC_APIFactory
{
public:
    virtual ZC_pWindow MakeWindow( const char* name = "", const int& width = 0, const int& height = 0) = 0;

    static ZC_pAPIFactory GetApiFactory();
};
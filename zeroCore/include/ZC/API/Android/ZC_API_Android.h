#pragma once

#include <ZC/ZC_APIFactory.h>
#include <ZC/API/Android/ZC_A_Window.h>

class ZC_API_Android : public ZC_APIFactory
{
public:
    ZC_API_Android(std::shared_ptr<ZC_A_Window> win);
    virtual ZC_pWindow CreateWindow(const char* name = "", const int& width = 0, const int& height = 0) override;
    static ZC_pAPIFactory ZC_GetAPI(std::shared_ptr<ZC_A_Window> win);
private:
    std::shared_ptr<ZC_A_Window> window;
};


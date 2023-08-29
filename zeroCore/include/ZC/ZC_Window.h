#pragma once

#include <ZC/ZC_Noncopyable.h>
#include <memory>
#include <iostream>

class ZC_Window : public ZC_Noncopyable
{
public:
    ZC_Window() = default;
    virtual void MainLoop(void(*pGameLoop)()) = 0;
    virtual void Clear() = 0;
private:
};

using ZC_pWindow = std::shared_ptr<ZC_Window>;
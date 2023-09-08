#pragma once

#include <ZC/ZC_Noncopyable.h>
#include <memory>

class ZC_Window : public ZC_Noncopyable
{
public:
    ZC_Window() = default;
    virtual bool HandleEvents() = 0;
    virtual void Clear() = 0;
    virtual void SwapBuffer() = 0;
private:
};

using ZC_pWindow = std::shared_ptr<ZC_Window>;
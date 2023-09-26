#pragma once

#include <ZC/ZC_Noncopyable.h>
#include <memory>
#include <ZC/ZC_OpenGL.h>

class ZC_Window : public ZC_Noncopyable
{
public:
    virtual bool HandleEvents() = 0;
    virtual void SwapBuffer() = 0;

    void SetClearColor(const float& r, const float& g, const float& b);
    void Clear();
    bool inited = false;
protected:
    float red = 0.0f, green = 0.0f, blue = 0.0f;
    
    ZC_Window() = default;
};

using ZC_pWindow = std::shared_ptr<ZC_Window>;
#pragma once

#include <ZC/Video/OpenGL/ZC_OpenGL.h>

#include <memory>

class ZC_Window
{
public:
    ZC_Window(const ZC_Window&) = delete;
    ZC_Window& operator = (const ZC_Window&) = delete;
    ZC_Window(ZC_Window&&) = delete;
    ZC_Window& operator = (ZC_Window&&) = delete;

    virtual ~ZC_Window() = default;
    
    /*
    Handle input events.

    Return:
    If there was an event that required closing the window, false, otherwise true.
    */
    virtual bool HandleEvents() noexcept = 0;

    /*
    Update a window with OpenGL rendering.
    */
    virtual void SwapBuffer() noexcept = 0;

    /*
    Set the window buffer clear color.

    Params:
    r - red color.
    g - green color.
    b - blue color.
    */
    void SetClearColor(const float& r, const float& g, const float& b);

    /*
    Clear the window buffer.
    */
    void Clear(const GLbitfield& mask = GL_COLOR_BUFFER_BIT);

    //  test data
    bool inited = false;    //  удалить

protected:
    
    ZC_Window() = default;
};
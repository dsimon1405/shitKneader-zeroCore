#pragma once

#include <ZC/Video/OpenGL/ZC_OpenGL.h>
#include <ZC/Tools/Math/ZC_Vec.h>

#include <memory>

class ZC_Window
{
public:
    ZC_Window(const ZC_Window&) = delete;
    ZC_Window& operator = (const ZC_Window&) = delete;

    ZC_Window(ZC_Window&& win) = delete;
    ZC_Window& operator = (ZC_Window&& win) = delete;

    virtual ~ZC_Window() = default;
    
    /*
    Handle input events.

    Return:
    If there was an event that required closing the window, false, otherwise true.
    */
    virtual bool HandleEvents() noexcept = 0;

    /*
    Changes the current buffer to a buffer with a prepared sketch
    */
    virtual void SwapBuffer() noexcept = 0;
    
    /*
    Returns the width of the window.
    */
    int GetWidth() const noexcept;
    
    /*
    Returns the height and height of the window.
    */
    int GetHeight() const noexcept;

    /*
    Set the window buffer clear color.

    Params:
    r - red color.
    g - green color.
    b - blue color.
    */
    void SetClearColor(const float& r, const float& g, const float& b) noexcept;

    /*
    Clear the window buffer.
    */
    void Clear(const GLbitfield& mask = GL_COLOR_BUFFER_BIT) noexcept;

protected:
    int width = 0,
        height = 0;

    ZC_Window() = default;
};
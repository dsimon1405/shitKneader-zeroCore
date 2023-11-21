#pragma once

#include <ZC/Video/ZC_Window.h>
#include "ZC_android_app.h"

// #include <android/input.h>
#include <EGL/egl.h>

class ZC_AndroidNativeAppGlue_Window : public ZC_Window, public ZC_android_app
{
public:
    ZC_AndroidNativeAppGlue_Window(const char* const& name, const int& width, const int& height) noexcept;
    
    ~ZC_AndroidNativeAppGlue_Window() override = default;

    bool HandleEvents() noexcept override;
    void SwapBuffer() noexcept override;

private:
    EGLDisplay display = nullptr;
    EGLSurface surface = nullptr;
    EGLContext context = nullptr;
    // int width = 0;
    // int height = 0;
//    int currentFrame = 0;

    static void HandleCMD(struct android_app* app, int cmd);
    static int HandleInput(struct android_app* app, AInputEvent* pEvent);

    bool InitGraphicOpenGL(ANativeWindow* const& pWindow) noexcept;
    void CloseGraphicOpenGL() noexcept;
};


#pragma once

#include <ZC/ZC_Window.h>

// #include <android/input.h>
#include <android_native_app_glue.h>
#include <EGL/egl.h>

class ZC_A_Window : public ZC_Window
{
public:
    ZC_A_Window(android_app* androidApp);
    virtual bool HandleEvents() override;
    virtual void SwapBuffer() override;

    bool InitGraphicOpenGL(ANativeWindow* pWindow);
    void CloseGraphicOpenGL();

    static void HandleCMD(struct android_app* app, int cmd);
    static int HandleInput(struct android_app* app, AInputEvent* pEvent);

    void ResetClearColor();

private:
    enum State
    {
        pause = -1,
        active = 0
    };

    android_app* pAndroidApp;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int width = 0;
    int height = 0;
    State state = pause;
//    int currentFrame = 0;
};


#pragma once

#include <ZC/ZC_Window.h>

// #include <android/input.h>
#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

class ZC_A_Window : public ZC_Window
{
public:
    ZC_A_Window(android_app* androidApp);
    virtual bool HandleEvents() override;
    virtual void Clear() override;
    virtual void SwapBuffer() override;
    bool InitGraphic_OpenGL(ANativeWindow* pWindow);
    void CloseGraphic_OpenGL();
    static void HandleCMD(struct android_app* app, int32_t cmd);
    static int32_t HandleInput(struct android_app* app, AInputEvent* pEvent);
    
    float r = 0.0f, g = 0.0f, b = 0.0f;
    bool m_IsPause = false;
    bool m_IsGraphicInited = false;
    int currentFrame = 0;

private:
    android_app* pAndroidApp;
    EGLDisplay m_Display;
    EGLSurface m_Surface;
    EGLContext m_Context;
    int32_t m_Width = 0;
    int32_t m_Height = 0;
};


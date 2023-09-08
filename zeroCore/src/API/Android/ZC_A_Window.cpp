#include <ZC/API/Android/ZC_A_Window.h>

ZC_A_Window::ZC_A_Window(android_app* androidApp)
    : pAndroidApp(androidApp)
{
    pAndroidApp->userData = this;
    pAndroidApp->onAppCmd = HandleCMD;
    pAndroidApp->onInputEvent = HandleInput;
}

bool ZC_A_Window::HandleEvents()
{
    static int ident;
    static int events;
    static struct android_poll_source* source;
        
    if ((ident = ALooper_pollOnce(0 /* -1 0 */, nullptr, &events,(void**)&source)) >= 0)
    {
        // Process this event.
        if (source != nullptr) {
            source->process(pAndroidApp, source);
        }

        // stop application
        if (pAndroidApp->destroyRequested != 0)
        {
            CloseGraphic_OpenGL();
            return false;
        }
    }
    return true;
}

void ZC_A_Window::Clear()
{
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ZC_A_Window::SwapBuffer()
{
    currentFrame++;
    eglSwapBuffers(m_Display, m_Surface);
}
    
bool ZC_A_Window::InitGraphic_OpenGL(ANativeWindow* pWindow)
{
    const EGLint attribs[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                              EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                              EGL_BLUE_SIZE,    8,
                              EGL_GREEN_SIZE,   8,
                              EGL_RED_SIZE,     8,
                              EGL_NONE};
    EGLint w, h, format;
    EGLint numConfigs;
    EGLConfig config = nullptr;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, nullptr, nullptr);

    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    surface = eglCreateWindowSurface(display, config, pWindow, NULL);

    EGLint contextAttribs[] =
            {
                    EGL_CONTEXT_CLIENT_VERSION, 2,
                    EGL_NONE
            };
    context = eglCreateContext(display, config, NULL, contextAttribs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
        return false;

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    m_Display = display;
    m_Context = context;
    m_Surface = surface;
    m_Width = w;
    m_Height = h;

    // Open GL states
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    return true;
}

void ZC_A_Window::CloseGraphic_OpenGL()
{
    if (m_Display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (m_Context != EGL_NO_CONTEXT) {
            eglDestroyContext(m_Display, m_Context);
        }

        if (m_Surface != EGL_NO_SURFACE) {
            eglDestroySurface(m_Display, m_Surface);
        }

        eglTerminate(m_Display);
    }

    m_Display = EGL_NO_DISPLAY;
    m_Context = EGL_NO_CONTEXT;
    m_Surface = EGL_NO_SURFACE;
}



int32_t ZC_A_Window::HandleInput(struct android_app* app, AInputEvent* pEvent)
{
    ZC_A_Window* pWindow = (ZC_A_Window*)app->userData;
    static int frame = 0;
    if (pWindow->currentFrame != frame)
    {
        frame = pWindow->currentFrame;
        if (AInputEvent_getType(pEvent) == AINPUT_EVENT_TYPE_MOTION)
        {
            auto x = AMotionEvent_getX(pEvent, 0);
            auto y = AMotionEvent_getY(pEvent, 0);

            if (x <= 360 && y <= 730)
            {
                pWindow->r = 1;
                pWindow->g = 0;
                pWindow->b = 0;
            }
            if (x >= 360 && y <= 730)
            {
                pWindow->r = 0;
                pWindow->g = 1;
                pWindow->b = 0;
            }
            if (x <= 360 && y >= 730)
            {
                pWindow->r = 0;
                pWindow->g = 0;
                pWindow->b = 1;
            }
            if (x >= 360 && y >= 730)
            {
                pWindow->r = 0;
                pWindow->g = 0;
                pWindow->b = 0;
            }

            return 1;
        }
    }
    return true;
}

void ZC_A_Window::HandleCMD(struct android_app* app, int32_t cmd)
{
    ZC_A_Window* pWindow = (ZC_A_Window*)app->userData;

    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            break;

        case APP_CMD_INIT_WINDOW:
            if (app->window != nullptr)
            {
                if (!pWindow->m_IsGraphicInited)
                    pWindow->m_IsGraphicInited = pWindow->InitGraphic_OpenGL(app->window);
            }
            break;

        case APP_CMD_TERM_WINDOW:
        {
            // The window is being hidden or closed, clean it up.
            pWindow->CloseGraphic_OpenGL();
            pWindow->m_IsGraphicInited = false;
            break;
        }

        case APP_CMD_GAINED_FOCUS:
        {
            pWindow->m_IsPause = false;
            // pWindow->OnActiveFocus();
            break;
        }

        case APP_CMD_LOST_FOCUS:
        {
            pWindow->m_IsPause = true;
            // pWindow->OnLostFocus();
            break;
        }

        default:
            break;
    }
}


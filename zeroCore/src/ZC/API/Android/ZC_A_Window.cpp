#include <ZC/API/Android/ZC_A_Window.h>

#include <ZC/ZC_OpenGL.h>
#include <ZC_EL.h>

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

    if ((ident = ALooper_pollOnce( 0 /* pause  -1 0 */, nullptr, &events,(void**)&source)) >= 0)
    {
        // Process this event.
        if (source != nullptr) {
            source->process(pAndroidApp, source);
        }

        // stop application
        if (pAndroidApp->destroyRequested != 0)
        {
            CloseGraphicOpenGL();
            return false;
        }
    }
    return true;
}

void ZC_A_Window::SwapBuffer()
{
//    currentFrame++;
    eglSwapBuffers(display, surface);
}

bool ZC_A_Window::InitGraphicOpenGL(ANativeWindow* pWindow)
{
    const EGLint attribs[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
                              EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                              EGL_BLUE_SIZE,    8,
                              EGL_GREEN_SIZE,   8,
                              EGL_RED_SIZE,     8,
                              EGL_NONE};
    EGLint w, h, format;
    EGLint numConfigs;
    EGLConfig config = nullptr;
    EGLSurface surf;
    EGLContext cont;

    EGLDisplay displ = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(displ, nullptr, nullptr);

    eglChooseConfig(displ, attribs, &config, 1, &numConfigs);

    eglGetConfigAttrib(displ, config, EGL_NATIVE_VISUAL_ID, &format);

    surf = eglCreateWindowSurface(displ, config, pWindow, NULL);

    EGLint contextAttribs[] =
            {
                    EGL_CONTEXT_MAJOR_VERSION, 3,
                    EGL_CONTEXT_MINOR_VERSION, 2,
                    EGL_NONE
            };
    cont = eglCreateContext(displ, config, NULL, contextAttribs);

    if (eglMakeCurrent(displ, surf, surf, cont) == EGL_FALSE)
        return false;
//    GLuint id = 0;
//    glGenBuffers(1, &id);
//    GLuint shader = glCreateShader(GL_GEOMETRY_SHADER);
    eglQuerySurface(displ, surf, EGL_WIDTH, &w);
    eglQuerySurface(displ, surf, EGL_HEIGHT, &h);

    display = displ;
    context = cont;
    surface = surf;
    width = w;
    height = h;

    // Open GL states
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    inited = true;
    return true;
}

void ZC_A_Window::CloseGraphicOpenGL()
{
    if (display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (context != EGL_NO_CONTEXT) {
            eglDestroyContext(display, context);
        }

        if (surface != EGL_NO_SURFACE) {
            eglDestroySurface(display, surface);
        }

        eglTerminate(display);
    }

    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
}



int ZC_A_Window::HandleInput(struct android_app* app, AInputEvent* pEvent)
{
    ZC_A_Window* pWindow = (ZC_A_Window*)app->userData;
//    static int frame = 0;
//    if (pWindow->currentFrame != frame)
//    {
//        frame = pWindow->currentFrame;
//        if (AInputEvent_getType(pEvent) == AINPUT_EVENT_TYPE_MOTION)
//        {
//            auto x = AMotionEvent_getX(pEvent, 0);
//            auto y = AMotionEvent_getY(pEvent, 0);
//
//            if (x <= 360 && y <= 730)
//            {
//                pWindow->red = 1;
//                pWindow->green = 0;
//                pWindow->blue = 0;
//            }
//            if (x >= 360 && y <= 730)
//            {
//                pWindow->red = 0;
//                pWindow->green = 1;
//                pWindow->blue = 0;
//            }
//            if (x <= 360 && y >= 730)
//            {
//                pWindow->red = 0;
//                pWindow->green = 0;
//                pWindow->blue = 1;
//            }
//            if (x >= 360 && y >= 730)
//            {
//                pWindow->red = 0;
//                pWindow->green = 0;
//                pWindow->blue = 0;
//            }
//            pWindow->ResetClearColor();
//            return false;
//        }
//    }
    return true;
}

void ZC_A_Window::HandleCMD(struct android_app* app, int cmd)
{
    ZC_A_Window* pWindow = (ZC_A_Window*)app->userData;

    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            break;

        case APP_CMD_INIT_WINDOW:
            if (app->window != nullptr)
            {
                if(!pWindow->InitGraphicOpenGL(app->window))
                {
                    ZC_Err("InitGraphicOpenGL failed!");
                    break;
                }
                pWindow->ResetClearColor();
            }
            break;

        case APP_CMD_TERM_WINDOW:
        {
            // The window is being hidden or closed, clean it up.
            pWindow->CloseGraphicOpenGL();
            break;
        }

        case APP_CMD_GAINED_FOCUS:
        {
            pWindow->state = ZC_A_Window::State::active;
            break;
        }

        case APP_CMD_LOST_FOCUS:
        {
            pWindow->state = ZC_A_Window::State::pause;
            break;
        }

        default:
            break;
    }
}

void ZC_A_Window::ResetClearColor()
{
    glClearColor(red, green, blue, 1);
}


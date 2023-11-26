#include "ZC_SDL_Window.h"

#include "../../OpenGL/PC/SDL/ZC_SDL_LoadOpenGLFunctions.h"
#include "../../OpenGL/ZC_OpenGLConfig.h"
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>

#include <sstream>

ZC_SDL_Window::ZC_SDL_Window(const char* name, int _width, int _height) noexcept
{
	static bool sdlVideoInited = false;
	if (!sdlVideoInited)
	{
    	if (SDL_Init(SDL_INIT_VIDEO) != 0)
    	{
        	ZC_ErrorLogger::Err("SDL_Init(SDL_INIT_VIDEO) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
			return;
    	}
		sdlVideoInited = true;
	}

    if (!ZC_SDL_LoadOpenGLFunctions()) return;

	if (!SetOpenGLAttributes()) return;

    window = _width <= 0 && _height <= 0 ?
		window = SDL_CreateWindow(name, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN)
		: window = SDL_CreateWindowWithPosition(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL);
    
	if (!window)
	{
		ZC_ErrorLogger::Err("SDL_CreateWindow() fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
		return;
	}

    glContext = SDL_GL_CreateContext(window);
	if (!glContext)
	{
		ZC_ErrorLogger::Err("SDL_GL_CreateContext() fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
		return;
	}

	// ZC_OpenGLAssigneErrorCallback();
	SDL_GetWindowSize(window, &width, &height);
}

ZC_SDL_Window::~ZC_SDL_Window() noexcept
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
}
#include <ZC/Tools/Console/ZC_cout.h>
bool ZC_SDL_Window::HandleEvents() noexcept
{
    static SDL_Event event;
	int count = 0;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return false;
        }

		if (event.type == SDL_EVENT_KEY_DOWN)
		{
		++count;
			// event.motion
			event.key.repeat;
			
			if (event.key.keysym.sym == SDLK_q)
			{
				ZC_cout("q down");
			}
			if (event.key.keysym.sym == SDLK_e)
			{
				ZC_cout("e");
			}
		}
		if (event.type == SDL_EVENT_KEY_UP)
		{
			if (event.key.keysym.sym == SDLK_q)
			{
				ZC_cout("q up");
			}
		}
    }
				if (count > 0) ZC_cout(std::to_string(count));

    return true;
}

void ZC_SDL_Window::SwapBuffer() noexcept
{
    SDL_GL_SwapWindow(window);
}

bool ZC_SDL_Window::SetOpenGLAttributes() noexcept
{
	// if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0)
	// {
	// 	ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
	// 	return false;
	// }
	// if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ZC_OPEN_GL_MAJOR_VERSION) != 0)
	// {
	// 	ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ZC_OPEN_GL_MAJOR_VERSION) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
	// 	return false;
	// }
	// if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ZC_OPEN_GL_MINOR_VERSION) != 0)
	// {
	// 	ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ZC_OPEN_GL_MINOR_VERSION) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
	// 	return false;
	// }
	// if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, ZC_OPEN_GL_COLLOR_BUFFER_SIZE) != 0)
	// {
	// 	ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
	// 	return false;
	// }
	// if (SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, ZC_OPEN_GL_COLLOR_BUFFER_SIZE) != 0)
	// {
	// 	ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
	// 	return false;
	// }
	// if (SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, ZC_OPEN_GL_COLLOR_BUFFER_SIZE) != 0)
	// {
	// 	ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
	// 	return false;
	// }
	// if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, ZC_OPEN_GL_DEPTH_BUFFER_SIZE) != 0)
	// {
	// 	ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
	// 	return false;
	// }

	return true;
}

	// int red = 0;
    // int a999 = SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &red);	//	8
	// int green = 0;
    // int a888 = SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &green);	//	8
	// int blue = 0;
    // int a777 = SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &blue);	//	8
	// int alpha = 0;
    // int a666 = SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &alpha);	//	8
	// int buffer = 0;
    // int a555 = SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &buffer);	//	32
	// int boublebuffer = 0;
    // int a444 = SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &boublebuffer);	//	1 on
	// int depth = 0;
    // int a333 = SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &depth);	//	24
	// int stencil = 0;
    // int a222 = SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &stencil);	//	8
	// int accumRed = 0;
    // int a111 = SDL_GL_GetAttribute(SDL_GL_ACCUM_RED_SIZE, &accumRed);
	// int accumGreen = 0;
    // int a99 = SDL_GL_GetAttribute(SDL_GL_ACCUM_GREEN_SIZE, &accumGreen);
	// int accumBlue = 0;
    // int a88 = SDL_GL_GetAttribute(SDL_GL_ACCUM_BLUE_SIZE, &accumBlue);
	// int accumAlpha = 0;
    // int a77 = SDL_GL_GetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, &accumAlpha);
	// int stereo = 0;
    // int a66 = SDL_GL_GetAttribute(SDL_GL_STEREO, &stereo);
	// int multisamplebuffers = 0;
    // int a55 = SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &multisamplebuffers);
	// int multisampleSamples = 0;
    // int a44 = SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &multisampleSamples);
	// int acceleratedVisual = 0;
    // int a33 = SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &acceleratedVisual);
	// int retainedBacking = 0;
    // int a22 = SDL_GL_GetAttribute(SDL_GL_RETAINED_BACKING, &retainedBacking);
	// int majorVersion = 0;
    // int a11 = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersion);
	// int minorVersion = 0;
    // int a0 = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minorVersion);
	// int contextFlags = 0;
    // int a9 = SDL_GL_GetAttribute(SDL_GL_CONTEXT_FLAGS, &contextFlags);
	// int contextProfileMask = 0;
    // int a8 = SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &contextProfileMask);
	// int shareWithCurrentContext = 0;
    // int a7 = SDL_GL_GetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, &shareWithCurrentContext);
	// int framebufferSRGBcapable = 0;
    // int a6 = SDL_GL_GetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, &framebufferSRGBcapable);
	// int contextReleaseBehavior = 0;
    // int a5 = SDL_GL_GetAttribute(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, &contextReleaseBehavior);
	// int contextResetNotofocation = 0;
    // int a4 = SDL_GL_GetAttribute(SDL_GL_CONTEXT_RESET_NOTIFICATION, &contextResetNotofocation);
	// int contextNoError = 0;
    // int a3 = SDL_GL_GetAttribute(SDL_GL_CONTEXT_NO_ERROR, &contextNoError);
	// int floatBuffers = 0;
    // int a2 = SDL_GL_GetAttribute(SDL_GL_FLOATBUFFERS, &floatBuffers);
	// int eglPlatform = 0;
    // int a1 = SDL_GL_GetAttribute(SDL_GL_EGL_PLATFORM, &eglPlatform);
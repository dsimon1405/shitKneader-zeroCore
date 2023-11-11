#include "ZC_SDL_Window.h"

#include "../../OpenGL/PC/SDL/ZC_SDL_LoadOpenGLFunctions.h"
#include "../../OpenGL/ZC_OpenGLConfig.h"
#include <ZC/ErrorLogger/ZC_ErrorLogger.h>

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>

#include <sstream>

ZC_SDL_Window::ZC_SDL_Window(const char* const& name, const int& width, const int& height) noexcept
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

    window = width <= 0 && height <= 0 ?
		window = SDL_CreateWindow(name, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN)
		: window = SDL_CreateWindowWithPosition(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    
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

	// #ifdef ZC_DEBUG
	// 	// GLint flags;
    // 	// glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	// 	// if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	// 	{
	// 		glEnable(GL_DEBUG_OUTPUT);
	// 		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	// 		glDebugMessageCallback(GLDebugOutput, nullptr);
	// 		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	// 	}
	// #endif
	ZC_OpenGLAssigneErrorCallback();
}

ZC_SDL_Window::~ZC_SDL_Window() noexcept
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
}

bool ZC_SDL_Window::HandleEvents() noexcept
{
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return false;
        }

		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			if (event.key.keysym.sym == SDLK_q)
			{
				
			} 
		}
    }

    return true;
}

void ZC_SDL_Window::SwapBuffer() noexcept
{
    SDL_GL_SwapWindow(window);  
}

// void APIENTRY ZC_SDL_Window::GLDebugOutput(
// 	GLenum source,
// 	GLenum type,
// 	unsigned int id,
// 	GLenum severity,
// 	GLsizei length,
// 	const char* message,
// 	const void* userParam)
// {
// 	// ignore these non-significant error codes
// 	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

//     std::stringstream stream;
//     stream << "Debug message (" << id << "): " << message;

// 	switch (source)
// 	{
// 	case GL_DEBUG_SOURCE_API:             stream << "Source: API"; break;
// 	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   stream << "Source: Window System"; break;
// 	case GL_DEBUG_SOURCE_SHADER_COMPILER: stream << "Source: Shader Compiler"; break;
// 	case GL_DEBUG_SOURCE_THIRD_PARTY:     stream << "Source: Third Party"; break;
// 	case GL_DEBUG_SOURCE_APPLICATION:     stream << "Source: Application"; break;
// 	case GL_DEBUG_SOURCE_OTHER:           stream << "Source: Other"; break;
// 	} stream << std::endl;

// 	switch (type)
// 	{
// 	case GL_DEBUG_TYPE_ERROR:               stream << "Type: Error"; break;
// 	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: stream << "Type: Deprecated Behaviour"; break;
// 	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  stream << "Type: Undefined Behaviour"; break;
// 	case GL_DEBUG_TYPE_PORTABILITY:         stream << "Type: Portability"; break;
// 	case GL_DEBUG_TYPE_PERFORMANCE:         stream << "Type: Performance"; break;
// 	case GL_DEBUG_TYPE_MARKER:              stream << "Type: Marker"; break;
// 	case GL_DEBUG_TYPE_PUSH_GROUP:          stream << "Type: Push Group"; break;
// 	case GL_DEBUG_TYPE_POP_GROUP:           stream << "Type: Pop Group"; break;
// 	case GL_DEBUG_TYPE_OTHER:               stream << "Type: Other"; break;
// 	} stream << std::endl;

// 	switch (severity)
// 	{
// 	case GL_DEBUG_SEVERITY_HIGH:         stream << "Severity: high"; break;
// 	case GL_DEBUG_SEVERITY_MEDIUM:       stream << "Severity: medium"; break;
// 	case GL_DEBUG_SEVERITY_LOW:          stream << "Severity: low"; break;
// 	case GL_DEBUG_SEVERITY_NOTIFICATION: stream << "Severity: notification"; break;
// 	};

//     ZC_ErrorLogger::Err(stream.str(), __FILE__, __LINE__);
// }

bool ZC_SDL_Window::SetOpenGLAttributes() noexcept
{
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0)
	{
		ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ZC_OPEN_GL_MAJOR_VERSION) != 0)
	{
		ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ZC_OPEN_GL_MAJOR_VERSION) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ZC_OPEN_GL_MINOR_VERSION) != 0)
	{
		ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ZC_OPEN_GL_MINOR_VERSION) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, ZC_OPEN_GL_COLLOR_BUFFER_SIZE) != 0)
	{
		ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, ZC_OPEN_GL_COLLOR_BUFFER_SIZE) != 0)
	{
		ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, ZC_OPEN_GL_COLLOR_BUFFER_SIZE) != 0)
	{
		ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
		return false;
	}
	if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, ZC_OPEN_GL_DEPTH_BUFFER_SIZE) != 0)
	{
		ZC_ErrorLogger::Err("SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE) fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
		return false;
	}
	
	// #ifdef ZC_DEBUG
    // 	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG) != 0)
	// 	{
	// 		ZC_ErrorLogger::Err("SDL_GL_SetAttribute() fail: " + std::string(SDL_GetError()), __FILE__, __LINE__);
	// 		return false;
	// 	}
	// #endif

	return true;
}
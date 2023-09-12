#include <ZC/API/PC/SDL/ZC_SDL_Window.h>

#include <ZC/ZC_OpenGL.h>

#include <ZC_EL.h>
#include <sstream>

void APIENTRY glDebugOutput(
	GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

    std::stringstream stream;
    stream << "Debug message (" << id << "): " << message;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             stream << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   stream << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: stream << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     stream << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     stream << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           stream << "Source: Other"; break;
	} stream << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               stream << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: stream << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  stream << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         stream << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         stream << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              stream << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          stream << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           stream << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               stream << "Type: Other"; break;
	} stream << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         stream << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       stream << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          stream << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: stream << "Severity: notification"; break;
	} stream << std::endl;
	stream << std::endl;

    ZC_Err(stream.str());
}

ZC_SDL_Window::ZC_SDL_Window(const char* name, const int& width, const int& height)
{
    if (width <= 0 && height <= 0)
    {
        window = SDL_CreateWindow(name, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        window = SDL_CreateWindowWithPosition(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    glContext = SDL_GL_CreateContext(window);
    ZC_SDL_LoadOpenGL();

	GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
}

ZC_SDL_Window::~ZC_SDL_Window()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
}

bool ZC_SDL_Window::HandleEvents()
{
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return false;
        }
    }

    return true;
}

void ZC_SDL_Window::SwapBuffer()
{
    SDL_GL_SwapWindow(window);  
}
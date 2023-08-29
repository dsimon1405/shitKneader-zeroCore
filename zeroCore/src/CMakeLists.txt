add_library(${PROJECT_NAME} ${ZC_LIB_TYPE}
    SDL/ZC_SDL_Window.cpp
    SDL/ZC_API_SDL.cpp
    ErrorLogger/ZC_ErroLogger.cpp
    ErrorLogger/ZC_EL_Console.cpp
    ErrorLogger/ZC_EL_Initializer.cpp
    SDL/ZC_SDL_OpenGL.cpp
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC ../include
    PUBLIC ${PROJECT_BINARY_DIR}
    )

target_link_libraries(${PROJECT_NAME}
    PUBLIC SDL3::SDL3
	)
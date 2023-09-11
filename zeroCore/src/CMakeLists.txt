add_library(${PROJECT_NAME} ${ZC_LIB_TYPE}
    API/PC/SDL/ZC_SDL_Window.cpp
    API/PC/SDL/ZC_API_SDL.cpp
    ErrorLogger/ZC_ErroLogger.cpp
    ErrorLogger/ZC_EL_Console.cpp
    API/PC/SDL/ZC_SDL_OpenGL.cpp
    ZC_EL.cpp
    API/PC/ZC_PC_main.cpp
    API/ZC_API_Initialize.cpp
    ErrorLogger/ZC_EL_Initialize.cpp
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_BINARY_DIR}/config
    PUBLIC ${PROJECT_SOURCE_DIR}/external/sdl3/include     #   debug
    )

target_link_libraries(${PROJECT_NAME}
    # PUBLIC SDL3::SDL3
    # PUBLIC ${PROJECT_SOURCE_DIR}/external/sdl3Libs/libSDL3.a     #   debug
    PUBLIC ${PROJECT_SOURCE_DIR}/external/sdl3Libs/libSDL3.so     #   debug
	)
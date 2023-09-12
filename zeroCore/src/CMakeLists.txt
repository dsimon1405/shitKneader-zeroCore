add_library(${PROJECT_NAME} ${ZC_LIB_TYPE}
    ZC/API/PC/SDL/ZC_SDL_Window.cpp
    ZC/API/PC/SDL/ZC_API_SDL.cpp
    ZC/ErrorLogger/ZC_ErroLogger.cpp
    ZC/ErrorLogger/ZC_EL_Console.cpp
    ZC/API/PC/SDL/ZC_SDL_OpenGL.cpp
    ZC_EL.cpp
    ZC/API/PC/ZC_PC_main.cpp
    ZC/API/ZC_API_Initialize.cpp
    ZC/ErrorLogger/ZC_EL_Initialize.cpp
    ZC/ZC_Window.cpp
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_BINARY_DIR}/config
    PUBLIC ${PROJECT_SOURCE_DIR}/external/sdl3/include     #   debug
    )

target_link_libraries(${PROJECT_NAME}
    # PUBLIC SDL3::SDL3     #   release
    # PUBLIC ${PROJECT_SOURCE_DIR}/external/sdl3Libs/libSDL3.a     #   debug
    PUBLIC ${PROJECT_SOURCE_DIR}/external/sdl3Libs/libSDL3.so     #   debug
	)
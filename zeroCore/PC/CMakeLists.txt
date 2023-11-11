#========================= src files
#   SDL3
    #   video
if(ZC_SDL_VIDEO)
    #	include
    set(ZC_INCLUDE_DIRS ${ZC_INCLUDE_DIRS}
        PRIVATE ${PROJECT_SOURCE_DIR}/external/sdl3/include)

    #   src
    set(ZC_SRC_FILES ${ZC_SRC_FILES}
        ${PROJECT_SOURCE_DIR}/src/Video/PC/SDL/ZC_SDL_Window.cpp
        ${PROJECT_SOURCE_DIR}/src/Video/OpenGL/PC/SDL/ZC_SDL_LoadOpenGLFunctions.cpp)
endif()

#   audio
if(ZC_AUDIO)
    if(ZC_SDL_AUDIO)
        set(ZC_SRC_FILES ${ZC_SRC_FILES}
            ${PROJECT_SOURCE_DIR}/src/Audio/PC/SDL/ZC_SDL_AudioStream.cpp)
    endif()
endif()

#========================= includeVariable
set(ZC_INCLUDE_DIRS ${ZC_INCLUDE_DIRS} PUBLIC ${PROJECT_SOURCE_DIR}/includeVariable/PC)

#========================= src files
set(ZC_SRC_FILES ${ZC_SRC_FILES}
        ${PROJECT_SOURCE_DIR}/src/Tools/Console/PC/ZC_cout.cpp
        ${PROJECT_SOURCE_DIR}/src/File/Read/PC/ZC_PC_FileReader.cpp
        ${PROJECT_SOURCE_DIR}/src/File/Read/PC/ZC_MakeAbsolutePath.cpp
        ${PROJECT_SOURCE_DIR}/src/main/PC/ZC_PC_main.cpp
        )

#========================= add lib
add_library(${PROJECT_NAME} ${ZC_LIB_TYPE} ${ZC_SRC_FILES})

#========================= include
target_include_directories(${PROJECT_NAME} ${ZC_INCLUDE_DIRS})

#========================= link
target_link_libraries(${PROJECT_NAME} ${ZC_LINK_LIBS})
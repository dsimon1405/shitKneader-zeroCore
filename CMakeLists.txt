cmake_minimum_required(VERSION 3.22)
project(shitKneader)

#========================= options

#   only one could be ON
option(SK_PC "Build executable file for PC" OFF)
option(SK_ANDROID "Build APK file in Android Studio" ON)

option(SK_DEBUG "ON - External libraries will be build shared" ON)

message(STATUS "======================= SHIT KNEADER START =======================")

#========================= options control
if(SK_PC)
    set(SK_ANDROID OFF)
else()
    set(SK_ANDROID ON)
endif()

#========================= compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(SK_PC AND WIN32 AND SK_DEBUG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

#========================= zeroCore
set(ZC_AUDIO ON)

if(SK_DEBUG)
    set(ZC_STATIC OFF)
    set(ZC_DEBUG ON)
else()
    set(ZC_STATIC ON)
    set(ZC_DEBUG OFF)
endif()

set(ZC_SRC_ASSETS_PATH "${PROJECT_SOURCE_DIR}/assets")
set(ZC_COPY_ASSETS_SRC_TO_BUILD ON)

if(SK_PC)
    set(ZC_PC ON)
    set(ZC_ANDROID OFF)
    set(ZC_BUILD_ASSETS_PATH "${PROJECT_BINARY_DIR}")
elseif(SK_ANDROID)
    set(ZC_PC OFF)
    set(ZC_ANDROID ON)
    set(ZC_BUILD_ASSETS_PATH "/home/dmitry/AndroidStudioProjects/SK/app/src/main")
endif()

#========================= external libs
set(SK_LINK_LIBS)

add_subdirectory(zeroCore)
set(SK_LINK_LIBS ${SK_LINK_LIBS} PUBLIC zeroCore)

#========================= SHIT KNEADER =========================

#========================= files
set(SK_SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    )

#========================= add exe/lib
if(SK_PC)
    add_executable(${PROJECT_NAME} ${SK_SRC_FILES})
elseif(SK_ANDROID)
    # set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
    add_library(${PROJECT_NAME} SHARED ${SK_SRC_FILES})
endif()

#========================= link libs
target_link_libraries(${PROJECT_NAME} ${SK_LINK_LIBS})


message(STATUS "====================== SHIT KNEADER CONFIG =======================\n")
message(STATUS "SK_PC: ${SK_PC}")
message(STATUS "SK_ANDROID: ${SK_ANDROID}\n")
message(STATUS "SK_DEBUG: ${SK_DEBUG}\n")
message(STATUS "======================== SHIT KNEADER END ========================")

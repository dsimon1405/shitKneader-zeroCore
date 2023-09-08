cmake_minimum_required(VERSION 3.22)
project(shitKneader)

#========================= options
#   only one could be ON
option(SK_RELEASE "ON - External libraries will be build static" ON)
option(SK_DEBUG "ON - External libraries will be build shared" OFF)

#   only one could be ON
option(SK_PC "Build APK file in Android Studio" OFF)
option(SK_ANDROID "Build APK file in Android Studio" ON)

#========================= options control
if(SK_RELEASE)
    set(SK_DEBUG OFF)
else()
    set(SK_DEBUG ON)
endif()

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
if(SK_RELEASE)
    set(ZC_STATIC ON)
    set(ZC_SHARED OFF)
    set(ZC_EXTERNAL_STATIC ON)
    set(ZC_EXTERNAL_SHARED OFF)
    set(ZC_ERROR_LOGGER_DATABASE OFF)   #   когда подключу сдечать ON
    set(ZC_ERROR_LOGGER_CONSOLE ON)
elseif(SK_DEBUG)
    set(ZC_STATIC OFF)
    set(ZC_SHARED ON)
    set(ZC_EXTERNAL_STATIC OFF)
    set(ZC_EXTERNAL_SHARED ON)
    set(ZC_ERROR_LOGGER_DATABASE OFF)
    set(ZC_ERROR_LOGGER_CONSOLE ON)
endif()

if(SK_PC)
    set(ZC_PC ON)
    set(ZC_ANDROID OFF)
    set(ZC_API_SDL ON)
elseif(SK_ANDROID)
    set(ZC_PC OFF)
    set(ZC_ANDROID ON)
    set(ZC_API_ANDROID ON)
endif()

#========================= zeroCore
add_subdirectory(zeroCore)

#========================= shitKneader
if(SK_PC)
    add_subdirectory(shitKneader/src)
elseif(SK_ANDROID)
    add_subdirectory(shitKneader/Android)
endif()

message(STATUS "======================== shitKneader OPTIONS ========================")
message(STATUS "SK_RELEASE: ${SK_RELEASE}")
message(STATUS "SK_DEBUG: ${SK_DEBUG}\n")
message(STATUS "SK_PC: ${SK_PC}")
message(STATUS "SK_ANDROID: ${SK_ANDROID}\n")

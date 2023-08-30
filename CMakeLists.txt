cmake_minimum_required(VERSION 3.22)
project(shitKneader)

option(SK_RELEASE "Build independent executable, external libraries will be build static" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32 AND NOT SK_RELEASE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()


#               DOWANLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#               UPDATE SUBMODULES AS NEDDED
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
        endif()
    endif()
endif()
#               CHECK ALL THE SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/zeroCore/external/sdl3/CMakeLists.txt")
    message(FATAL_ERROR "The sdl submodule was not downloaded!")
endif()


#   zeroCore
if(SK_RELEASE)
    set(ZC_SHARED OFF)
    set(ZC_ERROR_LOGGER_DATABASE ON)
else()
    set(ZC_EXTERNAL_SHARED ON)
    set(ZC_ERROR_LOGGER_CONSOLE ON)
    set(ZC_ERROR_LOGGER_DATABASE OFF)
endif()
add_subdirectory(zeroCore)

#   shitKneader
add_subdirectory(shitKneader/src)
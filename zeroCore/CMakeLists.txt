cmake_minimum_required(VERSION 3.22)
project(zeroCore)

option(ZC_SHARED "ON - build shared library, OFF - build static" ON)
option(ZC_EXTERNAL_SHARED "ON - build shared external libraries, OFF - build static" OFF)

#	only one error logger type could be ON
option(ZC_ERROR_LOGGER_CONSOLE "ON - print errors to console" ON)
option(ZC_ERROR_LOGGER_DATABASE "ON - log errors to console" OFF)

#	for windows build dll + lib for linking
if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

#	sdl3
if(NOT ZC_EXTERNAL_SHARED)
	set(SDL_SHARED OFF)
	set(SDL_STATIC ON)
endif()
set(SDL_TEST_LIBRARY OFF)
add_subdirectory(external/sdl3)

#	zeroCore
#	errorLogger file - ZC_EL_Initializer.cpp
set(ZC_ERROR_LOGGER_TYPE "")
if(ZC_ERROR_LOGGER_DATABASE)
	set(ZC_ERROR_LOGGER_TYPE "database")
else()
	if(ZC_ERROR_LOGGER_CONSOLE)
		set(ZC_ERROR_LOGGER_TYPE "console")
	else()
		set(ZC_ERROR_LOGGER_TYPE "none")
	endif()
endif()
configure_file(ZC_Config.h.in ZC_Config.h)

#	libType
set(ZC_LIB_TYPE STATIC)
if(ZC_SHARED)
    set(ZC_LIB_TYPE SHARED)
endif()
add_subdirectory(src)

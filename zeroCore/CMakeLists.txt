cmake_minimum_required(VERSION 3.22)
project(zeroCore)

#========================= options
#	only one could be ON
option(ZC_PC "ON - build for PC version" ON)
option(ZC_ANDROID "ON - build for Android version" OFF)

#	only one could be ON
option(ZC_API_SDL "ON - create API with SDL library" ON)
option(ZC_API_ANDROID "ON - create API with Android library" OFF)

#	only one could be ON
option(ZC_SHARED "ON - build shared library" ON)
option(ZC_STATIC "ON - build static library" OFF)

#	only one could be ON
option(ZC_EXTERNAL_SHARED "ON - build shared external libraries" ON)
option(ZC_EXTERNAL_STATIC "ON - build static external libraries" OFF)

#	only one could be ON, both could be OFF
option(ZC_ERROR_LOGGER_CONSOLE "ON - log errors to console" ON)
option(ZC_ERROR_LOGGER_DATABASE "ON - log errors to database" OFF)

#========================= options control
if(ZC_PC)
	#	disable other platforms options
	set(ZC_ANDROID OFF)

	#	disable incompatible API options
	set(ZC_API_ANDROID OFF)

	#	choose API options
	if(ZC_API_SDL)
		#	пока других нет для отключения на ПК, elseif() если появятся
	else()
		#	if not ON options, choose first one
		set(ZC_API_SDL ON)
	endif()
elseif(ZC_ANDROID)
	#	disable other platforms options
	set(ZC_PC OFF)

	#	disable incompatible API options
	set(ZC_API_SDL OFF)

	#	choose API options
	if(ZC_API_ANDROID)
		#	пока других нет для отключения на Андроид, elseif() если появятся
	else()
		#	if not ON options, choose first one
		set(ZC_API_ANDROID ON)
	endif()
else()
	#	if not ON options, make ON PC and repeat all for PC
	set(ZC_PC ON)

	#	disable incompatible API options
	set(ZC_API_ANDROID OFF)

	#	choose API options
	if(ZC_API_SDL)
		#	пока других нет для отключения на ПК, elseif() если появятся
	else()
		#	if not ON options, choose first one
		set(ZC_API_SDL ON)
	endif()
endif()

if(ZC_SHARED)
	set(ZC_STATIC OFF)
elseif(ZC_STATIC)
	set(ZC_SHARED OFF)
else()
	set(ZC_STATIC ON)
endif()

if(ZC_EXTERNAL_SHARED)
	set(ZC_EXTERNAL_STATIC OFF)
elseif(ZC_EXTERNAL_STATIC)
	set(ZC_EXTERNAL_SHARED OFF)
else()
	set(ZC_EXTERNAL_STATIC ON)
endif()

if(ZC_ERROR_LOGGER_CONSOLE)
	set(ZC_ERROR_LOGGER_DATABASE OFF)
elseif(ZC_ERROR_LOGGER_DATABASE)
	set(ZC_ERROR_LOGGER_CONSOLE OFF)
endif()

#	for windows build dll + lib for linking
if(ZC_PC AND WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

#========================= submodules
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
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/sdl3/CMakeLists.txt")
    message(FATAL_ERROR "The sdl submodule was not downloaded!")
endif()

#========================= external libs
#	sdl3
if(ZC_API_SDL)
	if(ZC_EXTERNAL_STATIC)
		set(SDL_STATIC ON)
		set(SDL_SHARED OFF)
	elseif(ZC_EXTERNAL_SHARED)
		set(SDL_STATIC OFF)
		set(SDL_SHARED ON)
	endif()

	set(SDL_TEST_LIBRARY OFF)
	add_subdirectory(external/sdl3)
endif()


#========================= zeroCore

#========================= config file
add_subdirectory(${PROJECT_SOURCE_DIR}/config)

#========================= lib type
set(ZC_LIB_TYPE STATIC)
if(ZC_SHARED)
    set(ZC_LIB_TYPE SHARED)
elseif(ZC_STATIC)
	set(ZC_LIB_TYPE STATIC)
endif()

#========================= platform type
if(ZC_ANDROID)
	add_subdirectory(Android)
else()
	add_subdirectory(src)
endif()

message(STATUS "======================== zeroCore OPTIONS ========================")
message(STATUS "ZC_PC: ${ZC_PC}")
message(STATUS "ZC_ANDROID: ${ZC_ANDROID}\n")
message(STATUS "ZC_API_SDL: ${ZC_API_SDL}")
message(STATUS "ZC_API_ANDROID: ${ZC_API_ANDROID}\n")
message(STATUS "ZC_SHARED: ${ZC_SHARED}")
message(STATUS "ZC_STATIC: ${ZC_STATIC}\n")
message(STATUS "ZC_EXTERNAL_SHARED: ${ZC_EXTERNAL_SHARED}")
message(STATUS "ZC_EXTERNAL_STATIC: ${ZC_EXTERNAL_STATIC}\n")
message(STATUS "ZC_ERROR_LOGGER_CONSOLE: ${ZC_ERROR_LOGGER_CONSOLE}")
message(STATUS "ZC_ERROR_LOGGER_DATABASE: ${ZC_ERROR_LOGGER_DATABASE}\n")
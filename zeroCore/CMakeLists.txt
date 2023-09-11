cmake_minimum_required(VERSION 3.22)
project(zeroCore)

message(STATUS "======================== ZeroCore ========================")
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
if(ZC_API_SDL)
	set(GIT_SUBMODULES ON)
else()
	set(GIT_SUBMODULES OFF)
endif()

if(GIT_SUBMODULES)
	find_package(Git QUIET)
	if(GIT_FOUND)
		#	git init
		if(NOT EXISTS "${PROJECT_SOURCE_DIR}/.git")
			message(STATUS "Init Git for submodules download")
			execute_process(COMMAND ${GIT_EXECUTABLE} init
		                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		                    RESULT_VARIABLE GIT_INIT_RESULT)
		    if(NOT GIT_INIT_RESULT EQUAL "0")
				message(FATAL_ERROR "git init => failed with: ${GIT_SUBMOD_RESULT}")
		    endif()
		endif()


		#	git submodule add
		set(SUBMODULES_UPDATE OFF)

		if(ZC_API_SDL)
			#	check adding to git submodules
			if(NOT EXISTS "${PROJECT_SOURCE_DIR}/.git/modules/external/sdl3")
				message(STATUS "Add submodule SDL3")
				execute_process(COMMAND ${GIT_EXECUTABLE} submodule add https://github.com/libsdl-org/SDL.git external/sdl3
			                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			                    RESULT_VARIABLE GIT_SUBMODULE_ADD_SDL3_RESULT)
			    if(NOT GIT_SUBMODULE_ADD_SDL3_RESULT EQUAL "0")
					message(FATAL_ERROR "git submodule add https://github.com/libsdl-org/SDL.git external/sdl3 => failed with: ${GIT_SUBMODULE_ADD_SDL3_RESULT}")
			    endif()
			endif()
			#	existing check
			if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/sdl3/CMakeLists.txt")
				set(SUBMODULES_UPDATE ON)
				message(STATUS "Submodule SDL3 needs update")
			endif()
		endif()


		#	git submodule update --init
		if(SUBMODULES_UPDATE)
		#	submodele supdate
		    message(STATUS "Submodules update")
		    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
		                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
		    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
		        message(FATAL_ERROR "git submodule update --init => failed with: ${GIT_SUBMOD_RESULT}")
		    endif()
		endif()
	else()
		message(FATAL_ERROR "Could not find_package(Git QUiET)!")
	endif()

	#	total submodules check
	if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/sdl3/CMakeLists.txt")
	    message(FATAL_ERROR "The sdl submodule was not downloaded!")
	endif()
endif()

#========================= external libs
#	sdl3
# if(ZC_API_SDL)
# 	if(ZC_EXTERNAL_STATIC)
# 		set(SDL_STATIC ON)
# 		set(SDL_SHARED OFF)
# 	elseif(ZC_EXTERNAL_SHARED)
# 		set(SDL_STATIC OFF)
# 		set(SDL_SHARED ON)
# 	endif()
# 
# 	set(SDL_TEST_LIBRARY OFF)
# 	add_subdirectory(external/sdl3)
# endif()


#========================= zeroCore

#========================= config file
add_subdirectory(${PROJECT_SOURCE_DIR}/config)

#========================= lib type
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

message(STATUS "======================== ZeroCore OPTIONS ========================")
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
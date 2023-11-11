cmake_minimum_required(VERSION 3.22)
project(zeroCore)

#========================= options
#	only one could be ON
option(ZC_PC "ON - build for PC version" ON)
option(ZC_ANDROID "ON - build for Android version" OFF)

option(ZC_AUDIO "ON - audio support" ON)

option(ZC_STATIC "ON - build static library, else build shared" ON)

option(ZC_DEBUG "ON - error will throw exception, else will logg error message" OFF)

#	ZC_SRC_ASSETS_PATH - set path to source assets directory in your CMakeLists.txt (exemple: set(ZC_SRC_ASSETS_PATH ".../assets"))
set(ZC_SRC_ASSETS_PATH ${ZC_SRC_ASSETS_PATH})
#	set ZC_BUILD_ASSETS_PATH - path to build assets directory (For PC development, this path will be considered absolute to assets)
set(ZC_BUILD_ASSETS_PATH ${ZC_BUILD_ASSETS_PATH})
option(ZC_COPY_ASSETS_SRC_TO_BUILD "ON - copy assets from ZC_SRC_ASSETS_PATH to ZC_BUILD_ASSETS_PATH" OFF)

message(STATUS "========================= ZERO CORE START ========================")

set(ZC_MY_DEBUG ON)

#========================= c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#	for windows build dll + lib for linking
if(ZC_PC AND WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

#========================= set configuration
if(ZC_ANDROID)
	#	disable other platforms options
	set(ZC_PC OFF)
	
	#	set video/audio API
	set(ZC_ANDROID_NATIVE_APP_GLUE ON)
	if(ZC_AUDIO)
		set(ZC_OBOE ON)
	else()
		set(ZC_OBOE OFF)
	endif()
else()
	#	if no ON options, make ON PC configuration
	set(ZC_PC ON)

	#	set video/audio API
	set(ZC_SDL_VIDEO ON)
	if(ZC_AUDIO)
		set(ZC_SDL_AUDIO ON)
	else()
		set(ZC_SDL_AUDIO OFF)
	endif()
endif()

#========================= git submodules
if(ZC_SDL_VIDEO OR ZC_OBOE)
	set(ZC_GIT_SUBMODULES ON)
else()
	set(ZC_GIT_SUBMODULES OFF)
endif()

if(ZC_GIT_SUBMODULES)
	find_package(Git QUIET)
	if(GIT_FOUND)
		#	git init
		if(NOT EXISTS "${PROJECT_SOURCE_DIR}/.git")
			message(STATUS "Init Git for submodules download")
			execute_process(COMMAND ${GIT_EXECUTABLE} init
		                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		                    RESULT_VARIABLE ZC_GIT_INIT_RESULT)
		    if(NOT ZC_GIT_INIT_RESULT EQUAL "0")
				message(FATAL_ERROR "git init => failed with: ${GIT_SUBMOD_RESULT}")
		    endif()
		endif()

		#	git submodule add
		function(ZC_F_GIT_SUBMODULE_CHECK name link needUpdate)
			#	check add to git submodules
			if(NOT EXISTS "${PROJECT_SOURCE_DIR}/.git/modules/external/${name}")
				message(STATUS "Add submodule ${name}")
				execute_process(COMMAND ${GIT_EXECUTABLE} submodule add ${link} external/${name}
			                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			                    RESULT_VARIABLE ZC_GIT_SUBMODULE_ADD_RESULT)
			    if(NOT ZC_GIT_SUBMODULE_ADD_RESULT EQUAL "0")
					message(FATAL_ERROR "git submodule add ${link} external/${name} => failed with: ${ZC_GIT_SUBMODULE_ADD_RESULT}")
			    endif()
			endif()
			#	existing check
			if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/${name}/.git")
				set(${needUpdate} ON PARENT_SCOPE)
				message(STATUS "Submodule ${name} need update")
			endif()
		endfunction()

		set(ZC_GIT_SUBMODULES_UPDATE OFF)

		if(ZC_SDL_VIDEO)
			ZC_F_GIT_SUBMODULE_CHECK("sdl3" "https://github.com/libsdl-org/SDL.git" ZC_GIT_SUBMODULES_UPDATE)
		elseif(ZC_OBOE)
			ZC_F_GIT_SUBMODULE_CHECK("oboe" "https://github.com/google/oboe.git" ZC_GIT_SUBMODULES_UPDATE)
		endif()

		#	git submodule update --init
		if(ZC_GIT_SUBMODULES_UPDATE)
			#	submodule update
		    message(STATUS "Submodules update")
		    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
		                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		                    RESULT_VARIABLE ZC_GIT_SUBMOD_RESULT)
		    if(NOT ZC_GIT_SUBMOD_RESULT EQUAL "0")
		        message(FATAL_ERROR "git submodule update --init --recursive => failed with: ${GIT_SUBMOD_RESULT}")
		    endif()
		endif()
	else()
		message(FATAL_ERROR "Could not find_package(Git QUIET)!")
	endif()

	#	total submodules check
	function(ZC_F_GIT_SUBMODULE_EXISTS name)
		if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/${name}/CMakeLists.txt")
	    	message(FATAL_ERROR "Doesn't exists: ${PROJECT_SOURCE_DIR}/external/${name}/CMakeLists.txt")
		endif()
	endfunction()

	if(ZC_SDL_VIDEO)
		ZC_F_GIT_SUBMODULE_EXISTS("sdl3")
	elseif(ZC_OBOE)
		ZC_F_GIT_SUBMODULE_EXISTS("oboe")
	endif()
endif()

#========================= include dirs
set(ZC_INCLUDE_DIRS
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PUBLIC ${PROJECT_BINARY_DIR}/config
	)

#========================= external libs
set(ZC_LINK_LIBS)

#	sdl3
if(ZC_SDL_VIDEO)
	#	add lib
	if(ZC_MY_DEBUG)
		set(ZC_LINK_LIBS ${ZC_LINK_LIBS} PRIVATE ${PROJECT_SOURCE_DIR}/external/sdl3Libs/libSDL3.so)
	else()
		set(SDL_STATIC ON)
		set(SDL_SHARED OFF)
		set(SDL_TEST_LIBRARY OFF)
		add_subdirectory(${PROJECT_SOURCE_DIR}/external/sdl3)

		set(ZC_LINK_LIBS ${ZC_LINK_LIBS} PRIVATE SDL3::SDL3)
	endif()
endif()

#	android_native_app_glue
if(ZC_ANDROID_NATIVE_APP_GLUE)
	#   set link flag for calling CMakeLists.txt
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate" PARENT_SCOPE)
endif()

#	oboe
if(ZC_OBOE)
	add_subdirectory(${PROJECT_SOURCE_DIR}/external/oboe)
endif()

#========================= ZERO CORE =========================

#========================= copy assets
if(ZC_COPY_ASSETS_SRC_TO_BUILD)
	message(STATUS "Copy: ${ZC_SRC_ASSETS_PATH} => ${ZC_BUILD_ASSETS_PATH}")
	execute_process(COMMAND cp -R ${ZC_SRC_ASSETS_PATH} ${ZC_BUILD_ASSETS_PATH}
				RESULT_VARIABLE ZC_COPY_ASSETS_RESULT)
	if(NOT ZC_COPY_ASSETS_RESULT EQUAL "0")
		message(FATAL_ERROR "cp -R ${ZC_SRC_ASSETS_PATH} ${ZC_BUILD_ASSETS_PATH} => failed with: ${GIT_SUBMOD_RESULT}")
	endif()
endif()

#========================= make config file
add_subdirectory(config)

#========================= lib type
if(ZC_STATIC)
	set(ZC_LIB_TYPE STATIC)
else()
	set(ZC_LIB_TYPE SHARED)
endif()

#========================= src files
set(ZC_SRC_FILES)

#	ErrorLogger
if(ZC_DEBUG)
	set(ZC_SRC_FILES ${ZC_SRC_FILES}
		${PROJECT_SOURCE_DIR}/src/ErrorLogger/Exception/ZC_ErrorLogger.cpp)
else()
	set(ZC_SRC_FILES ${ZC_SRC_FILES}
		${PROJECT_SOURCE_DIR}/src/ErrorLogger/Message/ZC_ErrorLogger.cpp)
endif()

#	audio
if(ZC_AUDIO)
	set(ZC_INCLUDE_DIRS ${ZC_INCLUDE_DIRS}
		PUBLIC ${PROJECT_SOURCE_DIR}/includeVariable/Audio)
    set(ZC_SRC_FILES ${ZC_SRC_FILES}
        ${PROJECT_SOURCE_DIR}/src/Audio/ZC_Audio.cpp
        ${PROJECT_SOURCE_DIR}/src/Audio/ZC_AudioSet.cpp
        ${PROJECT_SOURCE_DIR}/src/Audio/ZC_AudioStream.cpp
        ${PROJECT_SOURCE_DIR}/src/Audio/ZC_Sound.cpp
        ${PROJECT_SOURCE_DIR}/src/Audio/ZC_SoundData.cpp
        ${PROJECT_SOURCE_DIR}/src/Audio/ZC_Sounds.cpp
        ${PROJECT_SOURCE_DIR}/src/Audio/ZC_StreamSound.cpp
    )
endif()

# #	sqlite
# #set(ZC_SRC_FILES ${ZC_SRC_FILES} ${PROJECT_SOURCE_DIR}/external/sqlite/src/sqlite3.c)
# add_library(sqlite SHARED ${PROJECT_SOURCE_DIR}/external/sqlite/src/sqlite3.c)
# set(ZC_INCLUDE_DIRS ${ZC_INCLUDE_DIRS} PUBLIC ${PROJECT_SOURCE_DIR}/external/sqlite/include)
# set(ZC_LINK_LIBS ${ZC_LINK_LIBS} PUBLIC sqlite)

#	total
set(ZC_SRC_FILES ${ZC_SRC_FILES}
    ${PROJECT_SOURCE_DIR}/src/Video/ZC_Video.cpp
    ${PROJECT_SOURCE_DIR}/src/Video/ZC_Window.cpp
    ${PROJECT_SOURCE_DIR}/src/Video/OpenGL/ZC_OpenGLConfig.cpp
    ${PROJECT_SOURCE_DIR}/src/Video/OpenGL/Shader/ZC_Shader.cpp
	${PROJECT_SOURCE_DIR}/src/Video/OpenGL/Shader/ZC_ShaderCode.cpp
    ${PROJECT_SOURCE_DIR}/src/Video/OpenGL/Shader/ZC_ShaderLoader.cpp
    ${PROJECT_SOURCE_DIR}/src/Video/OpenGL/ZC_VBO.cpp
    ${PROJECT_SOURCE_DIR}/src/Video/OpenGL/VAO/ZC_VAO.cpp
    ${PROJECT_SOURCE_DIR}/src/Video/OpenGL/VAO/ZC_VAOConfig.cpp
    ${PROJECT_SOURCE_DIR}/src/Tools/Signal/ZC_SignalConnection.cpp
	${PROJECT_SOURCE_DIR}/src/Tools/Exception/ZC_Exception.cpp
	${PROJECT_SOURCE_DIR}/src/ErrorLogger/ZC_MakeErrorString.cpp
	${PROJECT_SOURCE_DIR}/src/File/Read/ZC_FileReader.cpp
	${PROJECT_SOURCE_DIR}/src/ErrorLogger/ZC_ErrorLogger.cpp
    )

#========================= add lib
if(ZC_PC)
	add_subdirectory(PC)
else(ZC_ANDROID)
	add_subdirectory(Android)
endif()


message(STATUS "======================== ZERO CORE CONFIG ========================\n")
message(STATUS "ZC_PC: ${ZC_PC}")
message(STATUS "ZC_ANDROID: ${ZC_ANDROID}\n")
message(STATUS "ZC_STATIC: ${ZC_STATIC}\n")
message(STATUS "ZC_AUDIO: ${ZC_AUDIO}\n")
message(STATUS "ZC_DEBUG: ${ZC_DEBUG}\n")
message(STATUS "ZC_SRC_ASSETS_PATH: ${ZC_SRC_ASSETS_PATH}")
message(STATUS "ZC_BUILD_ASSETS_PATH: ${ZC_BUILD_ASSETS_PATH}")
message(STATUS "ZC_COPY_ASSETS_SRC_TO_BUILD: ${ZC_COPY_ASSETS_SRC_TO_BUILD}\n")
message(STATUS "========================= ZERO CORE END ==========================")
cmake_minimum_required(VERSION 3.22)
project(zeroCore)

#========================= options
#	only one could be ON
option(ZC_PC "ON - build for PC version" ON)
option(ZC_ANDROID "ON - build for Android version" OFF)

#	set the relative path from the launch file to your resources (this is necessary for the same behavior of PC/Android file systems)
#	exapmle: your resources directory in build folder (.../build/allResurcesDirName) make next => set(ZC_ASSETS_PATH allResurcesDirName)
set(ZC_ASSETS_PATH ${ZC_ASSETS_PATH})

option(ZC_AUDIO "ON - audio support" ON)

option(ZC_STATIC "ON - build static library, else build shared" ON)

message(STATUS "========================= ZERO CORE START ========================")

set(ZC_MY_DEBUG 1)

#========================= c++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#	for windows build dll + lib for linking
if(ZC_PC AND WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

#========================= set configuration
if((ZC_PC AND ZC_ANDROID) OR (NOT ZC_PC AND NOT ZC_ANDROID))
	message(FATAL_ERROR "Options ZC_PC and ZC_ANDROID can't have the same values.")
endif()

#	all bool used values set off
	#	video
set(ZC_SDL_VIDEO OFF)
set(ZC_ANDROID_NATIVE_APP_GLUE ON)
	#	audio
set(ZC_OBOE OFF)
set(ZC_SDL_AUDIO OFF)

if(ZC_PC)
	#	video
	set(ZC_SDL_VIDEO ON)
	#	audio
	if(ZC_AUDIO)
		set(ZC_SDL_AUDIO ON)
	endif()
elseif(ZC_ANDROID)
	#	video
	set(ZC_ANDROID_NATIVE_APP_GLUE ON)
	#	audio
	if(ZC_AUDIO)
		set(ZC_OBOE ON)
	endif()
endif()

#========================= lib type
if(ZC_STATIC)
	set(ZC_LIB_TYPE STATIC)
else()
	set(ZC_LIB_TYPE SHARED)
endif()

#	fatatl error equal function
function(ZC_F_FATAL_EQUAL data1 data2 errorMessage)
	if(NOT ${data1} EQUAL ${data2})
		message(FATAL_ERROR ${errorMessage})
	endif()
endfunction()

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
			ZC_F_FATAL_EQUAL(${ZC_GIT_INIT_RESULT} 0 "git init => failed with: ${ZC_GIT_INIT_RESULT}")
		endif()

		#	git submodule add
		function(ZC_F_GIT_SUBMODULE_CHECK name link needUpdate)
			#	check add to git submodules
			if(NOT EXISTS "${PROJECT_SOURCE_DIR}/.git/modules/external/${name}")
				message(STATUS "Add submodule ${name}")
				execute_process(COMMAND ${GIT_EXECUTABLE} submodule add ${link} external/${name}
			                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			                    RESULT_VARIABLE ZC_GIT_SUBMODULE_ADD_RESULT)
				ZC_F_FATAL_EQUAL(${ZC_GIT_SUBMODULE_ADD_RESULT} 0 "git submodule add ${link} external/${name} => failed with: ${ZC_GIT_SUBMODULE_ADD_RESULT}")
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
			ZC_F_FATAL_EQUAL(${ZC_GIT_SUBMOD_RESULT} 0 "git submodule update --init --recursive => failed with: ${ZC_GIT_SUBMOD_RESULT}")
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

#========================= external libs
if(ZC_PC)
	#	sdl3
	if(ZC_SDL_VIDEO AND NOT ZC_MY_DEBUG)
		set(SDL_TEST_LIBRARY OFF)
		set(SDL_STATIC ON)
		set(SDL_SHARED OFF)
		add_subdirectory(${PROJECT_SOURCE_DIR}/external/sdl3)
	endif()
endif()

if(ZC_ANDROID)
	#	android_native_app_glue
	if(ZC_ANDROID_NATIVE_APP_GLUE)
		#   set link flag for calling CMakeLists.txt
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate" PARENT_SCOPE)
	endif()

	#	oboe
	if(ZC_OBOE)
		add_subdirectory(${PROJECT_SOURCE_DIR}/external/oboe)
	endif()
endif()

#========================= ZERO CORE =========================

#========================= make config file
add_subdirectory(config)

# #	sqlite
# #set(ZC_SRC_FILES ${ZC_SRC_FILES} ${PROJECT_SOURCE_DIR}/external/sqlite/src/sqlite3.c)
# add_library(sqlite SHARED ${PROJECT_SOURCE_DIR}/external/sqlite/src/sqlite3.c)
# set(ZC_INCLUDE_DIRS ${ZC_INCLUDE_DIRS} PUBLIC ${PROJECT_SOURCE_DIR}/external/sqlite/include)
# set(ZC_LINK_LIBS ${ZC_LINK_LIBS} PUBLIC sqlite)

#========================= sources
set(ZC_SRC_FILES)
set(ZC_INCLUDE_DIRS)
set(ZC_LINK_LIBS)

if(ZC_PC)
	add_subdirectory(PC)
elseif(ZC_ANDROID)
	add_subdirectory(Android)
endif()

set(ZC_SRC_FILES ${ZC_SRC_FILES}
	$<IF:$<CONFIG:Debug>,
		${PROJECT_SOURCE_DIR}/src/ErrorLogger/Exception/ZC_ErrorLogger.cpp,
		${PROJECT_SOURCE_DIR}/src/ErrorLogger/Message/ZC_ErrorLogger.cpp>
	$<$<BOOL:${ZC_AUDIO}>:
		${PROJECT_SOURCE_DIR}/src/Audio/ZC_Audio.cpp
		${PROJECT_SOURCE_DIR}/src/Audio/ZC_AudioSet.cpp
		${PROJECT_SOURCE_DIR}/src/Audio/ZC_AudioStream.cpp
		${PROJECT_SOURCE_DIR}/src/Audio/ZC_Sound.cpp
		${PROJECT_SOURCE_DIR}/src/Audio/ZC_SoundData.cpp
		${PROJECT_SOURCE_DIR}/src/Audio/ZC_Sounds.cpp
		${PROJECT_SOURCE_DIR}/src/Audio/ZC_StreamSound.cpp>
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
    ${PROJECT_SOURCE_DIR}/src/Tools/Time/ZC_Clock.cpp
	${PROJECT_SOURCE_DIR}/src/ErrorLogger/ZC_MakeErrorString.cpp
	${PROJECT_SOURCE_DIR}/src/File/Read/ZC_FileReader.cpp
	${PROJECT_SOURCE_DIR}/src/ErrorLogger/ZC_ErrorLogger.cpp
    )

add_library(${PROJECT_NAME} ${ZC_LIB_TYPE} ${ZC_SRC_FILES})

#========================= include dirs
set(ZC_INCLUDE_DIRS ${ZC_INCLUDE_DIRS}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PRIVATE ${PROJECT_SOURCE_DIR}/src
	PUBLIC ${PROJECT_BINARY_DIR}/config
	PUBLIC $<$<BOOL:${ZC_AUDIO}>:${PROJECT_SOURCE_DIR}/includeVariable/Audio>
	PUBLIC ${PROJECT_SOURCE_DIR}/external/glm/glm	#	delete me
	)

target_include_directories(${PROJECT_NAME} ${ZC_INCLUDE_DIRS})

#========================= link libs
set(ZC_LINK_LIBS ${ZC_LINK_LIBS})

target_link_libraries(${PROJECT_NAME} ${ZC_LINK_LIBS})

#========================= compiler params
target_compile_options(${PROJECT_NAME}
	PRIVATE	$<IF:$<BOOL:${WIN32}>,-W3,-Wall>
			$<$<CONFIG:Release>:-O3>
	)

message(STATUS "======================== ZERO CORE CONFIG ========================\n")
message(STATUS "ZC_PC: ${ZC_PC}")
message(STATUS "ZC_ANDROID: ${ZC_ANDROID}\n")
message(STATUS "ZC_STATIC: ${ZC_STATIC}\n")
message(STATUS "ZC_AUDIO: ${ZC_AUDIO}\n")
message(STATUS "========================= ZERO CORE END ==========================")
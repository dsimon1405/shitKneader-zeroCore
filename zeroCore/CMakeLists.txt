cmake_minimum_required(VERSION 3.22)
project(zeroCore)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
endif()

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC include)

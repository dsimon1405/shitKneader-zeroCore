cmake_minimum_required(VERSION 3.22)
project(zeroCore)

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC include)

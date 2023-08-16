cmake_minimum_required(VERSION 3.22)
project(shitKneader)

add_executable(${PROJECT_NAME}
    code/main.cpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC ../zeroCore/include)

# target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

target_link_libraries(${PROJECT_NAME} PRIVATE zeroCore)

message("e - ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
cmake_minimum_required(VERSION 3.22)
project(shitKneader)

#========================= options

#   only one could be ON
option(SK_PC "Build executable file for PC" ON)
option(SK_ANDROID "Build APK file in Android Studio" OFF)

message(STATUS "======================= SHIT KNEADER START =======================")

#========================= options control
if(SK_PC)
    set(SK_ANDROID OFF)
else()
    set(SK_ANDROID ON)
endif()

#========================= compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#========================= external libs
set(SK_LINK_LIBS)

set(SK_ASSETS_DIRECTORY_NAME assets)
#========================= zeroCore
if(SK_ANDROID)
    set(ZC_PC OFF)
    set(ZC_ANDROID ON)
endif()

set(ZC_ASSETS_PATH ${SK_ASSETS_DIRECTORY_NAME})

set(ZC_AUDIO ON)

# set(ZC_STATIC ON)
set(ZC_STATIC OFF)

add_subdirectory(zeroCore)
set(SK_LINK_LIBS ${SK_LINK_LIBS} PUBLIC zeroCore)

#========================= SHIT KNEADER =========================

#   dll 
if(SK_PC AND WIN32 AND NOT ZC_STATIC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

#========================= files
set(SK_SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    )

#========================= add exe/lib
if(SK_PC)
    add_executable(${PROJECT_NAME} ${SK_SRC_FILES})
elseif(SK_ANDROID)
    add_library(${PROJECT_NAME} SHARED ${SK_SRC_FILES})
endif()

#========================= link libs
target_link_libraries(${PROJECT_NAME} ${SK_LINK_LIBS})

#========================= compiler params
target_compile_options(${PROJECT_NAME}
    PRIVATE	-Wall
            $<$<CONFIG:Release>:-O3>)

#========================= copy assets
set(SK_ASSETS_DESTINATION_PATH 
    $<$<BOOL:${SK_PC}>:${PROJECT_BINARY_DIR}/${SK_ASSETS_DIRECTORY_NAME}>
    $<$<BOOL:${SK_ANDROID}>:/home/dmitry/AndroidStudioProjects/SK/app/src/main/${SK_ASSETS_DIRECTORY_NAME}>)

add_custom_target(SK_COPY_ASSETS ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/${SK_ASSETS_DIRECTORY_NAME} ${SK_ASSETS_DESTINATION_PATH}
    COMMENT "Copy assets: ${PROJECT_SOURCE_DIR}/${SK_ASSETS_DIRECTORY_NAME} => ${SK_ASSETS_DESTINATION_PATH}")
add_dependencies(${PROJECT_NAME} SK_COPY_ASSETS)


message(STATUS "====================== SHIT KNEADER CONFIG =======================\n")
message(STATUS "SK_PC: ${SK_PC}")
message(STATUS "SK_ANDROID: ${SK_ANDROID}\n")
message(STATUS "======================== SHIT KNEADER END ========================")

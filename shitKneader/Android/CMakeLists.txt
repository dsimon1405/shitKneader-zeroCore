

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
add_library(${PROJECT_NAME} SHARED
    ../src/main.cpp
    )

target_link_libraries(${PROJECT_NAME}
    PUBLIC zeroCore
	)
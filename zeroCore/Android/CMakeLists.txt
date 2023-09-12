#   glue
add_library(native_app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC
        ${ANDROID_NDK}/sources/android/native_app_glue)

add_library(${PROJECT_NAME} ${ZC_LIB_TYPE}
        ${PROJECT_SOURCE_DIR}/src/ZC/API/Android/ZC_A_Window.cpp
		${PROJECT_SOURCE_DIR}/src/ZC/API/Android/ZC_API_Android.cpp
        ${PROJECT_SOURCE_DIR}/src/ZC/ErrorLogger/ZC_EL_AndroidConsole.cpp
        ${PROJECT_SOURCE_DIR}/src/ZC/ErrorLogger/ZC_EL_Initialize.cpp
		${PROJECT_SOURCE_DIR}/src/ZC/ErrorLogger/ZC_ErroLogger.cpp
		${PROJECT_SOURCE_DIR}/src/ZC_EL.cpp
        ${PROJECT_SOURCE_DIR}/src/ZC/ZC_Window.cpp
    	)
        
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_BINARY_DIR}/config
    )

target_link_libraries(${PROJECT_NAME}
    android
    log
    native_app_glue
    EGL
    GLESv3
	)
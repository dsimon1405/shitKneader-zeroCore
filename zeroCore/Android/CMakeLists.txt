#   glue
add_library(native_app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC
        ${ANDROID_NDK}/sources/android/native_app_glue)

add_library(${PROJECT_NAME} STATIC
    	../src/API/Android/ZC_A_Window.cpp
		../src/API/Android/ZC_API_Android.cpp
        ../src/ErrorLogger/ZC_EL_AndroidConsole.cpp
        ../src/ErrorLogger/ZC_EL_AndroidInitialize.cpp
		../src/ErrorLogger/ZC_ErroLogger.cpp
		../src/ZC_EL.cpp
    	)
#${ZC_LIB_TYPE}
target_include_directories(${PROJECT_NAME}
    PUBLIC ../include
    PUBLIC ${PROJECT_BINARY_DIR}/config
    )

target_link_libraries(${PROJECT_NAME}
    android
    log
    native_app_glue
    EGL
    GLESv2
	)
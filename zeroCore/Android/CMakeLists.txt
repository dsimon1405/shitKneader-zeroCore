#========================= external libs
if(ZC_ANDROID_NATIVE_APP_GLUE)
    #   glue lib
    add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
    target_include_directories(native_app_glue PUBLIC ${ANDROID_NDK}/sources/android/native_app_glue)

    #   link libs
    set(ZC_LINK_LIBS ${ZC_LINK_LIBS} PUBLIC native_app_glue)

    #   includeVariable
    set(ZC_INCLUDE_DIRS ${ZC_INCLUDE_DIRS} PUBLIC ${PROJECT_SOURCE_DIR}/includeVariable/AndroidNativeAppGlue)

    #   src files
    set(ZC_SRC_FILES ${ZC_SRC_FILES}
        ${PROJECT_SOURCE_DIR}/src/Video/Android/AndroidNativeAppGlue/ZC_android_app.cpp
        ${PROJECT_SOURCE_DIR}/src/Video/Android/AndroidNativeAppGlue/ZC_AndroidNativeAppGlue_Window.cpp
        ${PROJECT_SOURCE_DIR}/src/File/Read/Android/AndroidNativeAppGlue/ZC_AndroidNativeAppGlue_FileReader.cpp
        )
endif()

#   audio
if(ZC_AUDIO)
    if(ZC_OBOE)
        #   src files
        set(ZC_SRC_FILES ${ZC_SRC_FILES} ${PROJECT_SOURCE_DIR}/src/Audio/Android/oboe/ZC_oboe_AudioStream.cpp)
        #   link libs
        set(ZC_LINK_LIBS ${ZC_LINK_LIBS} PRIVATE oboe)
    endif()
endif()

#   log
set(ZC_LINK_LIBS ${ZC_LINK_LIBS} PUBLIC log)

#========================= src files
set(ZC_SRC_FILES ${ZC_SRC_FILES}
        ${PROJECT_SOURCE_DIR}/src/Tools/Console/Android/AndroidNativeAppGlue/ZC_cout.cpp
        )

#========================= add lib
add_library(${PROJECT_NAME} ${ZC_LIB_TYPE} ${ZC_SRC_FILES})

#========================= include
target_include_directories(${PROJECT_NAME} ${ZC_INCLUDE_DIRS})

#========================= link
target_link_libraries(${PROJECT_NAME}
    ${ZC_LINK_LIBS}
    PUBLIC android
    PUBLIC EGL
    PUBLIC GLESv3
	)
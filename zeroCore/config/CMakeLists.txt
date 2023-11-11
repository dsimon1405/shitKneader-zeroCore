#  Config/ZC_Config.h.in

#========================= platform
if(ZC_PC)
	set(ZC_PLATFORM_TYPE ZC_PC)
elseif(ZC_ANDROID)
	set(ZC_PLATFORM_TYPE ZC_ANDROID)
endif()

#========================= video
if(ZC_SDL_VIDEO)
	set(ZC_VIDEO_TYPE ZC_SDL_VIDEO)
elseif(ZC_ANDROID_NATIVE_APP_GLUE)
	set(ZC_VIDEO_TYPE ZC_ANDROID_NATIVE_APP_GLUE)
endif()

#========================= audio
if(ZC_SDL_AUDIO)
    set(ZC_AUDIO_TYPE ZC_SDL_AUDIO)
elseif(ZC_OBOE)
    set(ZC_AUDIO_TYPE ZC_OBOE)
else()
    set(ZC_AUDIO_TYPE ZC_AUDIO_NONE)
endif()

if(ZC_PC)
    set(ZC_SRC_ASSETS_PATH ${ZC_SRC_ASSETS_PATH})
    set(ZC_BUILD_ASSETS_PATH ${ZC_BUILD_ASSETS_PATH})
elseif(ZC_ANDROID)
    set(ZC_SRC_ASSETS_PATH)
    set(ZC_BUILD_ASSETS_PATH)
endif()

#========================= debug
if(ZC_DEBUG)
    set(ZC_DEBUG_TYPE ZC_DEBUG)
else()
    set(ZC_DEBUG_TYPE ZC_RELEASE)
endif()


# #========================= make config file
configure_file(ZC_Config.h.in ${PROJECT_BINARY_DIR}/config/ZC_Config.h)
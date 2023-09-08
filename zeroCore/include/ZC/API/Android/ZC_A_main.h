#pragma once

#include <ZC/API/Android/ZC_A_Window.h>

#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))


#include <ZC/API/Android/ZC_API_Android.h>

void ZC_main(ZC_pAPIFactory apiFactory);

void android_main(android_app* pAndroidApp)
{
    std::shared_ptr<ZC_A_Window> window = std::make_shared<ZC_A_Window>(pAndroidApp);
    ZC_pAPIFactory apiFactory = ZC_API_Android::ZC_GetAPI(window);

    ZC_main(apiFactory);
}
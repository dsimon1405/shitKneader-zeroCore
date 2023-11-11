#pragma once

#include <ZC/main/ZC_main.h>
#include <ZC/Video/ZC_android_app.h>

#include <android/sensor.h>

#include <fstream>

void android_main(android_app* pAndroidApp)
{
//    ASensorEventQueue_getEvents



//    jclass context = pAndroidApp->activity->env->FindClass("android/content/Context");
//
//    jfieldID audioServiceField = pAndroidApp->activity->env->GetStaticFieldID(context, "AUDIO_SERVICE", "Ljava/lang/String;");
//
//    jstring jstr = (jstring)pAndroidApp->activity->env->GetStaticObjectField(context, audioServiceField);
//
//    jmethodID getSystemServiceID = pAndroidApp->activity->env->GetMethodID(context, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
//
////    jobject tm = pAndroidApp->activity->env->CallObjectMethod(currentAndroidActivity, getSystemServiceID, jstr);
//    jobject tm = pAndroidApp->activity->env->CallObjectMethod(pAndroidApp->activity->vm->, getSystemServiceID, jstr);
//
//    jclass AudioManager = pAndroidApp->activity->env->FindClass("android/media/AudioManager");
//
//    jmethodID getStreamVolume = pAndroidApp->activity->env->GetMethodID(AudioManager, "getStreamVolume", "(I)I");
//
//    jint stream = 3; //MUSIC_STREAM = 3
//    int volume = pAndroidApp->activity->env->CallIntMethod(tm, getStreamVolume, stream);
//    DEBUG_LOG(DEBUG_TAG, "volume = " + to_string(volume));

    ZC_android_app AndroidApp(pAndroidApp);
    ZC_main();
}
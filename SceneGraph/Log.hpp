#ifdef __APPLE__
    #define LOGI printf
    #define LOGE printf
    #define LOGV printf
    #define LOGD printf
    #define LOGW printf
#elif  defined __ANDROID__
    #include <jni.h>
    #include <android/log.h>
//! JNI Information and Error Log
    #define  LOG_TAG    "senseeCore"
    #define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG,__VA_ARGS__)
    #define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
    #define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG,__VA_ARGS__)
    #define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__)
    #define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG,__VA_ARGS__)
#endif

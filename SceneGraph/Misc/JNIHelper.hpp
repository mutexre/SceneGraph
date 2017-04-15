//
// Created by Sergey Vasilenko on 28.10.16.
//

#ifndef ANDROID_JNIHELPER_HPP
#define ANDROID_JNIHELPER_HPP

#ifdef __ANDROID__

    #include <jni.h>
    #include <Log.hpp>

namespace JniHelper {

    static bool isJByteBufferInitialized;
    static jclass nioAccessClass;
    static jclass bufferClass;
    static jmethodID getBasePointerID;
    static jmethodID getBaseArrayID;
    static jmethodID getBaseArrayOffsetID;
    static jfieldID positionID;
    static jfieldID limitID;
    static jfieldID elementSizeShiftID;

    static jfloat
    getFloatField(JNIEnv* env, jobject& obj, const char* fieldName) {
        jclass clazz = env->GetObjectClass(obj);
        jfieldID fieldId = env->GetFieldID(clazz, fieldName, "F");
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
        }
        jfloat value = env->GetFloatField(obj, fieldId);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
        }
        return value;
    }

    static void *
    getPointerFromByteBuffer(JNIEnv *_env, jobject buffer, jarray *array, jint *remaining, jint *offset) {
        jint position;
        jint limit;
        jint elementSizeShift;
        jlong pointer;

        if (!isJByteBufferInitialized) {
            jclass nioAccessClassLocal = _env->FindClass("java/nio/NIOAccess");
            nioAccessClass = (jclass) _env->NewGlobalRef(nioAccessClassLocal);

            jclass bufferClassLocal = _env->FindClass("java/nio/Buffer");
            bufferClass = (jclass) _env->NewGlobalRef(bufferClassLocal);

            getBasePointerID = _env->GetStaticMethodID(nioAccessClass, "getBasePointer", "(Ljava/nio/Buffer;)J");
            getBaseArrayID = _env->GetStaticMethodID(nioAccessClass, "getBaseArray", "(Ljava/nio/Buffer;)Ljava/lang/Object;");
            getBaseArrayOffsetID = _env->GetStaticMethodID(nioAccessClass, "getBaseArrayOffset", "(Ljava/nio/Buffer;)I");

            positionID = _env->GetFieldID(bufferClass, "position", "I");
            limitID = _env->GetFieldID(bufferClass, "limit", "I");
            elementSizeShiftID = _env->GetFieldID(bufferClass, "_elementSizeShift", "I");
            isJByteBufferInitialized = true;
        }

        position = _env->GetIntField(buffer, positionID);
        limit = _env->GetIntField(buffer, limitID);
        elementSizeShift = _env->GetIntField(buffer, elementSizeShiftID);
        *remaining = (limit - position) << elementSizeShift;
        pointer = _env->CallStaticLongMethod(nioAccessClass, getBasePointerID, buffer);
        if (pointer != 0L) {
            *array = NULL;
            return reinterpret_cast<void *>(pointer);
        }

        *array = (jarray) _env->CallStaticObjectMethod(nioAccessClass, getBaseArrayID, buffer);
        *offset = _env->CallStaticIntMethod(nioAccessClass, getBaseArrayOffsetID, buffer);

        return NULL;
    }

    static void
    releasePointer(JNIEnv *_env, jarray array, void *data, jboolean commit) {
        _env->ReleasePrimitiveArrayCritical(array, data, commit ? 0 : JNI_ABORT);
    }
}
#endif // __ANDROID__
#endif //ANDROID_JNIHELPER_HPP

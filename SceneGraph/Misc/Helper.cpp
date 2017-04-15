//
//  helper.cpp
//  SceneGraph
//
//  Created by mutexre on 09/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <SceneGraph/SceneGraph.hpp>

#ifdef __ANDROID__
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
    #include <SceneGraphGL/SceneGraphGL.hpp>

    JavaVM* SG::jvm;
#endif

string SG::readFile(const string& path) {
    ifstream ifs(path);
    stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

#ifdef __APPLE__

Option<string> getStringFromCFString(CFStringRef cfstr, unsigned maxChars = 2 * 1024)
{
    size_t bufferSize = 256;
    Boolean result;
    
    do {
        unique_ptr<char[]> buffer(new char[bufferSize]);
        result = CFStringGetCString(cfstr, buffer.get(), bufferSize, kCFStringEncodingUTF8);
        if (result)
            return Option<string>(buffer.get());
        else
            bufferSize <<= 1;
    }
    while (bufferSize < maxChars);
    
    return Option<string>();
}

Option<string> SG::findResourcePathByName(CFBundleRef bundle, const char* name, const char* ext) {
    auto _name = CFStringCreateWithCString(kCFAllocatorDefault, name, kCFStringEncodingUTF8);
    CFUniqueStr fileName{ _name, cfDeleter };

    auto _ext = CFStringCreateWithCString(kCFAllocatorDefault, ext, kCFStringEncodingUTF8);
    CFUniqueStr fileExt{ _ext, cfDeleter };

    auto _url = CFBundleCopyResourceURL(bundle, fileName.get(), fileExt.get(), nullptr);
    CFUniqueURL url{ _url, cfDeleter };
    if (url) {
        auto _path = CFURLCopyFileSystemPath(url.get(), kCFURLPOSIXPathStyle);
        CFUniqueStr path{ _path, cfDeleter };
        return getStringFromCFString(path.get());
    }

    return Option<string>();
}

Option<string> SG::findResourcePathByName(const char* name, const char* ext) {
    return findResourcePathByName(CFBundleGetMainBundle(), name, ext);
}

Option<string> SG::findResourcePathByName(const string& name, const string& ext) {
    return findResourcePathByName(name.c_str(), ext.c_str());
}

#endif

#ifdef __ANDROID__

JNIEnv* SG::getJNIEnv() {
    JNIEnv* g_env;
    // double check it's all ok
    int getEnvStat = SG::jvm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        LOGE("GetEnv: not attached");
        if (SG::jvm->AttachCurrentThread(&g_env, NULL) != 0) {
            LOGE("Failed to attach");
        }
    } else if (getEnvStat == JNI_OK) {
        //
    } else if (getEnvStat == JNI_EVERSION) {
        LOGE("GetEnv: version not supported");
    }


    /*g_vm->DetachCurrentThread();*/
    return g_env;
}

AAssetManager* SG::getAssetManager() {
    JNIEnv* env = SG::getJNIEnv();
    jclass jclazz = env->FindClass("com/core/jni/NativeHelper");
    jmethodID methodID = env->GetStaticMethodID(jclazz, "getAssetManager", "()Landroid/content/res/AssetManager;");
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
    }
    jobject assetManagerJava = env->CallStaticObjectMethod(jclazz, methodID);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
    }
    AAssetManager* am = AAssetManager_fromJava(env, assetManagerJava);
    return am;
}

AAsset* findShaderAsset(const string& filename) {
    AAssetManager* am = SG::getAssetManager();
    return AAssetManager_open(am, ("Shaders/" + filename).c_str(), AASSET_MODE_BUFFER);
}

string readShader(AAsset* asset) {
    long length = AAsset_getLength(asset);
    const void* buffer = AAsset_getBuffer(asset);
    if (buffer == NULL) {
        LOGE("getBuffer failed");
        JNIEnv* env = SG::getJNIEnv();
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
        }
    }
    std::string s((const char*) buffer, (unsigned int) length);
    AAsset_close(asset);
//    LOGE("shader loaded: %s", (const char *) buffer);
    return s;
}

double SG::getTime()
{
    JNIEnv* env = SG::getJNIEnv();
    jclass clazz = env->FindClass("android/os/SystemClock");
    jmethodID method = env->GetStaticMethodID(clazz, "uptimeMillis", "()J");
    jlong uptimeMillis = env->CallStaticLongMethod(clazz, method);
    return double(uptimeMillis) / 1000.0;
}

#endif


Option<SG::Program::Source> SG::readProgramSource(const char* vertex, const char* fragment)
{
    Program::Source src;

#ifdef __APPLE__
    auto bundle = CFBundleGetMainBundle();
    if (bundle) {
        auto vertexShaderPath = findResourcePathByName(bundle, vertex, "vert");
        if (!vertexShaderPath) {
            printf("vertex shader not found: %s\n", vertex);
            return Option<SG::Program::Source>();
        }

        auto fragmentShaderPath = findResourcePathByName(bundle, fragment, "frag");
        if (!fragmentShaderPath) {
            printf("fragment shader not found: %s\n", fragment);
            return Option<SG::Program::Source>();
        }

        src.vertex = readFile(vertexShaderPath.value);
        src.fragment = readFile(fragmentShaderPath.value);
    }
#elif defined _WIN32 || defined _WIN64
    src.vertex = readFile(string(vertex) + ".vert");
    src.fragment = readFile(string(fragment) + ".frag");
#elif defined __ANDROID__
    AAsset* vertexShaderPath = findShaderAsset(string(vertex) + ".vert");
    if (!vertexShaderPath) {
        LOGW("vertex shader not found: %s\n", vertex);
        throw runtime_error(string("vertex shader not found: \"") + vertex + ".vert\"");
    }

    AAsset* fragmentShaderPath = findShaderAsset(string(fragment) + ".frag");
    if (!fragmentShaderPath) {
        LOGW("fragment shader not found: %s\n", fragment);
        AAsset_close(vertexShaderPath);
        throw runtime_error(string("fragment shader not found: \"") + fragment + ".frag\"");
    }
    src.vertex = readShader(vertexShaderPath);
    src.fragment = readShader(fragmentShaderPath);
#endif

    return Option<Program::Source>(src);
}

void SG::getPixelFormatComponentsAndDataType(PixelFormat format,
                                             ColorComponents& components,
                                             PixelDataType& dataType)
{
    switch (format)
    {
        case PixelFormat::r8:
            components = ColorComponents::red;
            dataType = PixelDataType::u8;
        break;
        
        case PixelFormat::r8_snorm:
            components = ColorComponents::red;
            dataType = PixelDataType::snorm8;
        break;
        
        case PixelFormat::r16f:
            components = ColorComponents::red;
            dataType = PixelDataType::f16;
        break;
        
        case PixelFormat::r32f:
            components = ColorComponents::red;
            dataType = PixelDataType::f32;
        break;
        
        case PixelFormat::r8i:
            components = ColorComponents::red;
            dataType = PixelDataType::s8;
        break;
        
        case PixelFormat::r8ui:
            components = ColorComponents::red;
            dataType = PixelDataType::u8;
        break;
        
        case PixelFormat::r16i:
            components = ColorComponents::red;
            dataType = PixelDataType::s16;
        break;
        
        case PixelFormat::r16ui:
            components = ColorComponents::red;
            dataType = PixelDataType::u16;
        break;
        
        case PixelFormat::r32i:
            components = ColorComponents::red;
            dataType = PixelDataType::s32;
        break;
        
        case PixelFormat::r32ui:
            components = ColorComponents::red;
            dataType = PixelDataType::u32;
        break;
        
        case PixelFormat::rg8:
            components = ColorComponents::rg;
            dataType = PixelDataType::u8;
        break;
        
        case PixelFormat::rg8_snorm:
            components = ColorComponents::rg;
            dataType = PixelDataType::snorm8;
        break;
        
        case PixelFormat::rg16f:
            components = ColorComponents::rg;
            dataType = PixelDataType::f16;
        break;
        
        case PixelFormat::rg32f:
            components = ColorComponents::rg;
            dataType = PixelDataType::f32;
        break;
        
        case PixelFormat::rg8i:
            components = ColorComponents::rg;
            dataType = PixelDataType::s8;
        break;
        
        case PixelFormat::rg8ui:
            components = ColorComponents::rg;
            dataType = PixelDataType::u8;
        break;
        
        case PixelFormat::rg16i:
            components = ColorComponents::rg;
            dataType = PixelDataType::s16;
        break;
        
        case PixelFormat::rg16ui:
            components = ColorComponents::rg;
            dataType = PixelDataType::u16;
        break;

        case PixelFormat::rg32i:
            components = ColorComponents::rg;
            dataType = PixelDataType::s32;
        break;
        
        case PixelFormat::rg32ui:
            components = ColorComponents::rg;
            dataType = PixelDataType::u32;
        break;

        case PixelFormat::rgb8:
            components = ColorComponents::rgb;
            dataType = PixelDataType::u8;
        break;

        case PixelFormat::rgb8_snorm:
            components = ColorComponents::rgb;
            dataType = PixelDataType::snorm8;
        break;
        
        case PixelFormat::rgb565:
            components = ColorComponents::rgb;
            dataType = PixelDataType::u565;
        break;
        
        case PixelFormat::srgb8:
            components = ColorComponents::rgb;
            dataType = PixelDataType::u8;
        break;
        
        case PixelFormat::rgb16f:
            components = ColorComponents::rgb;
            dataType = PixelDataType::f16;
        break;
        
        case PixelFormat::rgb32f:
            components = ColorComponents::rgb;
            dataType = PixelDataType::f32;
        break;
        
        case PixelFormat::r11f_g11f_b10f:
            components = ColorComponents::rgb;
            dataType = PixelDataType::f11_f11_f10;
        break;
        
        case PixelFormat::rgb9_e5:
            components = ColorComponents::rgb;
            dataType = PixelDataType::f5_9_9_9_rev;
        break;
        
        case PixelFormat::rgb8i:
            components = ColorComponents::rgb;
            dataType = PixelDataType::s8;
        break;
        
        case PixelFormat::rgb8ui:
            components = ColorComponents::rgb;
            dataType = PixelDataType::u8;
        break;
        
        case PixelFormat::rgb16i:
            components = ColorComponents::rgb;
            dataType = PixelDataType::s16;
        break;
        
        case PixelFormat::rgb16ui:
            components = ColorComponents::rgb;
            dataType = PixelDataType::u16;
        break;
        
        case PixelFormat::rgb32i:
            components = ColorComponents::rgb;
            dataType = PixelDataType::s32;
        break;
        
        case PixelFormat::rgb32ui:
            components = ColorComponents::rgb;
            dataType = PixelDataType::u32;
        break;
        
// rgba4, rgb5_a1, rgba8, rgba8_snorm, rgb10_a2, rgb10_a2ui, srgb8_alpha8, rgba16f, rgba32f, rgba8i, rgba8ui, rgba16i, rgba16ui, rgba32i, rgba32ui,
        
        case PixelFormat::rgba4:
            components = ColorComponents::rgba;
            dataType = PixelDataType::u4444;
        break;
        
        case PixelFormat::rgb5_a1:
            components = ColorComponents::rgba;
            dataType = PixelDataType::u5551;
        break;

        case PixelFormat::rgba8:
            components = ColorComponents::rgba;
            dataType = PixelDataType::u8;
        break;
        
        case PixelFormat::rgba8_snorm:
            components = ColorComponents::rgba;
            dataType = PixelDataType::snorm8;
        break;
        
        case PixelFormat::rgb10_a2:
            components = ColorComponents::rgba;
            dataType = PixelDataType::u10_10_10_2;
        break;
        
        case PixelFormat::rgb10_a2ui:
            components = ColorComponents::rgba;
            dataType = PixelDataType::u10_10_10_2;
        break;

        case PixelFormat::srgb8_alpha8:
            components = ColorComponents::rgba;
            dataType = PixelDataType::u8;
        break;

        case PixelFormat::rgba16f:
            components = ColorComponents::rgba;
            dataType = PixelDataType::f16;
        break;

        case PixelFormat::rgba32f:
            components = ColorComponents::rgba;
            dataType = PixelDataType::f32;
        break;
        
        case PixelFormat::luminance:
            components = ColorComponents::luminance;
            dataType = PixelDataType::u8;
        break;

        case PixelFormat::luminance_alpha:
            components = ColorComponents::luminance_alpha;
            dataType = PixelDataType::u8;
        break;
        
        default: break;
    }
}

unsigned char SG::getNumberOfComponents(ColorComponents components)
{
    switch (components)
    {
        case ColorComponents::red:
        case ColorComponents::green:
        case ColorComponents::blue:
        case ColorComponents::alpha:
        case ColorComponents::luminance:
        case ColorComponents::stencil:
        case ColorComponents::depth:
            return 1;
        
        case ColorComponents::rg:
        case ColorComponents::depth_stencil:
        case ColorComponents::luminance_alpha:
            return 2;
        
        case ColorComponents::rgb:
        case ColorComponents::bgr:
            return 3;
        
        case ColorComponents::rgba:
        case ColorComponents::bgra:
            return 4;
    }
    return 0;
}

unsigned char SG::getPixelDataSize(ColorComponents colorComponents, PixelDataType dataType)
{
    switch (dataType)
    {
        case PixelDataType::u8:
        case PixelDataType::s8:
            return getNumberOfComponents(colorComponents);
        
        case PixelDataType::u332:
        case PixelDataType::u233_rev:
            return 1;
        
        case PixelDataType::u16:
        case PixelDataType::s16:
        case PixelDataType::u565:
        case PixelDataType::u565_rev:
        case PixelDataType::u4444:
        case PixelDataType::u4444_rev:
        case PixelDataType::u5551:
        case PixelDataType::u1555_rev:
            return 2;
        
        case PixelDataType::u32:
        case PixelDataType::s32:
        case PixelDataType::f32:
        case PixelDataType::u8888:
        case PixelDataType::u8888_rev:
        case PixelDataType::u10_10_10_2:
        case PixelDataType::u2_10_10_10_rev:
            return 4;
        
        default: break;
    }
    return 0;
}

//
//  helper.h
//  SceneGraph
//
//  Created by mutexre on 08/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
    #include <CoreGraphics/CoreGraphics.h>
#elif defined __ANDROID__
    #include <SceneGraph/Misc/JNIHelper.hpp>
    #include <android/asset_manager.h>
#endif

#include <SceneGraph/Log.hpp>

namespace SG
{
    string readFile(const string& path);

#ifdef __APPLE__

    Option<string> findResourcePathByName(CFBundleRef bundle, const char* name, const char* ext);
    Option<string> findResourcePathByName(const char* name, const char* ext);
    Option<string> findResourcePathByName(const string& name, const string& ext);

    auto cfDeleter = [](CFTypeRef ref) {
        if (ref) CFRelease(ref);
    };

    template <typename T>
    using CFUnique = unique_ptr<T, decltype(cfDeleter)>;

    using CFUniqueStr = CFUnique<const __CFString>;
    using CFUniqueURL = CFUnique<const __CFURL>;

#elif defined __ANDROID__

    extern JavaVM* jvm;

    JNIEnv* getJNIEnv();
    AAssetManager* getAssetManager();

#endif

    Option<SG::Program::Source> readProgramSource(const char* vertex, const char* fragment);
    shared_ptr<SG::Program> loadProgram(const char* vertexShaderName, const char* fragmentShaderName);
    
    void getPixelFormatComponentsAndDataType(PixelFormat, ColorComponents&, PixelDataType&);
    unsigned char getNumberOfComponents(ColorComponents);
    unsigned char getPixelDataSize(ColorComponents, PixelDataType);
    
    double getTime(); // seconds since the beginning of 1970 (with at least milliseconds precision)
}
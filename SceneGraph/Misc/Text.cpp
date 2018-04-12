//
//  Created by mutexre on 12/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

#ifdef __APPLE__
    #include <CoreGraphics/CoreGraphics.h>
    #include <CoreText/CoreText.h>
#elif defined __ANDROID__
    #include <android/bitmap.h>
#endif
#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

#ifdef __APPLE__

vec2 SG::getTextRectSize(const char* text,
                         const char* fontName,
                         float fontSize,
                         float maxWidth,
                         float maxHeight)
{
    CFStringRef fontNameRef = CFStringCreateWithCString(kCFAllocatorDefault, fontName, kCFStringEncodingUTF8);
    CTFontRef font = CTFontCreateWithName(fontNameRef, fontSize, nullptr);

    CFStringRef str = CFStringCreateWithCString(kCFAllocatorDefault, text, kCFStringEncodingUTF8);
    auto strLen = CFStringGetLength(str);
    CFRange range = CFRangeMake(0, strLen);

    CTTextAlignment paragraphAlignment = kCTTextAlignmentLeft;
    CTParagraphStyleSetting paragraphStyleSetting = {
        kCTParagraphStyleSpecifierAlignment,
        sizeof(paragraphAlignment),
        &paragraphAlignment
    };
    CTParagraphStyleRef paragraphStyle = CTParagraphStyleCreate(&paragraphStyleSetting, 1);

    const void* keys[] = { kCTFontAttributeName, kCTParagraphStyleAttributeName };
    const void* values[] = { font, paragraphStyle };
    CFDictionaryRef dict = CFDictionaryCreate(kCFAllocatorDefault, keys, values, 2, nullptr, nullptr);

    CFAttributedStringRef attrStr = CFAttributedStringCreate(kCFAllocatorDefault, str, dict);
    CTFramesetterRef frameSetter = CTFramesetterCreateWithAttributedString(attrStr);

    CGSize constraints;
    constraints.width = (maxWidth == 0 ? CGFLOAT_MAX : maxWidth);
    constraints.height = (maxHeight == 0 ? CGFLOAT_MAX : maxHeight);

    CFRange fitRange;
    CGSize size = CTFramesetterSuggestFrameSizeWithConstraints(frameSetter, range, nullptr, constraints, &fitRange);
    
    CFRelease(frameSetter);
    CFRelease(attrStr);
    CFRelease(dict);
    CFRelease(paragraphStyle);
    CFRelease(str);
    CFRelease(font);
    CFRelease(fontNameRef);
    
    return vec2(size.width, size.height);
}

vector<char>
SG::createTextBitmap(const char* text,
                     const char* fontName,
                     float fontSize,
                     vec4 backgroundColor,
                     vec4 fontColor,
                     unsigned w, unsigned h)
{
    vector<char> data((w * h) << 2);

    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(data.data(), w, h, 8, w << 2,
                                                 colorSpace,
                                                 kCGImageAlphaPremultipliedLast);

    CFStringRef fontNameRef = CFStringCreateWithCString(kCFAllocatorDefault, fontName, kCFStringEncodingUTF8);
    CTFontRef font = CTFontCreateWithName(fontNameRef, fontSize, nullptr);
    CGRect textRect = CGRectMake(0.f, 0.f, w, h);
    CGMutablePathRef path = CGPathCreateMutable();

    CGRect rect = CGRectMake(0, 0, w, h);
    CGPathAddRect(path, nullptr, rect);

    CFStringRef str = CFStringCreateWithCString(kCFAllocatorDefault, text, kCFStringEncodingUTF8);
    auto strLen = CFStringGetLength(str);
    CFRange range = CFRangeMake(0, strLen);

    CGFloat rgba[] = { fontColor.r, fontColor.g, fontColor.b, fontColor.a };
    CGColorRef color = CGColorCreate(colorSpace, rgba);

    CTTextAlignment paragraphAlignment = kCTTextAlignmentLeft;
    CTParagraphStyleSetting paragraphStyleSetting = {
        kCTParagraphStyleSpecifierAlignment,
        sizeof(paragraphAlignment),
        &paragraphAlignment
    };
    CTParagraphStyleRef paragraphStyle = CTParagraphStyleCreate(&paragraphStyleSetting, 1);

    const void* keys[] = { kCTFontAttributeName, kCTForegroundColorAttributeName, kCTParagraphStyleAttributeName };
    const void* values[] = { font, color, paragraphStyle };
    CFDictionaryRef dict = CFDictionaryCreate(kCFAllocatorDefault, keys, values, 3, nullptr, nullptr);

    CFAttributedStringRef attrStr = CFAttributedStringCreate(kCFAllocatorDefault, str, dict);
    CTFramesetterRef frameSetter = CTFramesetterCreateWithAttributedString(attrStr);
    CTFrameRef frame = CTFramesetterCreateFrame(frameSetter, range, path, nullptr);

    CGContextSetTextMatrix(context, CGAffineTransformIdentity);
    CGContextScaleCTM(context, 1.f, 1.f);

    CGContextSetRGBFillColor(context, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    CGContextFillRect(context, textRect);

    CTFrameDraw(frame, context);

    CFRelease(frame);
    CFRelease(frameSetter);
    CFRelease(attrStr);
    CFRelease(dict);
    CFRelease(paragraphStyle);
    CFRelease(color);
    CFRelease(str);
    CGPathRelease(path);
    CFRelease(font);
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    CFRelease(fontNameRef);

    return data;
}

#endif

#ifdef __ANDROID__

using namespace JniHelper;

vec2 SG::getTextRectSize(const char* text,
                         const char* fontName,
                         float fontSize,
                         float maxWidth,
                         float maxHeight)
{
    JNIEnv* env = SG::getJNIEnv();
    jclass jclazz = env->FindClass("com/core/jni/TextNative");
    jmethodID methodID = env->GetStaticMethodID(jclazz, "getTextRectSize", "(Ljava/lang/String;Ljava/lang/String;FFF)Landroid/graphics/PointF;");
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
    }
    jstring jtext = env->NewStringUTF(text);
    jstring jfontName = env->NewStringUTF(fontName);
    jobject jpoint = env->CallStaticObjectMethod(jclazz, methodID, jtext, jfontName, fontSize, maxWidth, maxHeight);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
    }
    jfloat x = getFloatField(env, jpoint, "x");
    jfloat y = getFloatField(env, jpoint, "y");
    return vec2(x, y);
}

inline unsigned convertColor(vec4 &color) {
    unsigned a = (unsigned) roundf(color.a * 255);
    unsigned r = (unsigned) roundf(color.r * 255);
    unsigned g = (unsigned) roundf(color.g * 255);
    unsigned b = (unsigned) roundf(color.b * 255);
    return a << 24 | r << 16 | g << 8 | b;
}

vector<char>
SG::createTextBitmap(const char* text,
                     const char* fontName,
                     float fontSize,
                     vec4 backgroundColor,
                     vec4 fontColor,
                     unsigned w, unsigned h)
{
    JNIEnv* env = SG::getJNIEnv();
    jclass jclazz = env->FindClass("com/core/jni/TextNative");
    /*
     * String text, String fontName, float fontSize, int backgroundColor,
	*										  int fontColor, int width, int height
     */
    jmethodID methodID = env->GetStaticMethodID(jclazz, "createTextBitmap", "(Ljava/lang/String;Ljava/lang/String;FIIII)Ljava/nio/ByteBuffer;");
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
    }
    jstring jtext = env->NewStringUTF(text);
    jstring jfontName = env->NewStringUTF(fontName);
    jint jbgColor = convertColor(backgroundColor);
    jint jtextColor = convertColor(fontColor);
    jobject jbyteBuffer = env->CallStaticObjectMethod(jclazz, methodID, jtext, jfontName, fontSize, jbgColor, jtextColor, w, h);

    jarray _array = (jarray) 0;
    jint _bufferOffset = (jint) 0;
    // initialize with invalid value
    jint _remaining = -1;
    char *pixels = (char *) 0;

    if (jbyteBuffer) {
        pixels = (char *) getPointerFromByteBuffer(env, jbyteBuffer, (jarray*)&_array, &_remaining, &_bufferOffset);
    }
    if (jbyteBuffer && pixels == NULL) {
        char * _pixelsBase = (char *)env->GetPrimitiveArrayCritical(_array, (jboolean *) 0);
        pixels =  _pixelsBase + _bufferOffset;
    }

    vector<char> data((w * h) << 2);
    memcpy(data.data(), pixels, (w * h) << 2);
    if (_array) {
        releasePointer(env, _array, pixels, JNI_FALSE);
    }
    return data;
}
#endif


shared_ptr<Texture>
SG::createTextureFromText(const char* text,
                          const char* fontName,
                          float fontSize,
                          vec4 backgroundColor,
                          vec4 fontColor,
                          unsigned w, unsigned h,
                          const shared_ptr<Context>& context)
{
    auto data = createTextBitmap(text, fontName, fontSize, backgroundColor, fontColor, w, h);
    
    auto texture = context->createTexture(Texture::Type::t2d, PixelFormat::rgba8);
    texture->setImage(data.data(), w, h, 0, SG::ColorComponents::rgba, SG::PixelDataType::u8);
    
    return texture;
}

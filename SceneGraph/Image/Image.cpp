//
//  Created by mutexre on 08/01/16.
//  Copyright © 2016 mutexre. All rights reserved.
//

#import <SceneGraph/SceneGraph.hpp>
#import <stb/stb_image_resize.h>

using namespace SG;

Image::Image()
{}

Image::Image(const string& path, bool flipVertical, bool flipHorizontal)
{
    storage.type = StorageType::internal;
    storage.internal = loadImage(path, w, h, bytesPerRow, components, dataType, flipVertical, flipHorizontal);
    data = storage.internal.data();
}

Image::Image(char* data, int w, int h,
             ColorComponents components,
             PixelDataType dataType,
             Option<int> bytesPerRow,
             bool copyDataToInternalStorage)
{
    if (!copyDataToInternalStorage)
        setExternalStorage(data);
    else
        copyExternalDataToInternalStorage(data, w, h, components, dataType, bytesPerRow);
    
    this->w = w;
    this->h = h;
    this->bytesPerRow = (bytesPerRow ? bytesPerRow.value : w * getPixelDataSize(components, dataType));
    this->components = components;
    this->dataType = dataType;
}

Image::~Image()
{}

Image::StorageType Image::getStorageType() const {
    return storage.type;
}

unsigned Image::getW() const {
    return w;
}

unsigned Image::getH() const {
    return h;
}

unsigned Image::getBytesPerRow() const {
    return bytesPerRow;
}

ColorComponents Image::getColorComponents() const {
    return components;
}

PixelDataType Image::getPixelDataType() const {
    return dataType;
}

const char* Image::getData() const {
    return data;
}

char* Image::getData() {
    return data;
}

void Image::setExternalStorage(char* ptr)
{
    storage.type = StorageType::external;
    storage.external = ptr;
    data = ptr;
}

void Image::copyExternalDataToInternalStorage(const char* data, int w, int h,
                                              ColorComponents components,
                                              PixelDataType dataType,
                                              Option<int> bytesPerRow)
{
    auto dataSize = calcDataSize(w, h, components, dataType, bytesPerRow);
    storage.internal.resize(dataSize);
    this->data = storage.internal.data();
    
    memcpy(this->data, data, dataSize);
    
    storage.type = StorageType::internal;
}

void Image::copyDataToInternalStorage()
{
    if (storage.type == StorageType::external)
        copyExternalDataToInternalStorage(data, w, h, components, dataType, bytesPerRow);
}

vector<char>
SG::loadImage(const string& path,
              unsigned& w, unsigned& h, unsigned& bytesPerRow,
              ColorComponents& colorComponents,
              PixelDataType& pixelDataType,
              bool flipVertical,
              bool flipHorizontal)
{
#ifdef __APPLE__
    CFUnique<CGDataProvider> dataProvider{
        CGDataProviderCreateWithFilename(path.c_str()),
        cfDeleter
    };
    
    if (!dataProvider)
        throw runtime_error(string("Failed to create data provider for image: ") + path);

    bool isJPG = false;
    
    const char* end = strrchr(path.c_str(), '.');
    if (strcmp(end, ".jpg") == 0 || strcmp(end, ".jpeg") == 0)
        isJPG = true;
    
    auto _image = (isJPG) ? CGImageCreateWithJPEGDataProvider(dataProvider.get(), nullptr, false, kCGRenderingIntentDefault) : CGImageCreateWithPNGDataProvider(dataProvider.get(), nullptr, false, kCGRenderingIntentDefault);
    if (!_image)
        throw runtime_error(string("Failed to load image: ") + path);
    
    CFUnique<CGImage> image{ _image, cfDeleter };

    CGImageAlphaInfo alphaInfo = CGImageGetAlphaInfo(_image);
    CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(_image);
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(_image);
    size_t bitsPerComponent = CGImageGetBitsPerComponent(_image);
    size_t bitsPerPixel = CGImageGetBitsPerPixel(_image);
    size_t bytesPerPixel = (bitsPerPixel + 7) / 8;

    w = static_cast<unsigned>(CGImageGetWidth(image.get()));
    h = static_cast<unsigned>(CGImageGetHeight(image.get()));
    auto data = vector<char>(w * h * bytesPerPixel);

    if (alphaInfo == kCGImageAlphaFirst)
        alphaInfo = kCGImageAlphaPremultipliedFirst;

    if (alphaInfo == kCGImageAlphaLast)
        alphaInfo = kCGImageAlphaPremultipliedLast;

    bitmapInfo &= ~kCGBitmapAlphaInfoMask;
    bitmapInfo |= alphaInfo;

    CGContextRef context = CGBitmapContextCreate(data.data(), w, h, bitsPerComponent, w * bytesPerPixel,
                                                 colorSpace, bitmapInfo);

    if (flipVertical) {
        CGAffineTransform flip = CGAffineTransformMake(1, 0, 0, -1, 0, h);
        CGContextConcatCTM(context, flip);
    }

    if (flipHorizontal) {
        CGAffineTransform flip = CGAffineTransformMake(-1, 0, 0, 1, w, 0);
        CGContextConcatCTM(context, flip);
    }

    CGContextDrawImage(context, CGRectMake(0, 0, w, h), _image);
    CGContextRelease(context);

/*    switch (alphaInfo) {
        case kCGImageAlphaNone:
        case kCGImageAlphaNoneSkipLast:
        case kCGImageAlphaNoneSkipFirst:
            components = Components::rgba;
        break;

        default:
            components = Components::rgba;
        break;
    }*/

    colorComponents = ColorComponents::rgba;
    pixelDataType = PixelDataType::u8;
    bytesPerRow = w * getPixelDataSize(colorComponents, pixelDataType);
    
    return data;
#elif defined __ANDROID__
    LOGI("loadImage from %s", path);
    // TODO set bitsPerPixel and load real data
    size_t bitsPerPixel = 8;
    size_t bytesPerPixel = (bitsPerPixel + 7) / 8;

    auto data = vector<char>(w * h * bytesPerPixel);
    return data;
#else
    #error Not implemented
#endif
}

size_t Image::calcDataSize(unsigned w, unsigned h,
                           ColorComponents components,
                           PixelDataType dataType,
                           Option<int> bytesPerRow)
{
    return h * (bytesPerRow ? bytesPerRow.value : w * getPixelDataSize(components, dataType));
}

void Image::resizeInternalStorage(unsigned w, unsigned h) {
    auto dataSize = calcDataSize(w, h, components, dataType, bytesPerRow);
    storage.internal.resize(dataSize);
}

bool Image::resample(unsigned w, unsigned h)
{
    if (storage.type == StorageType::internal)
    {
        auto newDataSize = calcDataSize(w, h, components, dataType, bytesPerRow);
        vector<char> newCanvas(newDataSize);
        
        stbir_resize_uint8((const unsigned char*)data, this->w, this->h, 0,
                           (unsigned char*)newCanvas.data(), w, h, 0, 4);
        
        storage.internal = newCanvas;
        data = newCanvas.data();
        
        this->w = w;
        this->h = h;
        
        return true;
    }
    
    return false;
}

shared_ptr<Image> Image::getResampledImage(unsigned w, unsigned h) const
{
    if (storage.type == StorageType::internal)
    {
        auto copy = shared_ptr<Image>(new Image(*this));
        copy->resample(w, h);
        return copy;
    }
    
    return nullptr;
}

mat3 Image::calcPaddingUvTransform() const
{
    mat3 m;
    auto pixelDataSize = getPixelDataSize(components, dataType);
    m[0][0] = float(w) / float(bytesPerRow / pixelDataSize);
    return m;
}

//
//  Created by mutexre on 08/01/16.
//  Copyright © 2016 mutexre. All rights reserved.
//

#import <SceneGraph/SceneGraph.hpp>

using namespace SG;

ImageStack::ImageStack()
{}

ImageStack::ImageStack(const vector<string>& paths, bool flipVertical, bool flipHorizontal)
{
    for (const string& p : paths) {
        subImages.push_back(make_shared<Image>(p, flipVertical, flipHorizontal));
    }
    
    const auto& first = subImages.front();
    updateStateBasedOnImage(first);
}

ImageStack::~ImageStack()
{}

ImageStack::ImageStack(const ImageStack& image)
{
    w = image.w;
    h = image.h;
    components = image.components;
    dataType = image.dataType;
    
    subImages.clear();
    for (auto& subImage : image.subImages) {
        auto copy = shared_ptr<Image>(new Image(*subImage));
        subImages.push_back(copy);
    }
}

unsigned ImageStack::getW() const {
    return w;
}

unsigned ImageStack::getH() const {
    return h;
}

unsigned ImageStack::getD() const {
    return subImages.size();
}

ColorComponents ImageStack::getColorComponents() const {
    return components;
}

PixelDataType ImageStack::getPixelDataType() const {
    return dataType;
}

const char* ImageStack::getData(unsigned z) const {
    return subImages[z]->getData();
}

char* ImageStack::getData(unsigned z) {
    return subImages[z]->getData();
}

const shared_ptr<Image>& ImageStack::operator[](unsigned z) const {
    return subImages[z];
}

void ImageStack::resample(unsigned w, unsigned h) {
    for (auto& image : subImages)
        image->resample(w, h);
    
    this->w = w;
    this->h = h;
}

shared_ptr<ImageStack> ImageStack::getResampledImage(unsigned w, unsigned h) const {
    auto copy = shared_ptr<ImageStack>(new ImageStack(*this));
    copy->resample(w, h);
    return copy;
}

void ImageStack::updateStateBasedOnImage(const shared_ptr<Image>& image)
{
    w = image->getW();
    h = image->getH();
    components = image->getColorComponents();
    dataType = image->getPixelDataType();
}

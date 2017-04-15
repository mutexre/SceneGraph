//
//  Image.cpp
//  SceneGraph
//
//  Created by mutexre on 08/01/16.
//  Copyright © 2016 mutexre. All rights reserved.
//

#import "SceneGraph.hpp"

using namespace SG;

Image3D::Image3D()
{}

Image3D::Image3D(const vector<string>& paths) {
    for (const string& p : paths) {
        subImages.push_back(make_shared<Image>(p));
    }
    
    w = subImages[0]->getW();
    h = subImages[0]->getH();
}

Image3D::~Image3D()
{}

Image3D::Image3D(const Image3D& image) {
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

unsigned Image3D::getW() const {
    return w;
}

unsigned Image3D::getH() const {
    return h;
}

unsigned Image3D::getD() const {
    return subImages.size();
}

ColorComponents Image3D::getColorComponents() const {
    return components;
}

PixelDataType Image3D::getPixelDataType() const {
    return dataType;
}

const char* Image3D::getData(unsigned z) const {
    return subImages[z]->getData();
}

char* Image3D::getData(unsigned z) {
    return subImages[z]->getData();
}

const shared_ptr<Image>& Image3D::operator[](unsigned z) const {
    return subImages[z];
}

void Image3D::resample(unsigned w, unsigned h) {
    for (auto& image : subImages)
        image->resample(w, h);
    
    this->w = w;
    this->h = h;
}

shared_ptr<Image3D> Image3D::getResampledImage(unsigned w, unsigned h) const {
    auto copy = shared_ptr<Image3D>(new Image3D(*this));
    copy->resample(w, h);
    return copy;
}

//
//  Texture.cpp
//  SceneGraph
//
//  Created by mutexre on 04/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Texture::Texture()
{}

Texture::Texture(Type type, PixelFormat format) {
    setType(type);
    setFormat(format);
}

Texture::~Texture()
{}

void Texture::setImage(const shared_ptr<Image>& image) {
    vector<shared_ptr<Image>> images{ image };
    setImages(images);
}

void Texture::setImage(const shared_ptr<Image3D>& image) {
    vector<shared_ptr<Image3D>> images{ image };
    setImages(images);
}

void Texture::setImage(Image& image)
{
    setImage(image.getData(),
             image.getBytesPerRow() / getNumberOfComponents(image.getColorComponents()),
             image.getH(), 1,
             image.getColorComponents(),
             image.getPixelDataType());
}

Texture::Type Texture::getType() const {
    return type;
}

void Texture::setType(Type type) {
    this->type = type;
}

PixelFormat Texture::getFormat() const {
    return format;
}

void Texture::setFormat(PixelFormat f) {
    format = f;
}

Texture::MinFilter Texture::getMinFilter() const {
    return filter.min;
}

void Texture::setMinFilter(MinFilter f) {
    filter.min = f;
}

Texture::MagFilter Texture::getMagFilter() const {
    return filter.mag;
}

void Texture::setMagFilter(MagFilter f) {
    filter.mag = f;
}

Texture::Wrap Texture::getWrapS() const {
    return wrap.s;
}

void Texture::setWrapS(Wrap w) {
    wrap.s = w;
}

Texture::Wrap Texture::getWrapT() const {
    return wrap.t;
}

void Texture::setWrapT(Wrap w) {
    wrap.t = w;
}

Texture::Wrap Texture::getWrapR() const {
    return wrap.r;
}

void Texture::setWrapR(Wrap w) {
    wrap.r = w;
}

float Texture::getMinLod() const {
    return lod.min;
}

void Texture::setMinLod(float min) {
    lod.min = min;
}

float Texture::getMaxLod() const {
    return lod.max;
}

void Texture::setMaxLod(float max) {
    lod.max = max;
}

float Texture::getBaseLevel() const {
    return lod.baseLevel;
}

void Texture::setBaseLevel(float baseLevel) {
    lod.baseLevel = baseLevel;
}

float Texture::getMaxLevel() const {
    return lod.maxLevel;
}

void Texture::setMaxLevel(float maxLevel) {
    lod.maxLevel = maxLevel;
}

vec4 Texture::getBorderColor() const {
    return borderColor;
}

void Texture::setBorderColor(vec4 c) {
    borderColor = c;
}

float Texture::getPriority() const {
    return priority;
}

void Texture::setPriority(float p) {
    priority = p;
}

//
//  Renderbuffer.cpp
//  sensee
//
//  Created by mutexre on 21/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Renderbuffer::~Renderbuffer()
{}

uvec2 Renderbuffer::getSize() const {
    return size;
}

PixelFormat Renderbuffer::getFormat() const {
    return format;
}

void Renderbuffer::setFormat(PixelFormat format) {
    this->format = format;
}

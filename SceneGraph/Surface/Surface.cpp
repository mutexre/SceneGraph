//
//  Created by mutexre on 18/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Surface::~Surface()
{}

void Surface::attach(AttachmentPoint attachment,
                     const shared_ptr<SG::Texture>& texture,
                     unsigned level,
                     unsigned cubeMapSide)
{
    attach(attachment, 0, texture, level, cubeMapSide);
}

void Surface::attach(AttachmentPoint attachment,
                     const shared_ptr<Renderbuffer>& renderbuffer)
{
    attach(attachment, 0, renderbuffer);
}

void Surface::makeActive()
{
    makeActive(Target::draw);
    makeActive(Target::read);
}

void Surface::invalidate()
{
    makeActive(Target::draw);
    makeActive(Target::read);
}

//
//  Created by mutexre on 09/11/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

#pragma mark - Color Mask

Settings::ColorMask::ColorMask(bool r, bool g, bool b, bool a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

bool Settings::ColorMask::operator==(const ColorMask& x) const {
    return r == x.r && g == x.g && b == x.b && a == x.a;
}

bool Settings::ColorMask::operator!=(const ColorMask& x) const {
    return !operator==(x);
}

#pragma mark - Settings

void Settings::apply(const Settings& s)
{
    if (s.depthTest)
        depthTest = s.depthTest;

    if (s.depthClamp)
        depthClamp = s.depthClamp;

    if (s.writeDepth)
        writeDepth = s.writeDepth;

    if (s.seamlessCubemaps)
        seamlessCubemaps = s.seamlessCubemaps;

    if (s.smoothPoints)
        smoothPoints = s.smoothPoints;

    if (s.cullFace)
        cullFace = s.cullFace;

    if (s.blend)
        blend = s.blend.value;

    if (s.viewport)
        viewport = s.viewport;

    if (s.scissor)
        scissor = s.scissor;

    if (s.colorMask)
        colorMask = s.colorMask.value;
}

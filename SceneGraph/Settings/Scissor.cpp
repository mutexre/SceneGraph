//
//  Created by mutexre on 20/01/2017.
//  Copyright © 2017 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Settings::Scissor::Scissor() : enabled(false)
{}

Settings::Scissor::Scissor(ivec4 rect) {
    enable(rect);
}

Settings::Scissor::Scissor(unsigned x, unsigned y,
                           unsigned w, unsigned h)
{
    enable(x, y, w, h);
}

void Settings::Scissor::disable() {
    enabled = false;
    rect.undefine();
}

void Settings::Scissor::enable(ivec4 r) {
    enabled = true;
    rect = r;
}

void Settings::Scissor::enable(unsigned x, unsigned y, unsigned w, unsigned h) {
    enable(ivec4(x, y, w, h));
}

bool Settings::Scissor::operator==(const Scissor& x) const {
    return enabled == x.enabled && rect == x.rect;
}

bool Settings::Scissor::operator!=(const Scissor& x) const {
    return !operator==(x);
}

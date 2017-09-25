//
//  Created by mutexre on 19/01/2017.
//  Copyright © 2017 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Settings::CullFace::CullFace() {
    disable();
}

Settings::CullFace::CullFace(Mode m) {
    enable(m);
}

void Settings::CullFace::enable(Mode m) {
    enabled.define(true);
    mode.define(m);
}

void Settings::CullFace::disable() {
    enabled.define(false);
    mode.undefine();
}

bool Settings::CullFace::operator==(const CullFace& x) const {
    return enabled == x.enabled && mode == x.mode;
}

bool Settings::CullFace::operator!=(const CullFace& x) const {
    return !operator==(x);
}

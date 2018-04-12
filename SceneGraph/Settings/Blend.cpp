//
//  Created by mutexre on 19/01/2017.
//  Copyright © 2017 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

Settings::Blend::Blend() : enabled(false)
{}

Settings::Blend::Blend(Func src, Func dst,
                       Equation eq,
                       vec4 color)
{
    enabled = true;
    separate = false;
    
    func.srcRGB = src;
    func.srcAlpha = src;
    func.dstRGB = dst;
    func.dstAlpha = dst;
    
    equation.rgb = eq;
    equation.alpha = eq;
    
    this->color = color;
}

Settings::Blend::Blend(Func srcRGB, Func srcAlpha,
                       Func dstRGB, Func dstAlpha,
                       Equation eqRGB,
                       Equation eqAlpha,
                       vec4 color)
{
    enabled = true;
    separate = true;
    
    func.srcRGB = srcRGB;
    func.srcAlpha = srcAlpha;
    func.dstRGB = dstRGB;
    func.dstAlpha = dstAlpha;
    
    equation.rgb = eqRGB;
    equation.alpha = eqAlpha;
    
    this->color = color;
}

void Settings::Blend::disable()
{
    enabled = false;
    
    func.srcRGB.undefine();
    func.srcAlpha.undefine();
    func.dstRGB.undefine();
    func.dstAlpha.undefine();
    
    equation.rgb.undefine();
    equation.alpha.undefine();
    
    color.undefine();
}

bool Settings::Blend::operator==(const Blend& x) const
{
    return enabled == x.enabled &&
           func.srcRGB == x.func.srcRGB &&
           func.srcAlpha == x.func.srcAlpha &&
           func.dstRGB == x.func.dstRGB &&
           func.dstAlpha == x.func.dstAlpha &&
           equation.rgb == x.equation.rgb &&
           equation.alpha == x.equation.alpha &&
           color == x.color;
}

bool Settings::Blend::operator!=(const Blend& x) const {
    return !operator==(x);
}

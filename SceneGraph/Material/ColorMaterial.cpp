//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

ColorMaterial::ColorMaterial(const shared_ptr<Context>& context)
 : Material(context)
{}

ColorMaterial::ColorMaterial(const shared_ptr<Context>& context,
                             const shared_ptr<Program>& program,
                             vec4 color)
 : ColorMaterial(context)
{
    setProgram(program);
    setColor(color);
}

const vec4& ColorMaterial::getColor() const {
    return color;
}

void ColorMaterial::setColor(vec4 color)
{
    this->color = color;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncColor();
    }
}

void ColorMaterial::syncColor()
{
    if (program->isUniformActive("color"))
        program->set("color", color);
    
    colorSynced = true;
}

void ColorMaterial::invalidateVariables()
{
    colorSynced = false;
}

void ColorMaterial::syncVariables()
{
    if (isProgramShared()) {
        syncColor();
    }
    else {
        if (!colorSynced)
            syncColor();
    }
}

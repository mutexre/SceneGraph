//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

SkyboxMaterial::SkyboxMaterial(const shared_ptr<Context>& context)
 : Material(context)
{}

SkyboxMaterial::SkyboxMaterial(const shared_ptr<Context>& context,
                               const shared_ptr<Program>& program,
                               const shared_ptr<Texture>& texture,
                               float lod)
 : SkyboxMaterial(context)
{
    setProgram(program);
    setTexture(texture);
    setLod(lod);
}

SkyboxMaterial& SkyboxMaterial::setTexture(const shared_ptr<Texture>& t)
{
    texture = t;
    return *this;
}

float SkyboxMaterial::getLod() const {
    return lod;
}

SkyboxMaterial& SkyboxMaterial::setLod(float lod)
{
    this->lod = lod;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncLod();
    }
    
    return *this;
}

void SkyboxMaterial::syncLod()
{
    if (program->isUniformActive("lod"))
        program->set("lod", lod);
    
    lodSynced = true;
}

void SkyboxMaterial::syncTextureSamplers()
{
    if (program->isUniformActive("texture"))
        program->set("texture", 0);
}

void SkyboxMaterial::invalidateVariables()
{
    lodSynced = false;
}

void SkyboxMaterial::syncVariables()
{
    if (isProgramShared()) {
        syncLod();
    }
    else {
        if (!lodSynced)
            syncLod();
    }
}

void SkyboxMaterial::activateTextures()
{
    if (texture)
        context->activate(0, texture);
}

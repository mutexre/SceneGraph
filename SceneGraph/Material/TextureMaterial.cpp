//
//  SkyboxMaterial.cpp
//  SceneGraph
//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

TextureMaterial::TextureMaterial(const shared_ptr<Context>& context)
 : Material(context)
{}

TextureMaterial::TextureMaterial(const shared_ptr<Context>& context,
                                 const shared_ptr<Program>& program,
                                 const shared_ptr<Texture>& texture,
                                 mat3 uvTransform)
 : TextureMaterial(context)
{
    setTexture(texture);
    setProgram(program);
    setUvTransform(uvTransform);
}

shared_ptr<Texture>& TextureMaterial::getTexture() {
    return texture;
}

TextureMaterial& TextureMaterial::setTexture(const shared_ptr<Texture>& t)
{
    texture = t;
    return *this;
}

mat3 TextureMaterial::getUvTransform() const {
    return uvTransform;
}

TextureMaterial& TextureMaterial::setUvTransform(mat3 m)
{
    uvTransform = m;

    if (!isProgramShared())
    {
        bindProgram();
        syncUvTransform();
    }
    
    return *this;
}

void TextureMaterial::syncUvTransform()
{
    if (program->isUniformActive("uvTransform"))
        program->set("uvTransform", uvTransform);
    
    uvTransformSynced = true;
}

void TextureMaterial::syncTextureSamplers()
{
    if (program->isUniformActive("texture"))
        program->set("texture", 0);
}

void TextureMaterial::invalidateVariables()
{
    uvTransformSynced = false;
}

void TextureMaterial::syncVariables()
{
    if (isProgramShared()) {
        syncUvTransform();
    }
    else {
        if (!uvTransformSynced)
            syncUvTransform();
    }
}

void TextureMaterial::activateTextures()
{
    if (texture)
        context->activate(0, texture);
}

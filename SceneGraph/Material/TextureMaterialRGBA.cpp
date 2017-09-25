//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

TextureMaterialRGBA::TextureMaterialRGBA(const shared_ptr<Context>& context)
 : Material(context)
{}

TextureMaterialRGBA::TextureMaterialRGBA(const shared_ptr<Context>& context,
                                         const shared_ptr<Program>& program,
                                         const shared_ptr<Texture>& color,
                                         const shared_ptr<Texture>& alpha,
                                         mat3 colorUvTransform,
                                         mat3 alphaUvTransform)
 : TextureMaterialRGBA(context)
{
    setProgram(program);
    setColorTexture(color);
    setAlphaTexture(alpha);
    setColorUvTransform(colorUvTransform);
    setAlphaUvTransform(alphaUvTransform);
}

shared_ptr<Texture>&
TextureMaterialRGBA::getColorTexture()
{
    return textures.color;
}

TextureMaterialRGBA&
TextureMaterialRGBA::setColorTexture(const shared_ptr<Texture>& texture)
{
    textures.color = texture;
    return *this;
}

shared_ptr<Texture>&
TextureMaterialRGBA::getAlphaTexture()
{
    return textures.alpha;
}

TextureMaterialRGBA&
TextureMaterialRGBA::setAlphaTexture(const shared_ptr<Texture>& texture)
{
    textures.alpha = texture;
    return *this;
}

mat3 TextureMaterialRGBA::getColorUvTransform() const {
    return uvTransform.color;
}

TextureMaterialRGBA& TextureMaterialRGBA::setColorUvTransform(mat3 m)
{
    uvTransform.color = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncColorUvTransform();
    }
    
    return *this;
}

void TextureMaterialRGBA::syncColorUvTransform()
{
    if (program->isUniformActive("uvTransformColor"))
        program->set("uvTransformColor", uvTransform.color);
    
    sync.uvTransform.color = true;
}

mat3 TextureMaterialRGBA::getAlphaUvTransform() const {
    return uvTransform.alpha;
}

TextureMaterialRGBA& TextureMaterialRGBA::setAlphaUvTransform(mat3 m)
{
    uvTransform.alpha = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncAlphaUvTransform();
    }
    
    return *this;
}

void TextureMaterialRGBA::syncAlphaUvTransform()
{
    if (program->isUniformActive("uvTransformAlpha"))
        program->set("uvTransformAlpha", uvTransform.alpha);
    
    sync.uvTransform.alpha = true;
}

Option<float> TextureMaterialRGBA::getFixedAlpha() const {
    return fixedAlpha;
}

TextureMaterialRGBA& TextureMaterialRGBA::setFixedAlpha(const Option<float>& value)
{
    fixedAlpha = value;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncUseFixedAlpha();
        syncFixedAlphaValue();
    }
    
    return *this;
}

void TextureMaterialRGBA::syncUseFixedAlpha()
{
    if (program->isUniformActive("useFixedAlpha"))
        program->set("useFixedAlpha", fixedAlpha.defined);
    
    sync.fixedAlpha.use = true;
}

void TextureMaterialRGBA::syncFixedAlphaValue()
{
    if (program->isUniformActive("fixedAlpha"))
        program->set("fixedAlpha", fixedAlpha.value);
    
    sync.fixedAlpha.value = true;
}

TextureMaterialRGBA& TextureMaterialRGBA::disableFixedAlpha()
{
    fixedAlpha.undefine();
    
    if (!isProgramShared())
    {
        bindProgram();
        syncUseFixedAlpha();
    }
    
    return *this;
}

void TextureMaterialRGBA::invalidateVariables()
{
    sync.uvTransform.color = false;
    sync.uvTransform.alpha = false;
    sync.fixedAlpha.use = false;
    sync.fixedAlpha.value = false;
}

void TextureMaterialRGBA::syncVariables()
{
    if (isProgramShared())
    {
        syncColorUvTransform();
        syncAlphaUvTransform();
        syncUseFixedAlpha();
        syncFixedAlphaValue();
    }
    else
    {
        if (!sync.uvTransform.color)
            syncColorUvTransform();
        
        if (!sync.uvTransform.alpha)
            syncAlphaUvTransform();
        
        if (!sync.fixedAlpha.use)
            syncUseFixedAlpha();
        
        if (!sync.fixedAlpha.value)
            syncFixedAlphaValue();
    }
}

void TextureMaterialRGBA::syncTextureSamplers()
{
    if (program->isUniformActive("textureColor"))
        program->set("textureColor", 0);
    
    if (program->isUniformActive("textureAlpha"))
        program->set("textureAlpha", 1);
}

void TextureMaterialRGBA::activateTextures()
{
    context->activate(0, textures.color);
    context->activate(1, textures.alpha);
}

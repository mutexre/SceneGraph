//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

TextureMaterialYUVA::TextureMaterialYUVA(const shared_ptr<Context>& context)
 : Material(context)
{}

TextureMaterialYUVA::TextureMaterialYUVA(const shared_ptr<Context>& context,
                                         const shared_ptr<Program>& program,
                                         const shared_ptr<Texture>& luma,
                                         const shared_ptr<Texture>& chroma,
                                         const shared_ptr<Texture>& alpha,
                                         const mat3& colorConversion,
                                         const mat3& lumaUvTransform,
                                         const mat3& chromaUvTransform,
                                         const mat3& alphaUvTransform)
 : TextureMaterialYUVA(context)
{
    setProgram(program);
    
    setLumaTexture(luma);
    setChromaTexture(chroma);
    setAlphaTexture(alpha);
    
    setLumaUvTransform(lumaUvTransform);
    setChromaUvTransform(chromaUvTransform);
    setAlphaUvTransform(alphaUvTransform);
    
    setColorConversion(colorConversion);
}

shared_ptr<Texture>& TextureMaterialYUVA::getLumaTexture() {
    return textures.luma;
}

TextureMaterialYUVA& TextureMaterialYUVA::setLumaTexture(const shared_ptr<Texture>& texture) {
    textures.luma = texture;
    return *this;
}

shared_ptr<Texture>& TextureMaterialYUVA::getChromaTexture() {
    return textures.chroma;
}

TextureMaterialYUVA& TextureMaterialYUVA::setChromaTexture(const shared_ptr<Texture>& texture) {
    textures.chroma = texture;
    return *this;
}

shared_ptr<Texture>& TextureMaterialYUVA::getAlphaTexture() {
    return textures.alpha;
}

TextureMaterialYUVA& TextureMaterialYUVA::setAlphaTexture(const shared_ptr<Texture>& texture) {
    textures.alpha = texture;
    return *this;
}

const mat3& TextureMaterialYUVA::getColorConversion() const {
    return colorConversion;
}

TextureMaterialYUVA& TextureMaterialYUVA::setColorConversion(const mat3& m)
{
    colorConversion = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncColorConversion();
    }
    
    return *this;
}

void TextureMaterialYUVA::syncColorConversion()
{
    if (program->isUniformActive("colorConversion"))
        program->set("colorConversion", colorConversion);
    
    sync.colorConversion = true;
}

const mat3& TextureMaterialYUVA::getLumaUvTransform() const {
    return uvTransform.luma;
}

TextureMaterialYUVA& TextureMaterialYUVA::setLumaUvTransform(const mat3& m)
{
    uvTransform.luma = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncLumaUvTransform();
    }
    
    return *this;
}

void TextureMaterialYUVA::syncLumaUvTransform()
{
    if (program->isUniformActive("uvTransform.luma"))
        program->set("uvTransform.luma", uvTransform.luma);
    
    sync.uvTransform.luma = true;
}

const mat3& TextureMaterialYUVA::getChromaUvTransform() const {
    return uvTransform.chroma;
}

TextureMaterialYUVA& TextureMaterialYUVA::setChromaUvTransform(const mat3& m)
{
    uvTransform.chroma = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncChromaUvTransform();
    }
    
    return *this;
}

void TextureMaterialYUVA::syncChromaUvTransform()
{
    if (program->isUniformActive("uvTransform.chroma"))
        program->set("uvTransform.chroma", uvTransform.chroma);
    
    sync.uvTransform.chroma = true;
}

const mat3& TextureMaterialYUVA::getAlphaUvTransform() const {
    return uvTransform.alpha;
}

TextureMaterialYUVA& TextureMaterialYUVA::setAlphaUvTransform(const mat3& m)
{
    uvTransform.alpha = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncAlphaUvTransform();
    }
    
    return *this;
}

void TextureMaterialYUVA::syncAlphaUvTransform()
{
    if (program->isUniformActive("uvTransformAlpha"))
        program->set("uvTransformAlpha", uvTransform.alpha);
    
    sync.uvTransform.alpha = true;
}

void TextureMaterialYUVA::syncTextureSamplers()
{
    if (program->isUniformActive("textures.luma"))
        program->set("textures.luma", 0);
    
    if (program->isUniformActive("textures.chroma"))
        program->set("textures.chroma", 1);
    
    if (program->isUniformActive("textures.alpha"))
        program->set("textures.alpha", 2);
}

void TextureMaterialYUVA::invalidateVariables()
{
    sync.colorConversion = false;
    sync.uvTransform.luma = false;
    sync.uvTransform.chroma = false;
    sync.uvTransform.alpha = false;
}

void TextureMaterialYUVA::syncVariables()
{
    if (isProgramShared())
    {
        syncColorConversion();
        syncLumaUvTransform();
        syncChromaUvTransform();
        syncAlphaUvTransform();
    }
    else
    {
        if (!sync.colorConversion)
            syncColorConversion();
        
        if (!sync.uvTransform.luma)
            syncLumaUvTransform();
        
        if (!sync.uvTransform.chroma)
            syncChromaUvTransform();
        
        if (!sync.uvTransform.alpha)
            syncAlphaUvTransform();
    }
}

void TextureMaterialYUVA::activateTextures()
{
    context->activate(0, textures.luma);
    context->activate(1, textures.chroma);
    context->activate(2, textures.alpha);
}

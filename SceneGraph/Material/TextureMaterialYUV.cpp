//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

TextureMaterialYUV::TextureMaterialYUV(const shared_ptr<Context>& context)
 : Material(context)
{}

TextureMaterialYUV::TextureMaterialYUV(const shared_ptr<Context>& context,
                                       const shared_ptr<Program>& program,
                                       const shared_ptr<Texture>& y,
                                       const shared_ptr<Texture>& uv,
                                       const mat3& colorConversion,
                                       const mat3& yTransform,
                                       const mat3& uvTransform)
 : TextureMaterialYUV(context)
{
    setMode(Mode::uv);
    setProgram(program);
    
    setY(y);
    setUV(uv);
    
    setUvTransformY(yTransform);
    setUvTransformUV(uvTransform);
    
    setColorConversion(colorConversion);
}

TextureMaterialYUV::TextureMaterialYUV(const shared_ptr<Context>& context,
                                       const shared_ptr<Program>& program,
                                       const shared_ptr<Texture>& y,
                                       const shared_ptr<Texture>& u,
                                       const shared_ptr<Texture>& v,
                                       const mat3& colorConversion,
                                       const mat3& yTransform,
                                       const mat3& uTransform,
                                       const mat3& vTransform)
 : TextureMaterialYUV(context)
{
    setMode(Mode::u_v);
    setProgram(program);
    
    setY(y);
    setU(u);
    setV(v);
    
    setUvTransformY(yTransform);
    setUvTransformU(uTransform);
    setUvTransformV(vTransform);
    
    setColorConversion(colorConversion);
}

TextureMaterialYUV::Mode TextureMaterialYUV::getMode() const {
    return mode;
}

void TextureMaterialYUV::setMode(Mode mode)
{
    this->mode = mode;
    bindProgram();
    syncTextureSamplers();
}

shared_ptr<Texture>& TextureMaterialYUV::getY() {
    return textures.y;
}

TextureMaterialYUV& TextureMaterialYUV::setY(const shared_ptr<Texture>& texture) {
    textures.y = texture;
    return *this;
}

shared_ptr<Texture>& TextureMaterialYUV::getU() {
    return textures.u;
}

TextureMaterialYUV& TextureMaterialYUV::setU(const shared_ptr<Texture>& texture) {
    textures.u = texture;
    return *this;
}

shared_ptr<Texture>& TextureMaterialYUV::getV() {
    return textures.v;
}

TextureMaterialYUV& TextureMaterialYUV::setV(const shared_ptr<Texture>& texture) {
    textures.v = texture;
    return *this;
}


shared_ptr<Texture>& TextureMaterialYUV::getUV() {
    return textures.uv;
}

TextureMaterialYUV& TextureMaterialYUV::setUV(const shared_ptr<Texture>& texture) {
    textures.uv = texture;
    return *this;
}

const mat3& TextureMaterialYUV::getColorConversion() const {
    return colorConversion;
}

TextureMaterialYUV& TextureMaterialYUV::setColorConversion(const mat3& m)
{
    colorConversion = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncColorConversion();
    }
    
    return *this;
}

void TextureMaterialYUV::syncColorConversion()
{
    if (program->isUniformActive("colorConversion"))
        program->set("colorConversion", colorConversion);
    
    sync.colorConversion = true;
}

const mat3& TextureMaterialYUV::getUvTransformY() const {
    return uvTransform.y;
}

TextureMaterialYUV& TextureMaterialYUV::setUvTransformY(const mat3& m)
{
    uvTransform.y = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncUvTransformY();
    }
    
    return *this;
}

void TextureMaterialYUV::syncUvTransformY()
{
    if (program->isUniformActive("uvTransformY"))
        program->set("uvTransformY", uvTransform.y);
    
    sync.uvTransform.y = true;
}

const mat3& TextureMaterialYUV::getUvTransformU() const {
    return uvTransform.u;
}

TextureMaterialYUV& TextureMaterialYUV::setUvTransformU(const mat3& m)
{
    uvTransform.u = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncUvTransformU();
    }
    
    return *this;
}

void TextureMaterialYUV::syncUvTransformU()
{
    if (program->isUniformActive("uvTransformU"))
        program->set("uvTransformU", uvTransform.u);
    
    sync.uvTransform.u = true;
}

const mat3& TextureMaterialYUV::getUvTransformV() const {
    return uvTransform.v;
}

TextureMaterialYUV& TextureMaterialYUV::setUvTransformV(const mat3& m)
{
    uvTransform.v = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncUvTransformV();
    }
    
    return *this;
}

void TextureMaterialYUV::syncUvTransformV()
{
    if (program->isUniformActive("uvTransformV"))
        program->set("uvTransformV", uvTransform.v);
    
    sync.uvTransform.v = true;
}

const mat3& TextureMaterialYUV::getUvTransformUV() const {
    return uvTransform.uv;
}

TextureMaterialYUV& TextureMaterialYUV::setUvTransformUV(const mat3& m)
{
    uvTransform.uv = m;
    
    if (!isProgramShared())
    {
        bindProgram();
        syncUvTransformUV();
    }
    
    return *this;
}

void TextureMaterialYUV::syncUvTransformUV()
{
    if (program->isUniformActive("uvTransformUV"))
        program->set("uvTransformUV", uvTransform.uv);
    
    sync.uvTransform.uv = true;
}

void TextureMaterialYUV::syncTextureSamplers()
{
    if (program->isUniformActive("textureY"))
        program->set("textureY", 0);
    
    if (mode == Mode::uv)
    {
        if (program->isUniformActive("textureUV"))
            program->set("textureUV", 1);
    }
    else
    {
        if (program->isUniformActive("textureU"))
            program->set("textureU", 1);
        
        if (program->isUniformActive("textureV"))
            program->set("textureV", 2);
    }
}

void TextureMaterialYUV::invalidateVariables()
{
    sync.colorConversion = false;
    sync.uvTransform.y = false;
    sync.uvTransform.u = false;
    sync.uvTransform.v = false;
    sync.uvTransform.uv = false;
}

void TextureMaterialYUV::syncVariables()
{
    if (isProgramShared())
    {
        syncColorConversion();
        syncUvTransformY();
        
        if (mode == Mode::uv) {
            syncUvTransformUV();
        }
        else
        {
            syncUvTransformU();
            syncUvTransformV();
        }
    }
    else
    {
        if (!sync.colorConversion)
            syncColorConversion();
        
        if (!sync.uvTransform.y)
            syncUvTransformY();
        
        if (mode == Mode::uv)
        {
            if (!sync.uvTransform.uv)
                syncUvTransformUV();
        }
        else
        {
            if (!sync.uvTransform.u)
                syncUvTransformU();
            
            if (!sync.uvTransform.v)
                syncUvTransformV();
        }
    }
}

void TextureMaterialYUV::activateTextures()
{
    context->activate(0, textures.y);
    
    if (mode == Mode::uv) {
        context->activate(1, textures.uv);
    }
    else
    {
        context->activate(1, textures.u);
        context->activate(2, textures.v);
    }
}

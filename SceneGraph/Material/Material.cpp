//
//  Material.cpp
//  LookseryTestTask
//
//  Created by mutexre on 14/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Material::Material(const shared_ptr<Context>& context) {
    setContext(context);
}

Material::~Material()
{}

void Material::bindProgram() {
    context->activate(program);
}

const shared_ptr<Context>& Material::getContext() const {
    return context;
}

void Material::setContext(const shared_ptr<Context>& c) {
    context = c;
}

const shared_ptr<Program>& Material::getProgram() const {
    return program;
}

void Material::setProgram(const shared_ptr<Program>& p)
{
    if (program != p)
    {
        p->adjustUseCount(+1);
        
        if (program)
            program->adjustUseCount(-1);
        
        program = p;
        
        if (program)
        {
            bindProgram();
            syncTextureSamplers();
            invalidateVariables();
        }
    }
}

bool Material::isProgramShared() const
{
    if (program->getUseCount() > 1)
        return true;

    return program->getUseCount() > 1;
}

void Material::invalidateVariables()
{}

void Material::syncTextureSamplers()
{}

void Material::syncVariables()
{}

void Material::activateTextures()
{}

void Material::bind()
{
    bindProgram();
    syncVariables();
    activateTextures();
}

bool Material::isVertexAttributeActive(const string& name) {
    return program->isVertexAttributeActive(name);
}

bool Material::isParameterActive(const string& name) {
    return program->isUniformActive(name);
}

void Material::set(const string& var, float value) {
    program->set(var, value);
}

void Material::set(const string& var, float v0, float v1) {
    program->set(var, v0, v1);
}

void Material::set(const string& var, float v0, float v1, float v2) {
    program->set(var, v0, v1, v2);
}

void Material::set(const string& var, float v0, float v1, float v2, float v3) {
    program->set(var, v0, v1, v2, v3);
}

void Material::set(const string& var, unsigned size, unsigned count, const float* data) {
    program->set(var, size, count, data);
}

void Material::set(const string& var, int value) {
    program->set(var, value);
}

void Material::set(const string& var, int v0, int v1) {
    program->set(var, v0, v1);
}

void Material::set(const string& var, int v0, int v1, int v2) {
    program->set(var, v0, v1, v2);
}

void Material::set(const string& var, int v0, int v1, int v2, int v3) {
    program->set(var, v0, v1, v2, v3);
}

void Material::set(const string& var, unsigned size, unsigned count, const int* data) {
    program->set(var, size, count, data);
}

void Material::set(const string& var, unsigned value) {
    program->set(var, value);
}

void Material::set(const string& var, unsigned v0, unsigned v1) {
    program->set(var, v0, v1);
}

void Material::set(const string& var, unsigned v0, unsigned v1, unsigned v2) {
    program->set(var, v0, v1, v2);
}

void Material::set(const string& var, unsigned v0, unsigned v1, unsigned v2, unsigned v3) {
    program->set(var, v0, v1, v2, v3);
}

void Material::set(const string& var, unsigned size, unsigned count, const unsigned* data) {
    program->set(var, size, count, data);
}

void Material::set(const string& var, const mat2& m, bool transpose) {
    program->set(var, m, transpose);
}

void Material::set(const string& var, const mat3& m, bool transpose) {
    program->set(var, m, transpose);
}

void Material::set(const string& var, const mat4& m, bool transpose) {
    program->set(var, m, transpose);
}

void Material::set(const string& var, const mat2x3& m, bool transpose) {
    program->set(var, m, transpose);
}

void Material::set(const string& var, const mat3x2& m, bool transpose) {
    program->set(var, m, transpose);
}

void Material::set(const string& var, const mat2x4& m, bool transpose) {
    program->set(var, m, transpose);
}

void Material::set(const string& var, const mat4x2& m, bool transpose) {
    program->set(var, m, transpose);
}

void Material::set(const string& var, const mat3x4& m, bool transpose) {
    program->set(var, m, transpose);
}

void Material::set(const string& var, const mat4x3& m, bool transpose) {
    program->set(var, m, transpose);
}

void Material::set(const string& var, unsigned count, const mat2* m, bool transpose) {
    program->set(var, count, m, transpose);
}

void Material::set(const string& var, unsigned count, const mat3* m, bool transpose) {
    program->set(var, count, m, transpose);
}

void Material::set(const string& var, unsigned count, const mat4* m, bool transpose) {
    program->set(var, count, m, transpose);
}

void Material::set(const string& var, unsigned count, const mat2x3* m, bool transpose) {
    program->set(var, count, m, transpose);
}

void Material::set(const string& var, unsigned count, const mat3x2* m, bool transpose) {
    program->set(var, count, m, transpose);
}

void Material::set(const string& var, unsigned count, const mat2x4* m, bool transpose) {
    program->set(var, count, m, transpose);
}

void Material::set(const string& var, unsigned count, const mat4x2* m, bool transpose) {
    program->set(var, count, m, transpose);
}

void Material::set(const string& var, unsigned count, const mat3x4* m, bool transpose) {
    program->set(var, count, m, transpose);
}

void Material::set(const string& var, unsigned count, const mat4x3* m, bool transpose) {
    program->set(var, count, m, transpose);
}

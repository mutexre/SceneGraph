//
//  Created by mutexre on 26/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Program::~Program()
{}

int Program::getUseCount() const {
    return useCount;
}

void Program::adjustUseCount(int amount) {
    useCount += amount;
}

shared_ptr<Program::Binary> Program::getBinary()
{
    if (!binary)
        loadBinary();
    
    return binary;
}

void Program::set(const string& var, float value) {
    set(var, 1, 1, &value);
}

void Program::set(const string& var, float v0, float v1) {
    float val[] = { v0, v1 };
    set(var, 2, 1, val);
}

void Program::set(const string& var, float v0, float v1, float v2) {
    float val[] = { v0, v1, v2 };
    set(var, 3, 1, val);
}

void Program::set(const string& var, float v0, float v1, float v2, float v3) {
    float val[] = { v0, v1, v2, v3 };
    set(var, 4, 1, val);
}

void Program::set(const string& var, const vec2& value) {
    set(var, value.x, value.y);
}

void Program::set(const string& var, const vec3& value) {
    set(var, value.x, value.y, value.z);
}

void Program::set(const string& var, const vec4& value) {
    set(var, value.x, value.y, value.z, value.w);
}

void Program::set(const string& var, int value) {
    set(var, 1, 1, &value);
}

void Program::set(const string& var, int v0, int v1) {
    int val[] = { v0, v1 };
    set(var, 2, 1, val);
}

void Program::set(const string& var, int v0, int v1, int v2) {
    int val[] = { v0, v1, v2 };
    set(var, 3, 1, val);
}

void Program::set(const string& var, int v0, int v1, int v2, int v3) {
    int val[] = { v0, v1, v2, v3 };
    set(var, 4, 1, val);
}

void Program::set(const string& var, const ivec2& value) {
    set(var, value.x, value.y);
}

void Program::set(const string& var, const ivec3& value) {
    set(var, value.x, value.y, value.z);
}

void Program::set(const string& var, const ivec4& value) {
    set(var, value.x, value.y, value.z, value.w);
}

void Program::set(const string& var, unsigned value) {
    set(var, 1, 1, &value);
}

void Program::set(const string& var, unsigned v0, unsigned v1) {
    unsigned val[] = { v0, v1 };
    set(var, 2, 1, val);
}

void Program::set(const string& var, unsigned v0, unsigned v1, unsigned v2) {
    unsigned val[] = { v0, v1, v2 };
    set(var, 3, 1, val);
}

void Program::set(const string& var, unsigned v0, unsigned v1, unsigned v2, unsigned v3) {
    unsigned val[] = { v0, v1, v2, v3 };
    set(var, 4, 1, val);
}

void Program::set(const string& var, const uvec2& value) {
    set(var, value.x, value.y);
}

void Program::set(const string& var, const uvec3& value) {
    set(var, value.x, value.y, value.z);
}

void Program::set(const string& var, const uvec4& value) {
    set(var, value.x, value.y, value.z, value.w);
}

void Program::set(const string& var, const mat2& m, bool transpose) {
    set(var, 1, &m, transpose);
}

void Program::set(const string& var, const mat3& m, bool transpose) {
    set(var, 1, &m, transpose);
}

void Program::set(const string& var, const mat4& m, bool transpose) {
    set(var, 1, &m, transpose);
}

void Program::set(const string& var, const mat2x3& m, bool transpose) {
    set(var, 1, &m, transpose);
}

void Program::set(const string& var, const mat3x2& m, bool transpose) {
    set(var, 1, &m, transpose);
}

void Program::set(const string& var, const mat2x4& m, bool transpose) {
    set(var, 1, &m, transpose);
}

void Program::set(const string& var, const mat4x2& m, bool transpose) {
    set(var, 1, &m, transpose);
}

void Program::set(const string& var, const mat3x4& m, bool transpose) {
    set(var, 1, &m, transpose);
}

void Program::set(const string& var, const mat4x3& m, bool transpose) {
    set(var, 1, &m, transpose);
}

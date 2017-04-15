//
//  Light.cpp
//  SceneGraph
//
//  Created by mutexre on 14/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Light::Light() : enabled(false)
{}

Light::Light(const string& name) : Node(Node::Type::light, name)
{}

bool Light::isEnabled() const {
    return enabled;
}

Light& Light::setEnabled(bool enabled) {
    this->enabled = enabled;
    return *this;
}

Light::Type Light::getType() const {
    return type;
}

Light& Light::setType(Type type) {
    this->type = type;
    return *this;
}

unsigned Light::getGroup() const {
    return group;
}

Light& Light::setGroup(unsigned g) {
    group = g;
    return *this;
}

vec3 Light::getAmbient() const {
    return ambient;
}

Light& Light::setAmbient(vec3 c) {
    ambient = c;
    return *this;
}

Light& Light::setAmbient(float r, float g, float b) {
    ambient.r = r;
    ambient.g = g;
    ambient.b = b;
    return *this;
}

Light& Light::setAmbient(float c) {
    setAmbient(c, c, c);
    return *this;
}

vec3 Light::getDiffuse() const {
    return diffuse;
}

Light& Light::setDiffuse(vec3 c) {
    diffuse = c;
    return *this;
}

Light& Light::setDiffuse(float r, float g, float b) {
    diffuse.r = r;
    diffuse.g = g;
    diffuse.b = b;
    return *this;
}

Light& Light::setDiffuse(float c) {
    setDiffuse(c, c, c);
    return *this;
}

vec3 Light::getSpecular() const {
    return specular;
}

Light& Light::setSpecular(vec3 c) {
    specular = c;
    return *this;
}

Light& Light::setSpecular(float r, float g, float b) {
    specular.r = r;
    specular.g = g;
    specular.b = b;
    return *this;
}

Light& Light::setSpecular(float c) {
    setSpecular(c, c, c);
    return *this;
}

vec3 Light::getDirection() const {
    return direction;
}

Light& Light::setDirection(vec3 d) {
    direction = d;
    return *this;
}

Light& Light::setDirection(float x, float y, float z) {
    direction.x = x;
    direction.y = y;
    direction.z = z;
    return *this;
}

Light& Light::setDirection(float x) {
    setDirection(x, x, x);
    return *this;
}

float Light::getAttenuation(unsigned i) const {
    return attenuation[i];
}

Light& Light::setAttenuation(unsigned i, float value) {
    attenuation[i] = value;
    return *this;
}

Light& Light::setAttenuation(float constant, float linear, float quadratic) {
    attenuation[0] = constant;
    attenuation[1] = linear;
    attenuation[2] = quadratic;
    return *this;
}

void Light::setOnGPU(int index, const shared_ptr<Program>& program, const vec3& position, const vec3& direction) {
    string prefix = "lights[" + to_string(index) + "].";

    if (program->isUniformActive(prefix + "enabled"))
    {
        program->set(prefix + "enabled", enabled ? 1 : 0);
        if (enabled) {
            program->set(prefix + "type", unsigned(type));

            program->set(prefix + "ambient", 3, 1, (const float*)&ambient);
            program->set(prefix + "diffuse", 3, 1, (const float*)&diffuse);
            program->set(prefix + "specular", 3, 1, (const float*)&specular);

            program->set(prefix + "position", position[0], position[1], position[2]);
            program->set(prefix + "direction", 3, 1, (const float*)&direction);
            
            program->set(prefix + "spotExponent", spot.exponent);
            program->set(prefix + "spotCutoff", spot.cutoff);
            program->set(prefix + "spotCosCutoff", spot.cosCutoff);

            program->set(prefix + "constantAttenuation", attenuation[0]);
            program->set(prefix + "linearAttenuation", attenuation[1]);
            program->set(prefix + "quadraticAttenuation", attenuation[2]);
        }
    }
}

//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

PhongMaterial::PhongMaterial(const shared_ptr<Context>& context) : Material(context)
{}

PhongMaterial::ShadingModel PhongMaterial::getMode() const {
    return mode;
}

PhongMaterial& PhongMaterial::setMode(ShadingModel mode) {
    this->mode = mode;
    return *this;
}

vec3 PhongMaterial::getEmissive() const {
    return emissive;
}

PhongMaterial& PhongMaterial::setEmissive(vec3 rgb) {
    emissive = rgb;
    return *this;
}

PhongMaterial& PhongMaterial::setEmissive(float r, float g, float b) {
    emissive.r = r;
    emissive.g = g;
    emissive.b = b;
    return *this;
}

PhongMaterial& PhongMaterial::setEmissive(float c) {
    setEmissive(c, c, c);
    return *this;
}

vec3 PhongMaterial::getAmbientReflectance() const {
    return reflectance.ambient;
}

PhongMaterial& PhongMaterial::setAmbient(vec3 rgb) {
    reflectance.ambient = rgb;
    return *this;
}

PhongMaterial& PhongMaterial::setAmbient(float r, float g, float b) {
    reflectance.ambient[0] = r;
    reflectance.ambient[1] = g;
    reflectance.ambient[2] = b;
    return *this;
}

PhongMaterial& PhongMaterial::setAmbient(float c) {
    setAmbient(c, c, c);
    return *this;
}

vec3 PhongMaterial::getDiffuseReflectance() const {
    return reflectance.diffuse;
}

PhongMaterial& PhongMaterial::setDiffuse(vec3 rgb) {
    reflectance.diffuse = rgb;
    return *this;
}

PhongMaterial& PhongMaterial::setDiffuse(float r, float g, float b) {
    reflectance.diffuse[0] = r;
    reflectance.diffuse[1] = g;
    reflectance.diffuse[2] = b;
    return *this;
}

PhongMaterial& PhongMaterial::setDiffuse(float c) {
    setDiffuse(c, c, c);
    return *this;
}

vec3 PhongMaterial::getSpecularReflectance() const {
    return reflectance.specular;
}

PhongMaterial& PhongMaterial::setSpecular(vec3 rgb) {
    reflectance.specular = rgb;
    return *this;
}

PhongMaterial& PhongMaterial::setSpecular(float r, float g, float b) {
    reflectance.specular[0] = r;
    reflectance.specular[1] = g;
    reflectance.specular[2] = b;
    return *this;
}

PhongMaterial& PhongMaterial::setSpecular(float c) {
    setSpecular(c, c, c);
    return *this;
}

float PhongMaterial::getOpacity() const {
    return opacity;
}

PhongMaterial& PhongMaterial::setOpacity(float value) {
    opacity = value;
    return *this;
}

float PhongMaterial::getShininess() const {
    return shininess;
}

PhongMaterial& PhongMaterial::setShininess(float value) {
    shininess = value;
    return *this;
}

float PhongMaterial::getReflectivity() const {
    return reflectivity;
}

PhongMaterial& PhongMaterial::setReflectivity(float value) {
    reflectivity = value;
    return *this;
}

bool PhongMaterial::getDoubleSided() const {
    return doubleSided;
}

PhongMaterial& PhongMaterial::setDoubleSided(bool d)
{
    doubleSided = d;
    
    if (!isProgramShared()) {
        Material::bind();
        program->set("material.doubleSided", doubleSided ? 1 : 0);
    }
    
    return *this;
}

#pragma mark Textures

shared_ptr<Texture> PhongMaterial::getDiffuseTexture() const {
    return textures.diffuse;
}

PhongMaterial& PhongMaterial::setDiffuseTexture(const shared_ptr<Texture>& texture) {
    textures.diffuse = texture;
    return *this;
}

shared_ptr<Texture> PhongMaterial::getBumpTexture() const {
    return textures.bump;
}

PhongMaterial& PhongMaterial::setBumpTexture(const shared_ptr<Texture>& texture) {
    textures.bump = texture;
    return *this;
}

shared_ptr<Texture> PhongMaterial::getSkyboxTexture() const {
    return textures.skybox;
}

PhongMaterial& PhongMaterial::setSkyboxTexture(const shared_ptr<Texture>& texture) {
    textures.skybox = texture;
    return *this;
}

shared_ptr<Texture> PhongMaterial::getAmbienceTexture() const {
    return textures.ambience;
}

PhongMaterial& PhongMaterial::setAmbienceTexture(const shared_ptr<Texture>& texture) {
    textures.ambience = texture;
    return *this;
}

#pragma mark Skybox Ambience

bool PhongMaterial::isSkyboxAmbienceMapEnabled() const {
    return skyboxAmbience.enabled;
}

PhongMaterial& PhongMaterial::enableSkyboxAmbienceMap(bool enable) {
    skyboxAmbience.enabled = enable;
    return *this;
}

PhongMaterial& PhongMaterial::disableSkyboxAmbienceMap() {
    skyboxAmbience.enabled = false;
    return *this;
}

float PhongMaterial::getSkyboxAmbienceLod() const {
    return skyboxAmbience.lod;
}

PhongMaterial& PhongMaterial::setSkyboxAmbienceLod(float lod) {
    skyboxAmbience.lod = lod;
    return *this;
}

float PhongMaterial::getSkyboxAmbienceIntensity() const {
    return skyboxAmbience.intensity;
}

PhongMaterial& PhongMaterial::setSkyboxAmbienceIntensity(float intensity) {
    skyboxAmbience.intensity = intensity;
    return *this;
}

#pragma mark Ambience

bool PhongMaterial::isAmbienceMapEnabled() const {
    return ambience.enabled;
}

PhongMaterial& PhongMaterial::enableAmbienceMap(bool enable) {
    ambience.enabled = enable;
    return *this;
}

PhongMaterial& PhongMaterial::disableAmbienceMap() {
    ambience.enabled = false;
    return *this;
}

float PhongMaterial::getAmbienceLod() const {
    return ambience.lod;
}

PhongMaterial& PhongMaterial::setAmbienceLod(float lod) {
    ambience.lod = lod;
    return *this;
}

float PhongMaterial::getAmbienceIntensity() const {
    return ambience.intensity;
}

PhongMaterial& PhongMaterial::setAmbienceIntensity(float intensity) {
    ambience.intensity = intensity;
    return *this;
}

void PhongMaterial::bind()
{
    Material::bind();

    if (isProgramShared())
    {
        string prefix = "material.";
        
        program->set(prefix + "doubleSided", doubleSided ? 1 : 0);
        
        program->set(prefix + "opacity", opacity);
        program->set(prefix + "shininess", shininess);
        program->set(prefix + "reflectivity", reflectivity);
        
        program->set(prefix + "emissive", 3, 1, (const float*)&emissive);
        program->set(prefix + "ambient", 3, 1, (const float*)&reflectance.ambient);
        program->set(prefix + "diffuse", 3, 1, (const float*)&reflectance.diffuse);
        program->set(prefix + "specular", 3, 1, (const float*)&reflectance.specular);

        program->set(prefix + "diffuseMap.texture", 0);
        program->set(prefix + "bumpMap.texture", 1);
        program->set("skybox.texture", 2);
        program->set("skyboxAmbience.texture", 2);
        program->set("ambience.texture", 3);

        if (textures.diffuse) {
            program->set(prefix + "diffuseMap.enabled", 1);
            context->activate(0, textures.diffuse);
        }
        else
            program->set(prefix + "diffuseMap.enabled", 0);

        if (textures.bump) {
            program->set(prefix + "bumpMap.enabled", 1);
            context->activate(1, textures.bump);
        }
        else
            program->set(prefix + "bumpMap.enabled", 0);

        if (textures.skybox) {
            program->set("skybox.enabled", 1);
            context->activate(2, textures.skybox);
        }
        else
            program->set("skybox.enabled", 0);

        if (skyboxAmbience.enabled) {
            program->set("skybox.ambience.enabled", 1);
            program->set("skybox.ambience.lod", skyboxAmbience.lod);
            program->set("skybox.ambience.intensity", skyboxAmbience.intensity);
            context->activate(2, textures.skybox);
        }
        else
            program->set("skybox.ambience.enabled", 0);

        if (ambience.enabled) {
            program->set("ambience.enabled", 1);
            program->set("ambience.lod", ambience.lod);
            program->set("ambience.intensity", ambience.intensity);
            context->activate(3, textures.ambience);
        }
        else
            program->set("ambience.enabled", 0);
    }
}

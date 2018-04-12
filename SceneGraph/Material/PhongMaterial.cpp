//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

PhongMaterial::PhongMaterial(const shared_ptr<Context>& context) : Material(context)
{}

PhongMaterial::ShadingModel PhongMaterial::getMode() const {
    return mode;
}

PhongMaterial& PhongMaterial::setMode(ShadingModel mode) {
    this->mode = mode;
    return *this;
}

const vec3& PhongMaterial::getEmissive() const {
    return emissive;
}

PhongMaterial& PhongMaterial::setEmissive(const vec3& rgb) {
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

const vec3& PhongMaterial::getAmbientReflectance() const {
    return reflectance.ambient;
}

PhongMaterial& PhongMaterial::setAmbient(const vec3& rgb) {
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

const vec3& PhongMaterial::getDiffuseReflectance() const {
    return reflectance.diffuse;
}

PhongMaterial& PhongMaterial::setDiffuse(const vec3& rgb) {
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

const vec3& PhongMaterial::getSpecularReflectance() const {
    return reflectance.specular;
}

PhongMaterial& PhongMaterial::setSpecular(const vec3& rgb) {
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
    
//    if (!isProgramShared()) {
//        Material::bind();
//        program->set("material.doubleSided", doubleSided ? 1 : 0);
//    }
    
    return *this;
}

#pragma mark Textures

const shared_ptr<Texture>& PhongMaterial::getDiffuseTexture() const {
    return textures.diffuse;
}

PhongMaterial& PhongMaterial::setDiffuseTexture(const shared_ptr<Texture>& texture) {
    textures.diffuse = texture;
    return *this;
}

const shared_ptr<Texture>& PhongMaterial::getBumpTexture() const {
    return textures.bump;
}

PhongMaterial& PhongMaterial::setBumpTexture(const shared_ptr<Texture>& texture) {
    textures.bump = texture;
    return *this;
}

const shared_ptr<Texture>& PhongMaterial::getSkyboxTexture() const {
    return textures.skybox;
}

PhongMaterial& PhongMaterial::setSkyboxTexture(const shared_ptr<Texture>& texture) {
    textures.skybox = texture;
    return *this;
}

const shared_ptr<Texture>& PhongMaterial::getAmbienceTexture() const {
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

void PhongMaterial::syncTextureSamplers()
{
    if (program->isUniformActive("material.diffuseMap.texture"))
        program->set("material.diffuseMap.texture", 0);
    
    if (program->isUniformActive("material.bumpMap.texture"))
        program->set("material.bumpMap.texture", 1);
    
    if (program->isUniformActive("skybox.texture"))
        program->set("skybox.texture", 2);
    
    if (program->isUniformActive("skyboxAmbience.texture"))
        program->set("skyboxAmbience.texture", 2);
    
    if (program->isUniformActive("ambience.texture"))
        program->set("ambience.texture", 3);
}

void PhongMaterial::invalidateVariables()
{
    sync.doubleSided = false;
    sync.opacity = false;
    sync.shininess = false;
    sync.reflectivity = false;
    sync.emissive = false;
    sync.ambient = false;
    sync.diffuse = false;
    sync.specular = false;

    sync.diffuseMapEnabled = false;
    sync.bumpMapEnabled = false;
    sync.skyboxEnabled = false;
    sync.skyboxTransform = false;

    sync.skyboxAmbience.enabled = false;
    sync.skyboxAmbience.lod = false;
    sync.skyboxAmbience.intensity = false;
    
    sync.ambience.enabled = false;
    sync.ambience.lod = false;
    sync.ambience.intensity = false;
}

void PhongMaterial::syncDoubleSided()
{
    if (program->isUniformActive("material.doubleSided"))
        program->set("material.doubleSided", doubleSided ? 1 : 0);

    sync.doubleSided = true;
}

void PhongMaterial::syncOpacity()
{
    if (program->isUniformActive("material.opacity"))
        program->set("material.opacity", opacity);

    sync.opacity = true;
}

void PhongMaterial::syncShininess()
{
    if (program->isUniformActive("material.shininess"))
        program->set("material.shininess", shininess);

    sync.shininess = true;
}

void PhongMaterial::syncReflectivity()
{
    if (program->isUniformActive("material.reflectivity"))
        program->set("material.reflectivity", reflectivity);

    sync.reflectivity = true;
}

void PhongMaterial::syncEmissive()
{
    if (program->isUniformActive("material.emissive"))
        program->set("material.emissive", 3, 1, (const float*)&emissive);

    sync.emissive = true;
}

void PhongMaterial::syncAmbient()
{
    if (program->isUniformActive("material.ambient"))
        program->set("material.ambient", 3, 1, (const float*)&reflectance.ambient);

    sync.ambient = true;
}

void PhongMaterial::syncDiffuse()
{
    if (program->isUniformActive("material.diffuse"))
        program->set("material.diffuse", 3, 1, (const float*)&reflectance.diffuse);

    sync.diffuse = true;
}

void PhongMaterial::syncSpecular()
{
    if (program->isUniformActive("material.specular"))
        program->set("material.specular", 3, 1, (const float*)&reflectance.specular);

    sync.specular = true;
}

void PhongMaterial::syncDiffuseMapEnabled()
{
    if (program->isUniformActive("material.diffuseMap.enabled"))
        program->set("material.diffuseMap.enabled", textures.diffuse != nullptr ? 1 : 0);

    sync.diffuseMapEnabled = true;
}

void PhongMaterial::syncBumpMapEnabled()
{
    if (program->isUniformActive("material.bumpMap.enabled"))
        program->set("material.bumpMap.enabled", textures.bump != nullptr ? 1 : 0);

    sync.bumpMapEnabled = true;
}

void PhongMaterial::syncSkyboxEnabled()
{
    if (program->isUniformActive("skybox.enabled"))
        program->set("skybox.enabled", textures.skybox != nullptr ? 1 : 0);

    sync.skyboxEnabled = true;
}

void PhongMaterial::syncSkyboxTransform()
{
    if (program->isUniformActive("skybox.transform"))
        program->set("skybox.transform", mat3(1));
    
    sync.skyboxTransform = true;
}

void PhongMaterial::syncSkyboxAmbienceEnabled()
{
    if (program->isUniformActive("skybox.ambience.enabled"))
        program->set("skybox.ambience.enabled", skyboxAmbience.enabled ? 1 : 0);

    sync.skyboxAmbience.enabled = true;
}

void PhongMaterial::syncSkyboxAmbienceLod()
{
    if (program->isUniformActive("skybox.ambience.lod"))
        program->set("skybox.ambience.lod", skyboxAmbience.lod);

    sync.skyboxAmbience.lod = true;
}

void PhongMaterial::syncSkyboxAmbienceIntensity()
{
    if (program->isUniformActive("skybox.ambience.intensity"))
        program->set("skybox.ambience.intensity", skyboxAmbience.intensity);

    sync.skyboxAmbience.intensity = true;
}

void PhongMaterial::syncAmbienceEnabled()
{
    if (program->isUniformActive("ambience.enabled"))
        program->set("ambience.enabled", ambience.enabled ? 1 : 0);

    sync.skyboxAmbience.enabled = true;
}

void PhongMaterial::syncAmbienceLod()
{
    if (program->isUniformActive("ambience.lod"))
        program->set("ambience.lod", ambience.lod);

    sync.ambience.lod = true;
}

void PhongMaterial::syncAmbienceIntensity()
{
    if (program->isUniformActive("ambience.intensity"))
        program->set("ambience.intensity", ambience.intensity);

    sync.ambience.intensity = true;
}

void PhongMaterial::syncVariables()
{
    if (isProgramShared())
    {
        syncDoubleSided();
        syncOpacity();
        syncShininess();
        syncReflectivity();
        syncEmissive();
        syncAmbient();
        syncDiffuse();
        syncSpecular();
        syncDiffuseMapEnabled();
        syncBumpMapEnabled();
        syncSkyboxEnabled();
        syncSkyboxTransform();
        syncSkyboxAmbienceEnabled();
        syncSkyboxAmbienceLod();
        syncSkyboxAmbienceIntensity();
        syncAmbienceEnabled();
        syncAmbienceLod();
        syncAmbienceIntensity();
    }
    else
    {
        if (!sync.doubleSided)
            syncDoubleSided();
        
        if (!sync.opacity)
            syncOpacity();
        
        if (!sync.shininess)
            syncShininess();
        
        if (sync.reflectivity)
            syncReflectivity();
        
        if (!sync.emissive)
            syncEmissive();
        
        if (!sync.ambient)
            syncAmbient();
        
        if (!sync.diffuse)
            syncDiffuse();
        
        if (!sync.specular)
            syncSpecular();

        if (!sync.diffuseMapEnabled)
            syncDiffuseMapEnabled();
        
        if (!sync.bumpMapEnabled)
            syncBumpMapEnabled();
        
        if (!sync.skyboxEnabled)
            syncSkyboxEnabled();

        if (!sync.skyboxTransform)
            syncSkyboxTransform();

        if (!sync.skyboxAmbience.enabled)
            syncSkyboxAmbienceEnabled();
        
        if (!sync.skyboxAmbience.lod)
            syncSkyboxAmbienceLod();
        
        if (!sync.skyboxAmbience.intensity)
            syncSkyboxAmbienceIntensity();
        
        if (!sync.ambience.enabled)
            syncAmbienceEnabled();
        
        if (!sync.ambience.lod)
            syncAmbienceLod();
        
        if (!sync.ambience.intensity)
            syncAmbienceIntensity();
    }
}

void PhongMaterial::activateTextures()
{
    if (textures.diffuse)
        context->activate(0, textures.diffuse);

    if (textures.bump)
        context->activate(1, textures.bump);

    if (textures.skybox)
        context->activate(2, textures.skybox);

    if (textures.ambience)
        context->activate(3, textures.ambience);
}

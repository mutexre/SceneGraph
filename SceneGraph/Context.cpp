//
//  Created by mutexre on 13/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Context::Context(OS os) {
    this->os = os;
}

bool Context::init()
{
    loadCurrentSettings();
    return true;
}

Context::OS Context::getOS() const {
    return os;
}

bool Context::isIOS() const {
    return os == OS::ios;
}

bool Context::isMacOS() const {
    return os == OS::macOS;
}

bool Context::isAndroid() const {
    return os == OS::android;
}

bool Context::isWindows() const {
    return os == OS::windows;
}

bool Context::isLinux() const {
    return os == OS::linux;
}

bool Context::isMSAASupported() const {
    return maxMSAASamples.defined;
}

int Context::getMaxMSAASamples() const {
    return maxMSAASamples.value;
}

void Context::activate(const shared_ptr<Program>& program)
{
    if (!activeObjects.program || activeObjects.program.value != program)
    {
        activeObjects.program = program;
        program->bind();
    }
}

void Context::activateSurface(Surface::Target target,
                              Option<shared_ptr<Surface>>& activeSurface,
                              const shared_ptr<Surface>& surface)
{
    if (!activeSurface || activeSurface.value != surface)
    {
        surface->makeActive(target);
        activeSurface = surface;
    }
}

void Context::activate(Surface::Target target, const shared_ptr<Surface>& surface)
{
    if (target == Surface::Target::draw)
        activateSurface(target, activeObjects.surface.draw, surface);
    else
        activateSurface(target, activeObjects.surface.read, surface);
}

void Context::activate(int textureUnit, const shared_ptr<Texture>& texture)
{
    auto iter = activeObjects.texture.find(textureUnit);
    bool found = (iter == activeObjects.texture.end());
    
    if ((found && iter->second != texture) || !found)
    {
        activeObjects.texture[textureUnit] = texture;
        texture->bind(textureUnit);
    }
}

#pragma mark - Factory Methods

shared_ptr<Node> Context::createNode(const string& name) {
    auto node = createNode();
    node->setName(name);
    return node;
}

shared_ptr<MeshNode> Context::createMeshNode(const string& name) {
    auto node = createMeshNode();
    node->setName(name);
    return node;
}

shared_ptr<Light> Context::createLight(const string& name) {
    auto node = createLight();
    node->setName(name);
    return node;
}

shared_ptr<Camera> Context::createCamera(const string& name) {
    auto node = createCamera();
    node->setName(name);
    return node;
}

shared_ptr<Texture> Context::createTexture(Texture::Type type, PixelFormat format) {
    auto texture = createTexture();
    texture->init(type, format);
    return texture;
}

#pragma mark - Programs

const map<string, shared_ptr<Program>>& Context::getPrograms() {
    return programs;
}

const shared_ptr<Program>& Context::getProgram(const char* name) {
    return programs[name];
}

void Context::loadProgram(const char* name, const char* vertex, const char* fragment) {
    addProgram(name, loadProgram(vertex, fragment));
}

void Context::addProgram(const string& name, const shared_ptr<Program>& program) {
    programs[name] = program;
}

void Context::removeProgram(const string& name) {
    programs.erase(name);
}

#pragma mark - Settings

const Settings& Context::getSettings() const {
    return settings;
}

void Context::loadCurrentSettings() {
    settings = fetchCurrentSettings();
}

void Context::applySettings(const Settings& s)
{
    if (s.depthTest && (!settings.depthTest || s.depthTest.value != settings.depthTest.value))
    {
        applyDepthTestSettings(s.depthTest.value);
        settings.depthTest.define(s.depthTest.value);
    }

    if (s.depthClamp && (!settings.depthClamp || s.depthClamp.value != settings.depthClamp.value))
    {
        applyDepthClampSettings(s.depthClamp.value);
        settings.depthClamp.define(s.depthClamp.value);
    }

    if (s.writeDepth && (!settings.writeDepth || s.writeDepth.value != settings.writeDepth.value))
    {
        applyWriteDepthSettings(s.writeDepth.value);
        settings.writeDepth.define(s.writeDepth.value);
    }
    
    if (s.seamlessCubemaps && (!settings.seamlessCubemaps || s.seamlessCubemaps.value != settings.seamlessCubemaps.value)) {
        applySeamlessCubemapsSettings(s.seamlessCubemaps.value);
        settings.seamlessCubemaps.define(s.seamlessCubemaps.value);
    }
    
    if (s.smoothPoints && (!settings.smoothPoints || s.smoothPoints.value != settings.smoothPoints.value)) {
        applySmoothPointsSettings(s.smoothPoints.value);
        settings.smoothPoints.define(s.smoothPoints.value);
    }

    if (s.cullFace && (!settings.cullFace || s.cullFace.value != settings.cullFace.value)) {
        applyCullFaceSettings(s.cullFace.value);
    }

    if (s.blend && (!settings.blend || s.blend.value != settings.blend.value)) {
        applyBlendSettings(s.blend.value);
    }

    if (s.viewport && (!settings.viewport || s.viewport.value != settings.viewport.value)) {
        applyViewportSettings(s.viewport.value);
        settings.viewport.define(s.viewport.value);
    }

    if (s.scissor && (!settings.scissor || s.scissor.value != settings.scissor.value)) {
        applyScissorSettings(s.scissor.value);
    }
    
    if (s.colorMask && (!settings.colorMask || s.colorMask.value != settings.colorMask.value)) {
        applyColorMaskSettings(s.colorMask.value);
        settings.colorMask.define(s.colorMask.value);
    }
}

//
//  Created by mutexre on 20/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

Scene::Scene(const shared_ptr<Context>& context) {
    setContext(context);
}

Scene::~Scene()
{}

void Scene::init()
{}

const shared_ptr<Context>& Scene::getContext() const {
    return context;
}

void Scene::setContext(const shared_ptr<Context>& context) {
    this->context = context;
}

shared_ptr<Node> Scene::findNode(const string& nodeName) {
    return root->findSubNode(nodeName);
}

void Scene::draw(const shared_ptr<Camera>& camera) {
    root->drawRecursively(shared_from_this(), camera);
}

void Scene::addNode(const shared_ptr<Node>& node, const shared_ptr<Node>& where)
{
    if (where)
        where->addChild(node);
    else {
        if (root)
            root->addChild(node);
    }
}

void Scene::setDefaultCamera(const shared_ptr<Camera>& camera) {
    defaultCamera = camera;
}

const shared_ptr<Node>& Scene::getSkybox() const {
    return skybox;
}

void Scene::setSkybox(const shared_ptr<Node>& node) {
    skybox = node;
}

void Scene::addLight(const shared_ptr<Light>& light, const shared_ptr<Node>& where) {
    addNode(light, where);
    lights.insert(light);
}

void Scene::addLight(const shared_ptr<Light>& light) {
    addLight(light, root);
}

void Scene::removeLight(const shared_ptr<Light>& light) {
    lights.erase(light);
}

const shared_ptr<Node>& Scene::getRoot() const {
    return root;
}

void Scene::setRoot(const shared_ptr<Node>& node) {
    root = node;
}

void Scene::setGlobalAmbient(const vec3& value) {
    globalAmbient = value;
}

//unsigned Scene::getLightCount() const {
//    return lightCount;
//}
//
//void Scene::setLightCount(unsigned value) {
//    lightCount = value;
//}

void Scene::animate(double t) {
    root->animate(t, true);
}

unsigned Scene::newLightGroup() {
    return ++currentLightGroup;
}

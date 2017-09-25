//
//  Created by mutexre on 12/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Node::Node() : type(Type::unknown)
{}

Node::Node(const string& name)
    : Node(Type::unknown, name)
{}

Node::Node(Type type, const string& name)
    : Object(name), type(type)
{}

void Node::init()
{}

Node::Type Node::getType() const {
    return type;
}

Node& Node::setType(Type type) {
    this->type = type;
    return *this;
}

const weak_ptr<Node>& Node::getParent() const {
    return parent;
}

Node& Node::setParent(const shared_ptr<Node>& value) {
    parent = value;
    return *this;
}

const list<shared_ptr<Node>>& Node::getChildren() const {
    return children;
}

void Node::insertChildAtIndex(const shared_ptr<Node>&, int index) {
}

void Node::insertChildPriorToAnotherChild(const shared_ptr<Node>& node, const shared_ptr<Node>& another) {
}

void Node::insertChildNextToAnotherChild(const shared_ptr<Node>& node, const shared_ptr<Node>& another) {
}

void Node::insertFirstChild(const shared_ptr<Node>&) {
}

void Node::insertLastChild(const shared_ptr<Node>&) {
}

void Node::removeChild(const shared_ptr<Node>&) {
}

void Node::removeChildAtIndex(unsigned) {
}

void Node::removeAllChildren() {
}

void Node::exchangeChildren(unsigned a, unsigned b) {
}

void Node::sendToBack(const shared_ptr<Node>& child)
{
    auto iter = find(children.begin(), children.end(), child);
    if (iter != children.end()) {
        children.erase(iter);
        children.push_front(child);
    }
}

void Node::bringToFront(const shared_ptr<Node>& child)
{
    auto iter = find(children.begin(), children.end(), child);
    if (iter != children.begin() && iter != children.end()) {
        children.erase(iter);
        children.push_back(child);
    }
}

bool Node::isVisible() const {
    return visible;
}

Node& Node::setVisible(bool visible) {
    this->visible = visible;
    return *this;
}

void Node::toggleVisibility() {
    this->visible = !this->visible;
}

bool Node::inheriteVisibility() const {
    return visibilityInheritance;
}

Node& Node::setVisibilityInheritance(bool value) {
    visibilityInheritance = value;
    return *this;
}

const Option<Settings>& Node::getSettings() const {
    return settings;
}

Option<Settings>& Node::getSettings() {
    return settings;
}

Node& Node::setSettings(const Settings& s) {
    settings = s;
    return *this;
}

void Node::removeSettings() {
    settings.undefine();
}

void Node::animate(double t, bool recursive) {
    if (animateFunc) animateFunc.value(this, t);
    if (recursive)
        for (auto& child : children)
            child->animate(t, recursive);
}

Node& Node::setAnimation(const Option<function<void(Node*, double)>>& f) {
    animateFunc = f;
    return *this;
}

const mat4& Node::getModelMatrix() const {
    return matrix.model;
}

mat4& Node::getModelMatrix() {
    return matrix.model;
}

void Node::setModelMatrix(const mat4& m) {
    matrix.model = m;
}

const mat4& Node::getWorldMatrix() const {
    return matrix.world;
}

void Node::updateWorldMatrix() {
    shared_ptr<Node> p = parent.lock();
    matrix.world = (p ? p->getWorldMatrix() * matrix.model : matrix.model);
}

void Node::updateWorldMatrixRecursively() {
    updateWorldMatrix();
    for (auto& child : children)
        child->updateWorldMatrixRecursively();
}

unsigned Node::getLightGroup() const {
    return lightGroup;
}

void Node::setLightGroup(unsigned g) {
    lightGroup = g;
}

void Node::traverse(const function<bool(shared_ptr<Node>&)>& f) {
    auto x = shared_from_this();
    if (f(x)) {
        for (auto& child : children)
            child->traverse(f);
    }
}

shared_ptr<Node> Node::findSubNode(const string& subNodeName)
{
    shared_ptr<Node> retval(nullptr);

    traverse([&retval, &subNodeName](shared_ptr<Node>& node) -> bool {
        if (node->getName().compare(subNodeName) == 0) {
            retval = node;
            return false;
        }
        return true;
    });

    return retval;
}

void Node::addChild(const shared_ptr<Node>& node) {
    children.push_back(node);
    node->setParent(shared_from_this());
}

void Node::draw(const shared_ptr<Scene>&, const shared_ptr<Camera>&)
{}

void Node::drawRecursively(const shared_ptr<Scene>& scene,
                           const shared_ptr<Camera>& camera,
                           Settings combinedSettings)
{
    if (visible)
    {
        if (settings)
            combinedSettings.apply(settings.value);
        
        scene->getContext()->applySettings(combinedSettings);
        
        draw(scene, camera);
        
        for (auto& child : children)
            child->drawRecursively(scene, camera, combinedSettings);
    }
}

void Node::print() {
    traverse([](shared_ptr<Node>& node) -> bool {
//        LOGD("node: \"%s\" of type %u with %llu children\n",
//            node->getName().c_str(),
//            node->getType(),
//            node->getChildren().size());
        return true;
    });
}

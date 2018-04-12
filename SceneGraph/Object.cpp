//
//  Created by mutexre on 22/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

Object::Object() : name("")
{}

Object::Object(const string& name) : name(name)
{}

Object::Object(string&& name) : name(move(name))
{}

Object::~Object()
{}

const shared_ptr<Context>& Object::getContext() const {
    return context;
}

void Object::setContext(const shared_ptr<Context>& context) {
    this->context = context;
}

const string& Object::getName() const {
    return name;
}

void Object::setName(const string& name) {
    this->name = name;
}

void Object::setName(string&& name) {
    this->name = move(name);
}

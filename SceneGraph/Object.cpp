//
//  Created by mutexre on 22/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Object::Object() : name("")
{}

Object::Object(const string& name) : name(name)
{}

Object::~Object()
{}

shared_ptr<Context> Object::getContext() const {
    return context;
}

void Object::setContext(const shared_ptr<Context>& context) {
    this->context = context;
}

string Object::getName() const {
    return name;
}

void Object::setName(const string& name) {
    this->name = name;
}

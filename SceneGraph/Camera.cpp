//
//  Camera.cpp
//  SceneGraph
//
//  Created by mutexre on 21/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Camera::Camera()
{}

Camera::Camera(const string& name)
    : Node(Node::Type::camera, name)
{}

Camera::Camera(const string& name, ProjectionType type, float fov, float near, float far, float aspect)
    : Camera(name)
{
    setProjectionType(type);
    setNear(near);
    setFar(far);
    setAspectRatio(aspect);
    setFov(fov);
    setMinFov(fov);
    setMaxFov(fov);
}

Camera& Camera::setProjectionType(ProjectionType type) {
    projectionType = type;
    return *this;
}

float Camera::getFov() const {
    return fov.value;
}

Camera& Camera::setFov(float value) {
    fov.value = value;
    return *this;
}

float Camera::getMinFov() const {
    return fov.min;
}

Camera& Camera::setMinFov(float value) {
    fov.min = value;
    return *this;
}

float Camera::getMaxFov() const {
    return fov.max;
}

Camera& Camera::setMaxFov(float value) {
    fov.max = value;
    return *this;
}

float Camera::getNear() const {
    return near;
}

Camera& Camera::setNear(float value) {
    near = value;
    return *this;
}

float Camera::getFar() const {
    return far;
}

Camera& Camera::setFar(float value) {
    far = value;
    return *this;
}

float Camera::getAspectRatio() const {
    return aspect;
}

Camera& Camera::setAspectRatio(float value) {
    aspect = value;
    return *this;
}

const mat4& Camera::getViewMatrix() const {
    return viewMatrix;
}

void Camera::updateViewMatrix() {
    viewMatrix = inverse(matrix.world);
}

const mat4& Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

mat4 Camera::getProjectionMatrix(ProjectionType type, float fov, float near, float far, float aspect) {
    switch (type) {
        case ProjectionType::orthogonal:
            return ortho(-1.f, +1.f, -aspect, +aspect, near, far);
        break;

        case ProjectionType::perspective:
            return perspective(fov, 1.0f / aspect, near, far);
        break;
    }
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = getProjectionMatrix(projectionType, fov.value, near, far, aspect);
}

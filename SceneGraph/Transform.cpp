//
//  Created by mutexre on 22/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

void Transform::Rotation::update()
{
    auto x = eulerAngleX(xyz[0]);
    auto y = eulerAngleY(xyz[1]);
    auto z = eulerAngleZ(xyz[2]);

    switch (order) {
        case RotationOrder::xyz:
            matrix = z * (y * x);
        break;

        case RotationOrder::xzy:
            matrix = y * (z * x);
        break;

        case RotationOrder::yzx:
            matrix = x * (z * y);
        break;

        case RotationOrder::yxz:
            matrix = z * (x * y);
        break;

        case RotationOrder::zxy:
            matrix = y * (x * z);
        break;

        case RotationOrder::zyx:
            matrix = x * (y * z);
        break;

        default:
            matrix = mat4(1.f);
        break;
    }

    matrix = postRotation * matrix;
}

void Transform::Scale::update() {
    matrix = glm::scale(mat4(1.f), xyz);
}

void Transform::Translate::update() {
    matrix = glm::translate(mat4(1.f), xyz);
}

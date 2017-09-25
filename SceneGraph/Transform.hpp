//
//  Created by mutexre on 18/09/16.
//  Copyright © 2016 Some Organization. All rights reserved.
//

namespace SG
{
    enum class RotationOrder {
        xyz, xzy, yzx, yxz, zxy, zyx, none
    };

    struct Transform
    {
        struct Component {
            bool enabled;
            vec3 xyz;
            mat4 matrix;
            virtual void update() = 0;
        };

        struct Scale : public Component {
            Scale() { xyz = vec3(1.f); }
            void update() override;
        }
        scale;

        struct Rotation: public Component {
            RotationOrder order;
            mat4 postRotation;
            Rotation() { xyz = vec3(0.f); }
            void update() override;
        }
        rotate;

        struct Translate : public Component {
            Translate() { xyz = vec3(0.f); }
            void update() override;
        }
        translate;
    };
}

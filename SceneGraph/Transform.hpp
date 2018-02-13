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

        struct Scale : public Component
        {
            Scale() {
                xyz.x = xyz.y = xyz.z = 1;
            }
            void update() override;
        }
        scale;

        struct Rotation: public Component
        {
            RotationOrder order;
            mat4 postRotation;
            Rotation() {
                xyz.x = xyz.y = xyz.z = 0;
            }
            void update() override;
        }
        rotate;

        struct Translate : public Component
        {
            Translate() {
                xyz.x = xyz.y = xyz.z = 0;
            }
            void update() override;
        }
        translate;
    };
}

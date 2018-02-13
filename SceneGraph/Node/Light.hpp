//
//  Created by mutexre on 14/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Light : public virtual Node
    {
    public:
        enum class Type : unsigned {
            ambient = 0,
            directional = 1,
            point = 2,
            spot  = 3
        };

    private:
        bool enabled;
        Type type;
        unsigned group;

        vec3 ambient  = { 0, 0, 0 };
        vec3 diffuse  = { 1, 1, 1 };
        vec3 specular = { 1, 1, 1 };

        vec3 direction;

        struct {
            float exponent;
            float cutoff;
            float cosCutoff;
        }
        spot;

        float attenuation[3] = { 1, 0, 0 };

    public:
        Light();
        Light(const string& name);

        bool isEnabled() const;
        Light& setEnabled(bool = true);
        
        Type getType() const;
        Light& setType(Type);

        unsigned getGroup() const;
        Light& setGroup(unsigned g);
        
        vec3 getAmbient() const;
        Light& setAmbient(vec3);
        Light& setAmbient(float, float, float);
        Light& setAmbient(float);
        
        vec3 getDiffuse() const;
        Light& setDiffuse(vec3);
        Light& setDiffuse(float, float, float);
        Light& setDiffuse(float);
        
        vec3 getSpecular() const;
        Light& setSpecular(vec3);
        Light& setSpecular(float, float, float);
        Light& setSpecular(float);
        
        float getAttenuation(unsigned) const;
        Light& setAttenuation(unsigned, float);
        Light& setAttenuation(float, float, float);

        vec3 getDirection() const;
        Light& setDirection(vec3);
        Light& setDirection(float, float, float);
        Light& setDirection(float);

        void setOnGPU(int index, const shared_ptr<Program>&,
                      const vec3& viewCoord,
                      const vec3& direction);
    };
}

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

        glm::vec3 ambient  = { 0, 0, 0 };
        glm::vec3 diffuse  = { 1, 1, 1 };
        glm::vec3 specular = { 1, 1, 1 };

        glm::vec3 direction;

        struct {
            float exponent;
            float cutoff;
            float cosCutoff;
        }
        spot;

        float attenuation[3] = { 1, 0, 0 };

    public:
        Light();
        Light(const std::string& name);

        bool isEnabled() const;
        Light& setEnabled(bool = true);
        
        Type getType() const;
        Light& setType(Type);

        unsigned getGroup() const;
        Light& setGroup(unsigned g);
        
        glm::vec3 getAmbient() const;
        Light& setAmbient(glm::vec3);
        Light& setAmbient(float, float, float);
        Light& setAmbient(float);
        
        glm::vec3 getDiffuse() const;
        Light& setDiffuse(glm::vec3);
        Light& setDiffuse(float, float, float);
        Light& setDiffuse(float);
        
        glm::vec3 getSpecular() const;
        Light& setSpecular(glm::vec3);
        Light& setSpecular(float, float, float);
        Light& setSpecular(float);
        
        float getAttenuation(unsigned) const;
        Light& setAttenuation(unsigned, float);
        Light& setAttenuation(float, float, float);

        glm::vec3 getDirection() const;
        Light& setDirection(glm::vec3);
        Light& setDirection(float, float, float);
        Light& setDirection(float);

        void setOnGPU(int index, const std::shared_ptr<Program>&,
                      const glm::vec3& viewCoord,
                      const glm::vec3& direction);
    };
}

//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class ColorMaterial : public Material
    {
    protected:
        glm::vec4 color;
        bool colorSynced;

    protected:
        virtual void invalidateVariables() override;
        virtual void syncVariables() override;
        void syncColor();

    public:
        ColorMaterial(const std::shared_ptr<Context>&);
        
        ColorMaterial(const std::shared_ptr<Context>&,
                      const std::shared_ptr<Program>&,
                      glm::vec4 color);
        
        const glm::vec4& getColor() const;
        void setColor(glm::vec4);
    };
}

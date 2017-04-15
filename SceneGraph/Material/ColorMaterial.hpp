//
//  SkyboxMaterial.hpp
//  SceneGraph
//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class ColorMaterial : public Material
    {
    protected:
        vec4 color;
        bool colorSynced;

    protected:
        virtual void invalidateVariables() override;
        virtual void syncVariables() override;
        void syncColor();

    public:
        ColorMaterial(const shared_ptr<Context>&);
        
        ColorMaterial(const shared_ptr<Context>&,
                      const shared_ptr<Program>&,
                      vec4 color);
        
        vec4 getColor() const;
        void setColor(vec4);
    };
}

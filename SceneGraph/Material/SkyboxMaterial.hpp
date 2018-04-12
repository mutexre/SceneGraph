//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class SkyboxMaterial : public Material
    {
    protected:
        std::shared_ptr<Texture> texture;

        float lod = 0;
        bool lodSynced;
    
    protected:
        virtual void syncTextureSamplers() override;
        virtual void invalidateVariables() override;
        virtual void syncVariables() override;
        virtual void activateTextures() override;
        
        void syncLod();

    public:
        SkyboxMaterial(const std::shared_ptr<Context>&);

        SkyboxMaterial(const std::shared_ptr<Context>&,
                       const std::shared_ptr<Program>&,
                       const std::shared_ptr<Texture>&,
                       float lod);

        const std::shared_ptr<Texture>& getTexture() const;
        SkyboxMaterial& setTexture(const std::shared_ptr<Texture>&);
        
        float getLod() const;
        SkyboxMaterial& setLod(float);
    };
}

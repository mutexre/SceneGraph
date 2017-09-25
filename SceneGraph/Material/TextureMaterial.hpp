//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class TextureMaterial : public Material
    {
    protected:
        shared_ptr<Texture> texture;
        mat3 uvTransform { 1 };
        bool uvTransformSynced;

    protected:
        virtual void syncTextureSamplers() override;
        virtual void invalidateVariables() override;
        virtual void syncVariables() override;
        virtual void activateTextures() override;
        
        void syncUvTransform();

    public:
        TextureMaterial(const shared_ptr<Context>&);
        
        TextureMaterial(const shared_ptr<Context>&,
                        const shared_ptr<Program>&,
                        const shared_ptr<Texture>&,
                        mat3 uvTransform = mat3(1));

        shared_ptr<Texture>& getTexture();
        TextureMaterial& setTexture(const shared_ptr<Texture>&);
        
        mat3 getUvTransform() const;
        TextureMaterial& setUvTransform(mat3);
    };
}

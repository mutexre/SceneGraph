//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class TextureMaterial : public Material
    {
    protected:
        std::shared_ptr<Texture> texture;
        glm::mat3 uvTransform { 1 };
        bool uvTransformSynced;

    protected:
        virtual void syncTextureSamplers() override;
        virtual void invalidateVariables() override;
        virtual void syncVariables() override;
        virtual void activateTextures() override;
        
        void syncUvTransform();

    public:
        TextureMaterial(const std::shared_ptr<Context>&);
        
        TextureMaterial(const std::shared_ptr<Context>&,
                        const std::shared_ptr<Program>&,
                        const std::shared_ptr<Texture>&,
                        glm::mat3 uvTransform = glm::mat3(1));

        std::shared_ptr<Texture>& getTexture();
        TextureMaterial& setTexture(const std::shared_ptr<Texture>&);
        
        const glm::mat3& getUvTransform() const;
        TextureMaterial& setUvTransform(const glm::mat3&);
    };
}

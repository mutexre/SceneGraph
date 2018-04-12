//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class TextureMaterialYUVA : public Material
    {
    protected:
        struct {
            std::shared_ptr<Texture> luma, chroma, alpha;
        }
        textures;

        glm::mat3 colorConversion;
        
        struct {
            glm::mat3 luma {1};
            glm::mat3 chroma {1};
            glm::mat3 alpha {1};
        }
        uvTransform;
    
        struct
        {
            bool colorConversion;
            
            struct {
                bool luma, chroma, alpha;
            }
            uvTransform;
        }
        sync;
    
    protected:
        virtual void syncTextureSamplers() override;
        virtual void invalidateVariables() override;
        virtual void syncVariables() override;
        virtual void activateTextures() override;
    
        void syncColorConversion();
        void syncLumaUvTransform();
        void syncChromaUvTransform();
        void syncAlphaUvTransform();
    
    public:
        TextureMaterialYUVA(const std::shared_ptr<Context>&);

        TextureMaterialYUVA(const std::shared_ptr<Context>&,
                            const std::shared_ptr<Program>&,
                            const std::shared_ptr<Texture>& luma,
                            const std::shared_ptr<Texture>& chroma,
                            const std::shared_ptr<Texture>& alpha,
                            const glm::mat3& colorConversion,
                            const glm::mat3& lumaUvTransform = glm::mat3(1),
                            const glm::mat3& chromaUvTransform = glm::mat3(1),
                            const glm::mat3& alphaUvTransform = glm::mat3(1));

        std::shared_ptr<Texture>& getLumaTexture();
        TextureMaterialYUVA& setLumaTexture(const std::shared_ptr<Texture>&);
        
        std::shared_ptr<Texture>& getChromaTexture();
        TextureMaterialYUVA& setChromaTexture(const std::shared_ptr<Texture>&);
        
        std::shared_ptr<Texture>& getAlphaTexture();
        TextureMaterialYUVA& setAlphaTexture(const std::shared_ptr<Texture>&);
        
        const glm::mat3& getColorConversion() const;
        TextureMaterialYUVA& setColorConversion(const glm::mat3&);
        
        const glm::mat3& getLumaUvTransform() const;
        TextureMaterialYUVA& setLumaUvTransform(const glm::mat3&);
        
        const glm::mat3& getChromaUvTransform() const;
        TextureMaterialYUVA& setChromaUvTransform(const glm::mat3&);
        
        const glm::mat3& getAlphaUvTransform() const;
        TextureMaterialYUVA& setAlphaUvTransform(const glm::mat3&);
    };
}

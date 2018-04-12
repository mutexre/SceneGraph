//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class TextureMaterialRGBA : public Material
    {
    protected:
        struct {
            std::shared_ptr<Texture> color, alpha;
        }
        textures;
        
        struct {
            glm::mat3 color{1}, alpha{1};
        }
        uvTransform;
        
        Option<float> fixedAlpha;
        
        struct
        {
            struct {
                bool color, alpha;
            }
            uvTransform;
            
            struct {
                bool use, value;
            }
            fixedAlpha;
        }
        sync;
    
    protected:
        virtual void syncTextureSamplers() override;
        virtual void invalidateVariables() override;
        virtual void syncVariables() override;
        virtual void activateTextures() override;
        
        void syncColorUvTransform();
        void syncAlphaUvTransform();
        void syncUseFixedAlpha();
        void syncFixedAlphaValue();

    public:
        TextureMaterialRGBA(const std::shared_ptr<Context>&);
        
        TextureMaterialRGBA(const std::shared_ptr<Context>&,
                            const std::shared_ptr<Program>&,
                            const std::shared_ptr<Texture>& color,
                            const std::shared_ptr<Texture>& alpha,
                            const glm::mat3& colorUvTransform,
                            const glm::mat3& alphaUvTransform);
        
        std::shared_ptr<Texture>& getColorTexture();
        TextureMaterialRGBA& setColorTexture(const std::shared_ptr<Texture>&);
        
        std::shared_ptr<Texture>& getAlphaTexture();
        TextureMaterialRGBA& setAlphaTexture(const std::shared_ptr<Texture>&);
        
        const glm::mat3& getColorUvTransform() const;
        TextureMaterialRGBA& setColorUvTransform(const glm::mat3&);
        
        const glm::mat3& getAlphaUvTransform() const;
        TextureMaterialRGBA& setAlphaUvTransform(const glm::mat3&);
        
        Option<float> getFixedAlpha() const;
        TextureMaterialRGBA& setFixedAlpha(const Option<float>&);
        TextureMaterialRGBA& disableFixedAlpha();
    };
}

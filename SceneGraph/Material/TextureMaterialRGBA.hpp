//
//  SkyboxMaterial.hpp
//  SceneGraph
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
            shared_ptr<Texture> color, alpha;
        }
        textures;
        
        struct {
            mat3 color{1}, alpha{1};
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
        TextureMaterialRGBA(const shared_ptr<Context>&);
        
        TextureMaterialRGBA(const shared_ptr<Context>&,
                            const shared_ptr<Program>&,
                            const shared_ptr<Texture>& color,
                            const shared_ptr<Texture>& alpha,
                            mat3 colorUvTransform,
                            mat3 alphaUvTransform);
        
        shared_ptr<Texture>& getColorTexture();
        TextureMaterialRGBA& setColorTexture(const shared_ptr<Texture>&);
        
        shared_ptr<Texture>& getAlphaTexture();
        TextureMaterialRGBA& setAlphaTexture(const shared_ptr<Texture>&);
        
        mat3 getColorUvTransform() const;
        TextureMaterialRGBA& setColorUvTransform(mat3);
        
        mat3 getAlphaUvTransform() const;
        TextureMaterialRGBA& setAlphaUvTransform(mat3);
        
        Option<float> getFixedAlpha() const;
        TextureMaterialRGBA& setFixedAlpha(const Option<float>&);
        TextureMaterialRGBA& disableFixedAlpha();
    };
}

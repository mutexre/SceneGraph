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
            shared_ptr<Texture> luma, chroma, alpha;
        }
        textures;

        mat3 colorConversion;
        
        struct {
            mat3 luma {1};
            mat3 chroma {1};
            mat3 alpha {1};
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
        TextureMaterialYUVA(const shared_ptr<Context>&);

        TextureMaterialYUVA(const shared_ptr<Context>&,
                            const shared_ptr<Program>&,
                            const shared_ptr<Texture>& luma,
                            const shared_ptr<Texture>& chroma,
                            const shared_ptr<Texture>& alpha,
                            const mat3& colorConversion,
                            const mat3& lumaUvTransform = mat3(1),
                            const mat3& chromaUvTransform = mat3(1),
                            const mat3& alphaUvTransform = mat3(1));

        shared_ptr<Texture>& getLumaTexture();
        TextureMaterialYUVA& setLumaTexture(const shared_ptr<Texture>&);
        
        shared_ptr<Texture>& getChromaTexture();
        TextureMaterialYUVA& setChromaTexture(const shared_ptr<Texture>&);
        
        shared_ptr<Texture>& getAlphaTexture();
        TextureMaterialYUVA& setAlphaTexture(const shared_ptr<Texture>&);
        
        const mat3& getColorConversion() const;
        TextureMaterialYUVA& setColorConversion(const mat3&);
        
        const mat3& getLumaUvTransform() const;
        TextureMaterialYUVA& setLumaUvTransform(const mat3&);
        
        const mat3& getChromaUvTransform() const;
        TextureMaterialYUVA& setChromaUvTransform(const mat3&);
        
        const mat3& getAlphaUvTransform() const;
        TextureMaterialYUVA& setAlphaUvTransform(const mat3&);
    };
}

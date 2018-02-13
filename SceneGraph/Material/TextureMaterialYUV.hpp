//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class TextureMaterialYUV : public Material
    {
    public:
        enum class Mode {
            uv, u_v
        };
    
    protected:
        Mode mode;
        
        struct {
            shared_ptr<Texture> y, u, v, uv;
        }
        textures;

        mat3 colorConversion;
        
        struct
        {
            mat3 y{1};
            mat3 u{1};
            mat3 v{1};
            mat3 uv{1};
        }
        uvTransform;
        
        struct
        {
            bool colorConversion;
            
            struct {
                bool y, u, v, uv;
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
        void syncUvTransformY();
        void syncUvTransformU();
        void syncUvTransformV();
        void syncUvTransformUV();
    
    public:
        TextureMaterialYUV(const shared_ptr<Context>&);
        
        TextureMaterialYUV(const shared_ptr<Context>&,
                           const shared_ptr<Program>&,
                           const shared_ptr<Texture>& y,
                           const shared_ptr<Texture>& uv,
                           const mat3& colorConversion,
                           const mat3& yTransform = mat3(1),
                           const mat3& uvTransform = mat3(1));
        
        TextureMaterialYUV(const shared_ptr<Context>&,
                           const shared_ptr<Program>&,
                           const shared_ptr<Texture>& y,
                           const shared_ptr<Texture>& u,
                           const shared_ptr<Texture>& v,
                           const mat3& colorConversion,
                           const mat3& yTransform = mat3(1),
                           const mat3& uTransform = mat3(1),
                           const mat3& vTransform = mat3(1));
        
        Mode getMode() const;
        void setMode(Mode);
        
        shared_ptr<Texture>& getY();
        TextureMaterialYUV& setY(const shared_ptr<Texture>&);
        
        shared_ptr<Texture>& getU();
        TextureMaterialYUV& setU(const shared_ptr<Texture>&);
        
        shared_ptr<Texture>& getV();
        TextureMaterialYUV& setV(const shared_ptr<Texture>&);
        
        shared_ptr<Texture>& getUV();
        TextureMaterialYUV& setUV(const shared_ptr<Texture>&);
        
        const mat3& getColorConversion() const;
        TextureMaterialYUV& setColorConversion(const mat3&);
        
        const mat3& getUvTransformY() const;
        TextureMaterialYUV& setUvTransformY(const mat3&);

        const mat3& getUvTransformU() const;
        TextureMaterialYUV& setUvTransformU(const mat3&);
        
        const mat3& getUvTransformV() const;
        TextureMaterialYUV& setUvTransformV(const mat3&);
        
        const mat3& getUvTransformUV() const;
        TextureMaterialYUV& setUvTransformUV(const mat3&);
    };
}

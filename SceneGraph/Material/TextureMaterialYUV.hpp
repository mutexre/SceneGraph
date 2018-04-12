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
            std::shared_ptr<Texture> y, u, v, uv;
        }
        textures;

        glm::mat3 colorConversion;
        
        struct
        {
            glm::mat3 y{1};
            glm::mat3 u{1};
            glm::mat3 v{1};
            glm::mat3 uv{1};
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
        TextureMaterialYUV(const std::shared_ptr<Context>&);
        
        TextureMaterialYUV(const std::shared_ptr<Context>&,
                           const std::shared_ptr<Program>&,
                           const std::shared_ptr<Texture>& y,
                           const std::shared_ptr<Texture>& uv,
                           const glm::mat3& colorConversion,
                           const glm::mat3& yTransform = glm::mat3(1),
                           const glm::mat3& uvTransform = glm::mat3(1));
        
        TextureMaterialYUV(const std::shared_ptr<Context>&,
                           const std::shared_ptr<Program>&,
                           const std::shared_ptr<Texture>& y,
                           const std::shared_ptr<Texture>& u,
                           const std::shared_ptr<Texture>& v,
                           const glm::mat3& colorConversion,
                           const glm::mat3& yTransform = glm::mat3(1),
                           const glm::mat3& uTransform = glm::mat3(1),
                           const glm::mat3& vTransform = glm::mat3(1));
        
        Mode getMode() const;
        void setMode(Mode);
        
        std::shared_ptr<Texture>& getY();
        TextureMaterialYUV& setY(const std::shared_ptr<Texture>&);
        
        std::shared_ptr<Texture>& getU();
        TextureMaterialYUV& setU(const std::shared_ptr<Texture>&);
        
        std::shared_ptr<Texture>& getV();
        TextureMaterialYUV& setV(const std::shared_ptr<Texture>&);
        
        std::shared_ptr<Texture>& getUV();
        TextureMaterialYUV& setUV(const std::shared_ptr<Texture>&);
        
        const glm::mat3& getColorConversion() const;
        TextureMaterialYUV& setColorConversion(const glm::mat3&);
        
        const glm::mat3& getUvTransformY() const;
        TextureMaterialYUV& setUvTransformY(const glm::mat3&);

        const glm::mat3& getUvTransformU() const;
        TextureMaterialYUV& setUvTransformU(const glm::mat3&);
        
        const glm::mat3& getUvTransformV() const;
        TextureMaterialYUV& setUvTransformV(const glm::mat3&);
        
        const glm::mat3& getUvTransformUV() const;
        TextureMaterialYUV& setUvTransformUV(const glm::mat3&);
    };
}

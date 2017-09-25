//
//  Created by mutexre on 05/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class PhongMaterial : public Material
    {
    public:
        enum class ShadingModel {
            flat,
            gouraud,
            lambert,
            phong
        };

        ShadingModel mode = ShadingModel::phong;

        bool doubleSided = false;

        float opacity = 1;
        float shininess = 16;
        float reflectivity = 0;

        vec3 emissive = { 0, 0, 0 };

        struct {
            vec3 ambient  = { 1, 1, 1 };
            vec3 diffuse  = { 1, 1, 1 };
            vec3 specular = { 1, 1, 1 };
        }
        reflectance;

        vec3 refractionIndex = { 1, 1, 1 };

        struct {
            shared_ptr<Texture> diffuse, bump, skybox, ambience;
        }
        textures;
        
        struct {
            bool enabled = false;
            float lod = 0;
            float intensity = 1;
        }
        skyboxAmbience, ambience;

    public:
        PhongMaterial(const shared_ptr<Context>&);

        ShadingModel getMode() const;
        PhongMaterial& setMode(ShadingModel);

        vec3 getEmissive() const;
        PhongMaterial& setEmissive(vec3);
        PhongMaterial& setEmissive(float r, float g, float b);
        PhongMaterial& setEmissive(float);

        vec3 getAmbientReflectance() const;
        PhongMaterial& setAmbient(vec3);
        PhongMaterial& setAmbient(float r, float g, float b);
        PhongMaterial& setAmbient(float);

        vec3 getDiffuseReflectance() const;
        PhongMaterial& setDiffuse(vec3);
        PhongMaterial& setDiffuse(float r, float g, float b);
        PhongMaterial& setDiffuse(float);

        vec3 getSpecularReflectance() const;
        PhongMaterial& setSpecular(vec3);
        PhongMaterial& setSpecular(float r, float g, float b);
        PhongMaterial& setSpecular(float);

        float getOpacity() const;
        PhongMaterial& setOpacity(float);

        float getShininess() const;
        PhongMaterial& setShininess(float);

        float getReflectivity() const;
        PhongMaterial& setReflectivity(float);
        
        bool getDoubleSided() const;
        PhongMaterial& setDoubleSided(bool);

        shared_ptr<Texture> getDiffuseTexture() const;
        PhongMaterial& setDiffuseTexture(const shared_ptr<Texture>&);
        
        shared_ptr<Texture> getBumpTexture() const;
        PhongMaterial& setBumpTexture(const shared_ptr<Texture>&);
        
        shared_ptr<Texture> getSkyboxTexture() const;
        PhongMaterial& setSkyboxTexture(const shared_ptr<Texture>&);

        shared_ptr<Texture> getAmbienceTexture() const;
        PhongMaterial& setAmbienceTexture(const shared_ptr<Texture>&);
        
        bool isSkyboxAmbienceMapEnabled() const;
        PhongMaterial& enableSkyboxAmbienceMap(bool = true);
        PhongMaterial& disableSkyboxAmbienceMap();
        
        float getSkyboxAmbienceLod() const;
        PhongMaterial& setSkyboxAmbienceLod(float);
        
        float getSkyboxAmbienceIntensity() const;
        PhongMaterial& setSkyboxAmbienceIntensity(float);

        bool isAmbienceMapEnabled() const;
        PhongMaterial& enableAmbienceMap(bool = true);
        PhongMaterial& disableAmbienceMap();
        
        float getAmbienceLod() const;
        PhongMaterial& setAmbienceLod(float);
        
        float getAmbienceIntensity() const;
        PhongMaterial& setAmbienceIntensity(float);

        virtual void bind();
    };
}

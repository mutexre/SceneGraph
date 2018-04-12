//
//  Created by mutexre on 13/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

namespace SG
{
    class Context : public std::enable_shared_from_this<Context>
    {
    protected:
        std::map<std::string, std::shared_ptr<Program>> programs;
        Settings settings;
        OS os;
        Option<int> maxMSAASamples;
        
        struct
        {
            Option<std::shared_ptr<Program>> program;

            struct {
                Option<std::shared_ptr<Surface>> draw, read;
            }
            surface;
            
            std::map<int, std::shared_ptr<Texture>> texture;
        }
        activeObjects;
        
    protected:
        virtual std::shared_ptr<Program> loadProgram(const std::string& vertexShaderName,
                                                     const std::string& fragmentShaderName) = 0;
        
        void activateSurface(Surface::Target,
                             Option<std::shared_ptr<Surface>>&,
                             const std::shared_ptr<Surface>&);
        
    public:
        Context(OS);
        virtual bool init();

        OS getOS() const;
        bool isIOS() const;
        bool isMacOS() const;
        bool isAndroid() const;
        bool isWindows() const;
        bool isLinux() const;
        
        bool isMSAASupported() const;
        int getMaxMSAASamples() const;

    #pragma mark - Factory Methods
    
        virtual std::shared_ptr<Scene> createScene() = 0;
        virtual std::shared_ptr<Node> createNode();
        virtual std::shared_ptr<MeshNode> createMeshNode();
        virtual std::shared_ptr<Light> createLight();
        virtual std::shared_ptr<Camera> createCamera();
        virtual std::shared_ptr<Mesh> createMesh() = 0;
        virtual std::shared_ptr<Texture> createTexture() = 0;
        virtual std::shared_ptr<Surface> createSurface() = 0;
        virtual std::shared_ptr<Renderbuffer> createRenderbuffer() = 0;
        
        virtual std::shared_ptr<Node> createNode(const std::string& name);
        virtual std::shared_ptr<MeshNode> createMeshNode(const std::string& name);
        virtual std::shared_ptr<Light> createLight(const std::string& name);
        virtual std::shared_ptr<Camera> createCamera(const std::string& name);
        virtual std::shared_ptr<Texture> createTexture(Texture::Type, PixelFormat);
    
    #pragma mark - Activate
    
        void activate(const std::shared_ptr<Program>&);
        void activate(Surface::Target, const std::shared_ptr<Surface>&);
        void activate(int textureUnit, const std::shared_ptr<Texture>&);
    
    #pragma mark - Programs
        
        const std::map<std::string, std::shared_ptr<Program>>& getPrograms() const;
        const std::shared_ptr<Program>& getProgram(const std::string&) const;
        
        void loadProgram(const std::string& name,
                         const std::string& vertex,
                         const std::string& fragment);
        
        void setProgram(const std::string& name, const std::shared_ptr<Program>& program);
        void removeProgram(const std::string& name);
        virtual std::shared_ptr<Program> cloneProgram(const char* name) = 0;
        
    #pragma mark - Settings
    
        const Settings& getSettings() const;
        void applySettings(const Settings&);
    
    protected:
        void loadCurrentSettings();
        virtual Settings fetchCurrentSettings() = 0;
        
        virtual bool applyDepthTestSettings(bool) = 0;
        virtual bool applyDepthClampSettings(bool) = 0;
        virtual bool applyWriteDepthSettings(bool) = 0;
        virtual bool applySeamlessCubemapsSettings(bool) = 0;
        virtual bool applySmoothPointsSettings(bool) = 0;
        virtual bool applyCullFaceSettings(const Settings::CullFace&) = 0;
        virtual bool applyBlendSettings(const Settings::Blend&) = 0;
        virtual bool applyViewportSettings(glm::ivec4) = 0;
        virtual bool applyScissorSettings(const Settings::Scissor&) = 0;
        virtual bool applyColorMaskSettings(const Settings::ColorMask&) = 0;
    };
}

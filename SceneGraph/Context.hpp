//
//  Created by mutexre on 13/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

namespace SG
{
    class Context : public enable_shared_from_this<Context>
    {
    public:
        enum class OS {
            ios,
            macOS,
            android,
            windows,
            linux
        };
    
    protected:
        map<string, shared_ptr<Program>> programs;
        Settings settings;
        OS os;
        Option<int> maxMSAASamples;
        
        struct
        {
            Option<shared_ptr<Program>> program;

            struct {
                Option<shared_ptr<Surface>> draw, read;
            }
            surface;
            
            map<int, shared_ptr<Texture>> texture;
        }
        activeObjects;
        
    protected:
        virtual shared_ptr<Program> loadProgram(const char* vertexShaderName,
                                                const char* fragmentShaderName) = 0;
        
        void activateSurface(Surface::Target,
                             Option<shared_ptr<Surface>>&,
                             const shared_ptr<Surface>&);
        
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
    
        virtual shared_ptr<Scene> createScene() = 0;
        virtual shared_ptr<Node> createNode() = 0;
        virtual shared_ptr<MeshNode> createMeshNode() = 0;
        virtual shared_ptr<Light> createLight() = 0;
        virtual shared_ptr<Camera> createCamera() = 0;
        virtual shared_ptr<Mesh> createMesh() = 0;
        virtual shared_ptr<Texture> createTexture() = 0;
        virtual shared_ptr<Surface> createSurface() = 0;
        virtual shared_ptr<Renderbuffer> createRenderbuffer() = 0;
        virtual shared_ptr<OffScreenBuffer> createOffScreenBuffer() = 0;
        
        virtual shared_ptr<Node> createNode(const string& name);
        virtual shared_ptr<MeshNode> createMeshNode(const string& name);
        virtual shared_ptr<Light> createLight(const string& name);
        virtual shared_ptr<Camera> createCamera(const string& name);
        virtual shared_ptr<Texture> createTexture(Texture::Type, PixelFormat);
    
    #pragma mark - Activate
    
        void activate(const shared_ptr<Program>&);
        void activate(Surface::Target, const shared_ptr<Surface>&);
        void activate(int textureUnit, const shared_ptr<Texture>&);
    
    #pragma mark - Programs
        
        const map<string, shared_ptr<Program>>& getPrograms();
        const shared_ptr<Program>& getProgram(const char*);
        void loadProgram(const char* name, const char* vertex, const char* fragment);
        void addProgram(const string& name, const shared_ptr<Program>& program);
        void removeProgram(const string& name);
        virtual shared_ptr<Program> cloneProgram(const char* name) = 0;
        
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
        virtual bool applyViewportSettings(ivec4) = 0;
        virtual bool applyScissorSettings(const Settings::Scissor&) = 0;
        virtual bool applyColorMaskSettings(const Settings::ColorMask&) = 0;
    };
}

//
//  Created by mutexre on 20/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Scene : public Object,
                  public std::enable_shared_from_this<Scene>
    {
        friend class MeshNode;
        
    protected:
        std::shared_ptr<Context> context;
        std::shared_ptr<Node> root = nullptr;

        std::set<std::shared_ptr<Light>> lights;

//        unsigned lightCount = 8;

        glm::vec3 globalAmbient{ 0.f };
        std::shared_ptr<Camera> defaultCamera;
        std::shared_ptr<Node> skybox;
        
        glm::vec4 clearColor { 0, 0, 0, 1};
        float clearDepth = 0.f;

    private:
        unsigned currentLightGroup = 0;

    protected:
        virtual void setLightsOnGPU(const std::shared_ptr<Program>&,
                                    const glm::mat4& viewMatrix) = 0;

    public:
        Scene(const std::shared_ptr<Context>&);
        virtual ~Scene();

        virtual void init();

        const std::shared_ptr<Context>& getContext() const;
        void setContext(const std::shared_ptr<Context>&);

        std::shared_ptr<Node> findNode(const std::string& nodeName);

        virtual void draw(const std::shared_ptr<Camera>& = nullptr);
        
        const std::shared_ptr<Node>& getRoot() const;
        void setRoot(const std::shared_ptr<Node>&);

        void setGlobalAmbient(const glm::vec3&);
        void enableLights(bool enable = true);
        void setDefaultCamera(const std::shared_ptr<Camera>&);

        const std::shared_ptr<Node>& getSkybox() const;
        void setSkybox(const std::shared_ptr<Node>&);

        unsigned getLightCount() const;
        void setLightCount(unsigned);

        void addNode(const std::shared_ptr<Node>&, const std::shared_ptr<Node>& where = nullptr);

        std::set<std::shared_ptr<Light>> getLight(const char* name);

        void addLight(const std::shared_ptr<Light>&, const std::shared_ptr<Node>& where);
        void addLight(const std::shared_ptr<Light>&);
        void removeLight(const std::shared_ptr<Light>&);

        void animate(double time);

        unsigned newLightGroup();
    };
}

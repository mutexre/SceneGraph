//
//  Created by mutexre on 20/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Scene : public virtual Object,
                  public enable_shared_from_this<Scene>
    {
    protected:
        shared_ptr<Context> context;
        shared_ptr<Node> root = nullptr;

        list<shared_ptr<Light>> lights;

        unsigned lightCount = 8;

        vec3 globalAmbient{ 0.f };
        shared_ptr<Camera> defaultCamera;
        shared_ptr<Node> skybox;
        
        vec4 clearColor { 0, 0, 0, 1};
        float clearDepth = 0.f;

    private:
        unsigned currentLightGroup = 0;

    public:
        Scene(const shared_ptr<Context>&);
        virtual ~Scene();

        virtual void init();

        shared_ptr<Context> getContext() const;
        void setContext(const shared_ptr<Context>&);

        shared_ptr<Node> findNode(const string& nodeName);

        virtual void draw(const shared_ptr<Camera>& = nullptr);
        
        shared_ptr<Node> getRoot() const;
        void setRoot(const shared_ptr<Node>&);

        void setGlobalAmbient(const vec3&);
        virtual void setLightsOnGPU(const shared_ptr<Program>&, const mat4& viewMatrix) = 0;
        void enableLights(bool enable = true);
        void setDefaultCamera(const shared_ptr<Camera>&);

        const shared_ptr<Node>& getSkybox() const;
        void setSkybox(const shared_ptr<Node>&);

        unsigned getLightCount() const;
        void setLightCount(unsigned);

        void addNode(const shared_ptr<Node>&, const shared_ptr<Node>& where = nullptr);

        set<shared_ptr<Light>> getLight(const char* name);

        void addLight(const shared_ptr<Light>&, const shared_ptr<Node>& where);
        void addLight(const shared_ptr<Light>&);

        void animate(double time);

        unsigned newLightGroup();
    };
}

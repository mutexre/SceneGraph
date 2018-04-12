//
//  Created by mutexre on 12/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Node : public virtual Object,
                 public std::enable_shared_from_this<Node>
    {
    public:
        enum class Type {
            unknown,
            mesh,
            camera,
            light
        };

    protected:
        Type type;
        bool visible = true;
        bool visibilityInheritance;
        Option<Settings> settings;
        std::weak_ptr<Node> parent;
        std::list<std::shared_ptr<Node>> children;
        Option<std::function<void(Node*, double)>> animateFunc;
        unsigned lightGroup = 0;
        
        struct {
            glm::mat4 model, world;
        }
        matrix;
    
    protected:
        virtual void draw(const std::shared_ptr<Scene>&, const std::shared_ptr<Camera>&);

    public:
        Node();
        Node(const std::string& name);
        Node(Type, const std::string& name);

        void init();

        Type getType() const;
        Node& setType(Type);

        const std::weak_ptr<Node>& getParent() const;
        Node& setParent(const std::shared_ptr<Node>&);

        const std::list<std::shared_ptr<Node>>& getChildren() const;
        void addChild(const std::shared_ptr<Node>&);
        void insertChildAtIndex(const std::shared_ptr<Node>&, int index);
        void insertChildPriorToAnotherChild(const std::shared_ptr<Node>& node, const std::shared_ptr<Node>& another);
        void insertChildNextToAnotherChild(const std::shared_ptr<Node>& node, const std::shared_ptr<Node>& another);
        void insertFirstChild(const std::shared_ptr<Node>&);
        void insertLastChild(const std::shared_ptr<Node>&);
        void removeChild(const std::shared_ptr<Node>&);
        void removeChildAtIndex(unsigned);
        void removeAllChildren();
        void exchangeChildren(unsigned a, unsigned b);
        void sendToBack(const std::shared_ptr<Node>&);
        void bringToFront(const std::shared_ptr<Node>&);

        bool isVisible() const;
        Node& setVisible(bool visible = true);
        void toggleVisibility();

        bool inheriteVisibility() const;
        Node& setVisibilityInheritance(bool);

        const Option<Settings>& getSettings() const;
        Option<Settings>& getSettings();
        
        Node& setSettings(const Settings&);
        void removeSettings();

        const std::shared_ptr<Mesh>& getMesh() const;
        Node& setMesh(const std::shared_ptr<Mesh>&);

        void animate(double t, bool recursive = false);
        Node& setAnimation(const Option<std::function<void(Node*, double)>>&);

        const glm::mat4& getModelMatrix() const;
        glm::mat4& getModelMatrix();
        void setModelMatrix(const glm::mat4&);

        const glm::mat4& getWorldMatrix() const;
        void updateWorldMatrix();
        void updateWorldMatrixRecursively();

        unsigned getLightGroup() const;
        void setLightGroup(unsigned g);

        void traverse(const std::function<bool(std::shared_ptr<Node>&)>&);

        std::shared_ptr<Node> findSubNode(const std::string& subNodeName);

        void drawRecursively(const std::shared_ptr<Scene>&,
                             const std::shared_ptr<Camera>&,
                             Settings combinedSettings = Settings());

        void print();
    };
}

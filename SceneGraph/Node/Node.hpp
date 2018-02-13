//
//  Created by mutexre on 12/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    class Node : public virtual Object,
                 public enable_shared_from_this<Node>
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
        weak_ptr<Node> parent;
        list<shared_ptr<Node>> children;
        Option<function<void(Node*, double)>> animateFunc;
        unsigned lightGroup = 0;
        
        struct {
            mat4 model, world;
        }
        matrix;
    
    protected:
        virtual void draw(const shared_ptr<Scene>&, const shared_ptr<Camera>&);

    public:
        Node();
        Node(const string& name);
        Node(Type, const string& name);

        void init();

        Type getType() const;
        Node& setType(Type);

        const weak_ptr<Node>& getParent() const;
        Node& setParent(const shared_ptr<Node>&);

        const list<shared_ptr<Node>>& getChildren() const;
        void addChild(const shared_ptr<Node>&);
        void insertChildAtIndex(const shared_ptr<Node>&, int index);
        void insertChildPriorToAnotherChild(const shared_ptr<Node>& node, const shared_ptr<Node>& another);
        void insertChildNextToAnotherChild(const shared_ptr<Node>& node, const shared_ptr<Node>& another);
        void insertFirstChild(const shared_ptr<Node>&);
        void insertLastChild(const shared_ptr<Node>&);
        void removeChild(const shared_ptr<Node>&);
        void removeChildAtIndex(unsigned);
        void removeAllChildren();
        void exchangeChildren(unsigned a, unsigned b);
        void sendToBack(const shared_ptr<Node>&);
        void bringToFront(const shared_ptr<Node>&);

        bool isVisible() const;
        Node& setVisible(bool visible = true);
        void toggleVisibility();

        bool inheriteVisibility() const;
        Node& setVisibilityInheritance(bool);

        const Option<Settings>& getSettings() const;
        Option<Settings>& getSettings();
        
        Node& setSettings(const Settings&);
        void removeSettings();

        const shared_ptr<Mesh>& getMesh() const;
        Node& setMesh(const shared_ptr<Mesh>&);

        void animate(double t, bool recursive = false);
        Node& setAnimation(const Option<function<void(Node*, double)>>&);

        const mat4& getModelMatrix() const;
        mat4& getModelMatrix();
        void setModelMatrix(const mat4&);

        const mat4& getWorldMatrix() const;
        void updateWorldMatrix();
        void updateWorldMatrixRecursively();

        unsigned getLightGroup() const;
        void setLightGroup(unsigned g);

        void traverse(const function<bool(shared_ptr<Node>&)>&);

        shared_ptr<Node> findSubNode(const string& subNodeName);

        void drawRecursively(const shared_ptr<Scene>&,
                             const shared_ptr<Camera>&,
                             Settings combinedSettings = Settings());

        void print();
    };
}

//
//  Created by mutexre on 20/09/16.
//  Copyright © 2016 Some Organization. All rights reserved.
//

namespace SG
{
    class MeshNode : public virtual Node
    {
    protected:
        shared_ptr<Mesh> mesh;
        shared_ptr<Material> material;

    protected:
        virtual void draw(const shared_ptr<Scene>&, const shared_ptr<Camera>&) override;

    public:
        MeshNode();
        
        MeshNode(const string& name,
                 const shared_ptr<Mesh>& mesh = nullptr,
                 const shared_ptr<Material>& material = nullptr);
        
        shared_ptr<Mesh>& getMesh();
        MeshNode& setMesh(const shared_ptr<Mesh>&);
        
        shared_ptr<Material>& getMaterial();
        MeshNode& setMaterial(const shared_ptr<Material>&);
    };
}

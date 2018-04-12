//
//  Created by mutexre on 20/09/16.
//  Copyright © 2016 Some Organization. All rights reserved.
//

namespace SG
{
    class MeshNode : public Node
    {
    protected:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;

    protected:
        virtual void draw(const std::shared_ptr<Scene>&,
                          const std::shared_ptr<Camera>&) override;

    public:
        MeshNode();
        
        MeshNode(const std::string& name,
                 const std::shared_ptr<Mesh>& mesh = nullptr,
                 const std::shared_ptr<Material>& material = nullptr);
        
        const std::shared_ptr<Mesh>& getMesh() const;
        MeshNode& setMesh(const std::shared_ptr<Mesh>&);
        
        const std::shared_ptr<Material>& getMaterial() const;
        MeshNode& setMaterial(const std::shared_ptr<Material>&);
    };
}

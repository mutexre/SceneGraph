//
//  Created by mutexre on 20/09/16.
//  Copyright © 2016 Some Organization. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

MeshNode::MeshNode()
{}
    
MeshNode::MeshNode(const string& name,
                   const shared_ptr<Mesh>& mesh,
                   const shared_ptr<Material>& material)
    : Node(Node::Type::mesh, name)
{
    setMesh(mesh);
    setMaterial(material);
}

shared_ptr<Mesh>& MeshNode::getMesh() {
    return mesh;
}

MeshNode& MeshNode::setMesh(const shared_ptr<Mesh>& mesh) {
    this->mesh = mesh;
    return *this;
}

shared_ptr<Material>& MeshNode::getMaterial() {
    return material;
}

MeshNode& MeshNode::setMaterial(const shared_ptr<Material>& material) {
    this->material = material;
    return *this;
}

void MeshNode::draw(const shared_ptr<Scene>& scene, const shared_ptr<Camera>& camera)
{
    if (mesh)
    {
        auto worldNormalMatrix = inverseTranspose(mat3(matrix.world));
        auto skyboxWorldMatrix = (scene->getSkybox() ? mat3(scene->getSkybox()->getWorldMatrix()) : mat3(1.f));

        material->bind();

        if (material->isParameterActive("worldMatrix"))
            material->set("worldMatrix", matrix.world);
        
        if (material->isParameterActive("worldNormalMatrix"))
            material->set("worldNormalMatrix", worldNormalMatrix);
        
        if (material->isParameterActive("skybox.transform"))
            material->set("skybox.transform", skyboxWorldMatrix);
        
        if (material->isParameterActive("ambienceMap.transform"))
            material->set("ambienceMap.transform", skyboxWorldMatrix);
        
        if (camera)
        {
            const auto& viewMatrix = camera->getViewMatrix();
            auto worldViewMatrix = viewMatrix * matrix.world;
            auto viewNormalMatrix = inverseTranspose(mat3(worldViewMatrix));
            auto& projectionMatrix = camera->getProjectionMatrix();

            vec4 cameraWorldCoord = camera->getWorldMatrix() * vec4(0.f, 0.f, 0.f, 1.f);
            cameraWorldCoord /= cameraWorldCoord.w;
            vec3 cameraWorldCoordXYZ(cameraWorldCoord);
        
            if (material->isParameterActive("worldViewMatrix"))
                material->set("worldViewMatrix", worldViewMatrix);
            
            if (material->isParameterActive("viewNormalMatrix"))
                material->set("viewNormalMatrix", viewNormalMatrix);
            
            if (material->isParameterActive("view.matrix"))
                material->set("view.matrix", viewMatrix);
            
            if (material->isParameterActive("projectionMatrix"))
                material->set("projectionMatrix", projectionMatrix);
            
            if (material->isParameterActive("cameraWorldCoord"))
                material->set("cameraWorldCoord", 3, 1, (const float*)&cameraWorldCoordXYZ);
            
            scene->setLightsOnGPU(material->getProgram(), viewMatrix);
        }

        mesh->bind();
        mesh->draw();
    }
}

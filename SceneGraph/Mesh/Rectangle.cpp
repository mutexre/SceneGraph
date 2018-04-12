//
//  Created by mutexre on 31/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

void SG::Rect::fillVertexAttributes(shared_ptr<Mesh>& mesh, bool verticallyFlipUVs)
{
    mesh->setCoordSystem(CoordSystem::cartesian);
    
    auto& coords = mesh->getCoords();
    auto& normals = mesh->getNormals();
    auto& colors = mesh->getColors();
    auto& uvs = mesh->getUVs();
    
    coords.push_back({ -1.f, -1.f, 0.f, 1.f });
    coords.push_back({  1.f, -1.f, 0.f, 1.f });
    coords.push_back({ -1.f,  1.f, 0.f, 1.f });
    coords.push_back({  1.f,  1.f, 0.f, 1.f });
    
    normals.push_back({ 0.f, 0.f, 1.f });
    normals.push_back({ 0.f, 0.f, 1.f });
    normals.push_back({ 0.f, 0.f, 1.f });
    normals.push_back({ 0.f, 0.f, 1.f });
    
    colors.push_back({ 1.f, 1.f, 1.f, 1.f });
    colors.push_back({ 1.f, 1.f, 1.f, 1.f });
    colors.push_back({ 1.f, 1.f, 1.f, 1.f });
    colors.push_back({ 1.f, 1.f, 1.f, 1.f });
    
    if (verticallyFlipUVs)
    {
        uvs.push_back({ 0.f, 0.f });
        uvs.push_back({ 1.f, 0.f });
        uvs.push_back({ 0.f, 1.f });
        uvs.push_back({ 1.f, 1.f });
    }
    else
    {
        uvs.push_back({ 0.f, 1.f });
        uvs.push_back({ 1.f, 1.f });
        uvs.push_back({ 0.f, 0.f });
        uvs.push_back({ 1.f, 0.f });
    }
    
    mesh->invalidateCoords();
    mesh->invalidateNormals();
    mesh->invalidateColors();
    mesh->invalidateUVs();
}

void SG::Rect::fillIndices(shared_ptr<Mesh>& mesh, PrimitivesType primitivesType)
{
    auto& indices = mesh->getIndices();
    
    switch (primitivesType)
    {
        case PrimitivesType::triangles:
        {
            indices.push_back(0);
            indices.push_back(1);
            indices.push_back(2);
            
            indices.push_back(2);
            indices.push_back(1);
            indices.push_back(3);
        }
        break;
        
        case PrimitivesType::lines:
        {
            indices.push_back(0);
            indices.push_back(1);
            
            indices.push_back(1);
            indices.push_back(3);
            
            indices.push_back(3);
            indices.push_back(2);
            
            indices.push_back(2);
            indices.push_back(0);
        }
        break;
        
        default:
            throw "unknown primitives type";
    }
    
    mesh->setPrimitivesType(primitivesType);
    mesh->invalidateIndices();
}

void SG::Rect::make(shared_ptr<Mesh>& mesh,
                    PrimitivesType primitivesType,
                    bool verticallyFlipUVs)
{
    fillVertexAttributes(mesh, verticallyFlipUVs);
    fillIndices(mesh, primitivesType);
}

void SG::Rect::stroke(shared_ptr<Mesh>& mesh, bool verticallyFlipUVs)
{
    make(mesh, PrimitivesType::lines, verticallyFlipUVs);
}

void SG::Rect::fill(shared_ptr<Mesh>& mesh, bool verticallyFlipUVs)
{
    make(mesh, PrimitivesType::triangles, verticallyFlipUVs);
}

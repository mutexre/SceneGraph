//
//  Created by mutexre on 23/04/2017.
//  Copyright © 2016 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

void SG::Grid2D::fillVertexAttributes(shared_ptr<Mesh>& mesh,
                                      uvec2 dims,
                                      bool verticallyFlipUVs)
{
    mesh->setCoordSystem(CoordSystem::cartesian);
    
    float dx = 2.f / float(dims.x);
    float dy = 2.f / float(dims.y);

    float x;
    float y = -1.f;

    auto& coords = mesh->getCoords();
    auto& normals = mesh->getNormals();
    auto& uvs = mesh->getUVs();

    for (unsigned i = 0; i <= dims.y; i++)
    {
        x = -1.f;
        
        for (unsigned j = 0; j <= dims.x; j++)
        {
            coords.push_back({ x, y, 0.f, 1.f });
            normals.push_back({ 0.f, 0.f, 1.f });
            
            vec2 uv = verticallyFlipUVs ? vec2{ 0.5f * (x + 1.f), 1.f - 0.5f * (y + 1.f) } :
                                          vec2{ 0.5f * (x + 1.f), 0.5f * (y + 1.f) };
            uvs.push_back(uv);
            
            x += dx;
        }

        y += dy;
    }
    
    mesh->invalidateCoords();
    mesh->invalidateNormals();
    mesh->invalidateUVs();
}

void SG::Grid2D::fillIndices(shared_ptr<Mesh>& mesh,
                             PrimitivesType primitivesType,
                             uvec2 dims)
{
    auto& indices = mesh->getIndices();
    
    switch (primitivesType)
    {
        case PrimitivesType::triangles:
        {
            for (int i = 1; i <= dims.y; i++)
            {
                for (int j = 1; j <= dims.x; j++)
                {
                    int a = (dims.y + 1) * (i - 1) + (j - 1);
                    int b = (dims.y + 1) * i + (j - 1);
                    int c = (dims.y + 1) * i + j;
                    int d = (dims.y + 1) * (i - 1) + j;
                    
                    indices.push_back(a);
                    indices.push_back(b);
                    indices.push_back(c);
                    
                    indices.push_back(a);
                    indices.push_back(c);
                    indices.push_back(d);
                }
            }
        }
        break;
        
        case PrimitivesType::lines:
        {
            for (int i = 0; i <= dims.y; i++)
            {
                for (int j = 0; j <= dims.x; j++)
                {
                    int a = (dims.y + 1) * i + j;
                    
                    if (i < dims.y)
                    {
                        int b = (dims.y + 1) * (i + 1) + j;
                        indices.push_back(a);
                        indices.push_back(b);
                    }
                    
                    if (j < dims.x)
                    {
                        int b = (dims.y + 1) * i + (j + 1);
                        indices.push_back(a);
                        indices.push_back(b);
                    }
                }
            }
        }
        break;
        
        default:
            throw "unknown primitives type";
    }
    
    mesh->setPrimitivesType(primitivesType);
    mesh->invalidateIndices();
}

void SG::Grid2D::make(shared_ptr<Mesh>& mesh,
                      PrimitivesType primitivesType,
                      uvec2 dims,
                      bool verticallyFlipUVs)
{
    fillVertexAttributes(mesh, dims, verticallyFlipUVs);
    fillIndices(mesh, primitivesType, dims);
}

void SG::Grid2D::stroke(shared_ptr<Mesh>& mesh,
                        uvec2 dims,
                        bool verticallyFlipUVs)
{
    make(mesh, PrimitivesType::lines, dims, verticallyFlipUVs);
}

void SG::Grid2D::fill(shared_ptr<Mesh>& mesh,
                      uvec2 dims,
                      bool verticallyFlipUVs)
{
    make(mesh, PrimitivesType::triangles, dims, verticallyFlipUVs);
}

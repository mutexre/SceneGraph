//
//  Quad.cpp
//  SceneGraph
//
//  Created by mutexre on 31/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

void SG::fillRectVertexAttributes(shared_ptr<Mesh>& mesh,
                                  unsigned rows,
                                  unsigned cols,
                                  bool verticallyFlipUVs)
{
    mesh->setCoordSystem(CoordSystem::cartesian);
    
    float dx = 2.f / float(cols);
    float dy = 2.f / float(rows);

    float x;
    float y = -1.f;

    auto& coords = mesh->getCoords();
    auto& normals = mesh->getNormals();
    auto& uvs = mesh->getUVs();

    for (unsigned i = 0; i <= rows; i++)
    {
        x = -1.f;
        for (unsigned j = 0; j <= cols; j++)
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

void SG::fillRectIndices(shared_ptr<Mesh>& mesh,
                         PrimitivesType primitivesType,
                         unsigned rows,
                         unsigned cols)
{
    auto& indices = mesh->getIndices();
    
    switch (primitivesType)
    {
        case PrimitivesType::triangles:
        {
            for (int i = 1; i <= rows; i++)
            {
                for (int j = 1; j <= cols; j++)
                {
                    int a = (rows + 1) * (i - 1) + (j - 1);
                    int b = (rows + 1) * i + (j - 1);
                    int c = (rows + 1) * i + j;
                    int d = (rows + 1) * (i - 1) + j;
                    
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
            for (int i = 0; i <= rows; i++)
            {
                for (int j = 0; j <= cols; j++)
                {
                    int a = (rows + 1) * i + j;
                    
                    if (i < rows)
                    {
                        int b = (rows + 1) * (i + 1) + j;
                        indices.push_back(a);
                        indices.push_back(b);
                    }
                    
                    if (j < cols)
                    {
                        int b = (rows + 1) * i + (j + 1);
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

void SG::makeRectangles(shared_ptr<Mesh>& mesh,
                        PrimitivesType primitivesType,
                        unsigned rows,
                        unsigned cols,
                        bool verticallyFlipUVs)
{
    fillRectVertexAttributes(mesh, rows, cols, verticallyFlipUVs);
    fillRectIndices(mesh, primitivesType, rows, cols);
}

void SG::strokeRectangles(shared_ptr<Mesh>& mesh,
                          unsigned rows,
                          unsigned cols,
                          bool verticallyFlipUVs)
{
    makeRectangles(mesh, PrimitivesType::lines, rows, cols, verticallyFlipUVs);
}

void SG::fillRectangles(shared_ptr<Mesh>& mesh,
                        unsigned rows,
                        unsigned cols,
                        bool verticallyFlipUVs)
{
    makeRectangles(mesh, PrimitivesType::triangles, rows, cols, verticallyFlipUVs);
}

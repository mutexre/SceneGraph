//
//  Created by mutexre on 27/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;
using namespace std;
using namespace glm;

void SG::Cube::fillVertexAttributes(shared_ptr<Mesh>& mesh)
{
    mesh->setCoordSystem(CoordSystem::cartesian);
    
    auto& coords = mesh->getCoords();
    auto& normals = mesh->getNormals();
    auto& colors = mesh->getColors();
    auto& uvs = mesh->getUVs();
    
    coords = {
        { +1.0f, +1.0f, +1.0f, 1.0f },
        { +1.0f, +1.0f, -1.0f, 1.0f },
        { +1.0f, -1.0f, +1.0f, 1.0f },
        { +1.0f, -1.0f, -1.0f, 1.0f },
        { -1.0f, +1.0f, +1.0f, 1.0f },
        { -1.0f, +1.0f, -1.0f, 1.0f },
        { -1.0f, -1.0f, +1.0f, 1.0f },
        { -1.0f, -1.0f, -1.0f, 1.0f },
        
        { +1.0f, +1.0f, -1.0f, 1.0f },
        { +1.0f, +1.0f, +1.0f, 1.0f },
        { -1.0f, +1.0f, -1.0f, 1.0f },
        { -1.0f, +1.0f, +1.0f, 1.0f },
        { +1.0f, -1.0f, -1.0f, 1.0f },
        { +1.0f, -1.0f, +1.0f, 1.0f },
        { -1.0f, -1.0f, -1.0f, 1.0f },
        { -1.0f, -1.0f, +1.0f, 1.0f },
        
        { +1.0f, +1.0f, +1.0f, 1.0f },
        { +1.0f, -1.0f, +1.0f, 1.0f },
        { -1.0f, +1.0f, +1.0f, 1.0f },
        { -1.0f, -1.0f, +1.0f, 1.0f },
        { +1.0f, +1.0f, -1.0f, 1.0f },
        { +1.0f, -1.0f, -1.0f, 1.0f },
        { -1.0f, +1.0f, -1.0f, 1.0f },
        { -1.0f, -1.0f, -1.0f, 1.0f }
    };
    
    normals = {
        { +1.0f,  0.0f,  0.0f },
        { +1.0f,  0.0f,  0.0f },
        { +1.0f,  0.0f,  0.0f },
        { +1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        
        { 0.0f, +1.0f,  0.0f },
        { 0.0f, +1.0f,  0.0f },
        { 0.0f, +1.0f,  0.0f },
        { 0.0f, +1.0f,  0.0f },
        { 0.0f, -1.0f,  0.0f },
        { 0.0f, -1.0f,  0.0f },
        { 0.0f, -1.0f,  0.0f },
        { 0.0f, -1.0f,  0.0f },
        
        { 0.0f,  0.0f, +1.0f },
        { 0.0f,  0.0f, +1.0f },
        { 0.0f,  0.0f, +1.0f },
        { 0.0f,  0.0f, +1.0f },
        { 0.0f,  0.0f, -1.0f },
        { 0.0f,  0.0f, -1.0f },
        { 0.0f,  0.0f, -1.0f },
        { 0.0f,  0.0f, -1.0f }
    };
    
    colors = {
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f },
        { 1.f, 1.f, 1.f, 1.f }
    };
    
    uvs = {
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f }
    };
    
    mesh->invalidateCoords();
    mesh->invalidateNormals();
    mesh->invalidateColors();
    mesh->invalidateUVs();
}

void SG::Cube::fillIndices(shared_ptr<Mesh>& mesh, PrimitivesType primitivesType)
{
    auto& indices = mesh->getIndices();
    
    switch (primitivesType)
    {
        case PrimitivesType::triangles:
        {
            indices = {
                0,  1,  2,    3,  2,  1, // x+
                6,  5,  4,    5,  6,  7, // x-
                
                8,  9, 10,   11, 10,  9, // y+
                14, 13, 12,   13, 14, 15, // y-
                
                16, 17, 18,   19, 18, 17, // z+
                22, 21, 20,   21, 22, 23, // z-
            };
        }
        break;
            
        case PrimitivesType::lines:
        {
            indices = {
                0, 1,
                1, 3,
                3, 2,
                2, 0,
                
                4, 5,
                5, 7,
                7, 6,
                6, 4,
                
                0, 4,
                1, 5,
                3, 7,
                2, 6
            };
        }
        break;
            
        default:
            throw "unknown primitives type";
    }
    
    mesh->setPrimitivesType(primitivesType);
    mesh->invalidateIndices();
}

void SG::Cube::make(shared_ptr<Mesh>& mesh,
                    PrimitivesType primitivesType)
{
    fillVertexAttributes(mesh);
    fillIndices(mesh, primitivesType);
}

void SG::Cube::stroke(shared_ptr<Mesh>& mesh) {
    make(mesh, PrimitivesType::lines);
}

void SG::Cube::fill(shared_ptr<Mesh>& mesh) {
    make(mesh, PrimitivesType::triangles);
}

/*Cube::Cube(const shared_ptr<Scene>& scene, const shared_ptr<Material>& material) {
    vector<vec4> coords = {
        { +1.0f, +1.0f, +1.0f, 1.0f },
        { +1.0f, +1.0f, -1.0f, 1.0f },
        { +1.0f, -1.0f, +1.0f, 1.0f },
        { +1.0f, -1.0f, -1.0f, 1.0f },
        { -1.0f, +1.0f, +1.0f, 1.0f },
        { -1.0f, +1.0f, -1.0f, 1.0f },
        { -1.0f, -1.0f, +1.0f, 1.0f },
        { -1.0f, -1.0f, -1.0f, 1.0f },

        { +1.0f, +1.0f, -1.0f, 1.0f },
        { +1.0f, +1.0f, +1.0f, 1.0f },
        { -1.0f, +1.0f, -1.0f, 1.0f },
        { -1.0f, +1.0f, +1.0f, 1.0f },
        { +1.0f, -1.0f, -1.0f, 1.0f },
        { +1.0f, -1.0f, +1.0f, 1.0f },
        { -1.0f, -1.0f, -1.0f, 1.0f },
        { -1.0f, -1.0f, +1.0f, 1.0f },

        { +1.0f, +1.0f, +1.0f, 1.0f },
        { +1.0f, -1.0f, +1.0f, 1.0f },
        { -1.0f, +1.0f, +1.0f, 1.0f },
        { -1.0f, -1.0f, +1.0f, 1.0f },
        { +1.0f, +1.0f, -1.0f, 1.0f },
        { +1.0f, -1.0f, -1.0f, 1.0f },
        { -1.0f, +1.0f, -1.0f, 1.0f },
        { -1.0f, -1.0f, -1.0f, 1.0f }
    };

    vector<vec3> normals = {
        { +1.0f,  0.0f,  0.0f },
        { +1.0f,  0.0f,  0.0f },
        { +1.0f,  0.0f,  0.0f },
        { +1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },

        { 0.0f, +1.0f,  0.0f },
        { 0.0f, +1.0f,  0.0f },
        { 0.0f, +1.0f,  0.0f },
        { 0.0f, +1.0f,  0.0f },
        { 0.0f, -1.0f,  0.0f },
        { 0.0f, -1.0f,  0.0f },
        { 0.0f, -1.0f,  0.0f },
        { 0.0f, -1.0f,  0.0f },

        { 0.0f,  0.0f, +1.0f },
        { 0.0f,  0.0f, +1.0f },
        { 0.0f,  0.0f, +1.0f },
        { 0.0f,  0.0f, +1.0f },
        { 0.0f,  0.0f, -1.0f },
        { 0.0f,  0.0f, -1.0f },
        { 0.0f,  0.0f, -1.0f },
        { 0.0f,  0.0f, -1.0f }
    };
    for (auto& n : normals)
        n *= +1;

    vector<vec2> uvs = {
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },

        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },

        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f },
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 0.0f, 0.0f }
    };

    vector<unsigned> indices = {
         0,  1,  2,    3,  2,  1, // x+
         6,  5,  4,    5,  6,  7, // x-

         8,  9, 10,   11, 10,  9, // y+
        14, 13, 12,   13, 14, 15, // y-

        16, 17, 18,   19, 18, 17, // z+
        22, 21, 20,   21, 22, 23, // z-
    };

    auto s = scene->createSegment();
    s->setMaterial(material)
      .setIndices(indices)
      .setCoords(coords)
      .setNormals(normals)
      .setUVs(uvs)
      .setPrimitivesType(PrimitivesType::triangles)
      .update();
    
    segments.push_back(s);
}*/

//
//  CubeMesh.cpp
//  SceneGraph
//
//  Created by mutexre on 27/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "SceneGraph.hpp"

using namespace SG;

Cube::Cube(const shared_ptr<Scene>& scene, const shared_ptr<Material>& material) {
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
}

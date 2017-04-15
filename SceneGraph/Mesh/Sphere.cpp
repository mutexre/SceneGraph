//
//  Sphere.cpp
//  SceneGraph
//
//  Created by mutexre on 29/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include "SceneGraph.hpp"

using namespace SG;

Sphere::Sphere(const shared_ptr<Scene>& scene,
               const shared_ptr<Material>& material,
               unsigned m, unsigned n,
               bool sphericalCoords)
{
    vector<vec4> coords;
    vector<vec3> normals;
    vector<vec2> uvs;
    vector<unsigned> indices;

    float mInv = 1.f / float(m);
    float nInv = 1.f / float(n);
    float r = 1.f;
    float dTheta = M_PI * mInv;
    float dPhi = 2.f * M_PI * nInv;

    float st = sin(dTheta);
    float ct = cos(dTheta);
    float sp = sin(dPhi);
    float cp = cos(dPhi);

    int northPoleIndex = (m - 1) * n;
    int southPoleIndex = northPoleIndex + 1;

    float x = 0.f, z = r, theta = dTheta;
    for (unsigned i = 0; i < m - 1; i++)
    {
        float y = 0.f, phi = 0;

        auto _x = x * ct + z * st;
        auto _z = z * ct - x * st;
        x = _x;
        z = _z;

        for (unsigned j = 0; j < n; j++)
        {
            auto _x = x * cp - y * sp;
            auto _y = x * sp + y * cp;
            x = _x;
            y = _y;

            if (!sphericalCoords)
                coords.push_back({ x, y, z, 1.f });
            else
                coords.push_back({ theta, phi, r * cos(3. * theta - 4. * phi) /* cos(5 * theta)*/, 0.f });

            auto l = sqrt(x * x + y * y + z * z);
            auto invL = 1.f / l;
            auto nx = x * invL;
            auto ny = y * invL;
            auto nz = z * invL;
            normals.push_back({ nx, ny, nz });

            float u = float(i) * mInv;
            float v = float(j) * nInv;
            uvs.push_back({ u, v });

            phi += dPhi;
        }

        x = _x;
        theta += dTheta;
    }

    // north pole attributes
    if (!sphericalCoords)
        coords.push_back({ 0.f, 0.f, r, 1.f });
    else
        coords.push_back({ 0.f, 0.f, r, 0.f });

    normals.push_back({ 0.f, 0.f, 1.f });
    uvs.push_back({ 0.f, 0.f });

    // south pole attributes
    if (!sphericalCoords)
        coords.push_back({ 0.f, 0.f, -r, 1.f });
    else
        coords.push_back({ M_PI, 0.f, r, 0.f });

    normals.push_back({ 0.f, 0.f, -1.f });
    uvs.push_back({ 0.f, 1.f });

    // north pole indices
    for (unsigned i = 0; i < n; i++)
    {
        indices.push_back(northPoleIndex);
        indices.push_back(i != n - 1 ? i + 1 : 0);
        indices.push_back(i);
    }

    for (unsigned i = 0; i < m - 2; i++)
    {
        for (unsigned j = 0; j < n; j++)
        {
            int k1 = i * n;
            int k2 = k1 + n;
            int k3 = (j != n - 1 ? j + 1 : 0);

            int a = k1 + j;
            int b = k1 + k3;
            int c = k2 + k3;
            int d = k2 + j;

            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);

            indices.push_back(d);
            indices.push_back(a);
            indices.push_back(c);
        }
    }

    // south pole indices
    for (unsigned i = 0; i < n; i++)
    {
        auto zero = (m - 2) * n;
        indices.push_back(zero + i);
        indices.push_back(i != n - 1 ? zero + i + 1 : zero);
        indices.push_back(southPoleIndex);
    }

    auto s = scene->createSegment();
    s->setMaterial(material)
      .setCoords(coords)
      .setNormals(normals)
      .setUVs(uvs)
      .setIndices(indices)
      .setPrimitivesType(PrimitivesType::triangles)
      .setCoordSystem(CoordSystem::spherical);
    
    //s->calcNormals();
    s->update();
    
    segments.push_back(s);
}

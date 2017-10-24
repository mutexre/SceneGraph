//
//  Created by mutexre on 23/04/2017.
//  Copyright © 2017 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

//void SG::Cube::fillVertexAttributes(shared_ptr<Mesh>& mesh, uvec3 dims)
//{
//    float dx = 2.f / float(dims.x);
//    float dy = 2.f / float(dims.y);
//    float dz = 2.f / float(dims.z);
//
//    float x, y, z;
//
//    z = -1.f;
//
//    for (unsigned i = 0; i <= dims.z; i++)
//    {
//        y = -1.f;
//
//        for (unsigned j = 0; j <= dims.y; j++)
//        {
//            x = -1.f;
//
//            for (unsigned k = 0; k <= dims.x; k++)
//            {
//                coords.push_back({ x, y, z, 1.f });
//                x += dx;
//            }
//
//            y += dy;
//        }
//
//        z += dz;
//    }
//}
//
//void SG::Cube::fillLinesVertexAttributes(shared_ptr<Mesh>& mesh, bool splitVertices, uvec3 dims)
//{
//    float dx = 2.f / float(dims.x);
//    float dy = 2.f / float(dims.y);
//    float dz = 2.f / float(dims.z);
//
//    float x, y, z;
//
//    z = -1.f;
//
//    for (unsigned i = 0; i <= dims.z; i++)
//    {
//        y = -1.f;
//
//        for (unsigned j = 0; j <= dims.y; j++)
//        {
//            x = -1.f;
//
//            for (unsigned k = 0; k <= dims.x; k++)
//            {
//                coords.push_back({ x, y, z, 1.f });
//                normals.push_back({ 0.f, 0.f, 1.f });
//
//                x += dx;
//            }
//
//            y += dy;
//        }
//
//        z += dz;
//    }
//}
//
//void SG::Cube::fillTrianglesVertexAttributes(shared_ptr<Mesh>& mesh, uvec3 dims)
//{
//    float dx = 2.f / float(dims.x);
//    float dy = 2.f / float(dims.y);
//    float dz = 2.f / float(dims.z);
//
//    float x, y, z;
//
//    z = -1.f;
//
//    for (unsigned i = 0; i <= dims.z; i++)
//    {
//        y = -1.f;
//
//        for (unsigned j = 0; j <= dims.y; j++)
//        {
//            x = -1.f;
//
//            for (unsigned k = 0; k <= dims.x; k++)
//            {
//                coords.push_back({ x, y, z, 1.f });
//                normals.push_back({ 0.f, 0.f, 1.f });
//
//                /*vec2 uv = verticallyFlipUVs ? vec2{ 0.5f * (x + 1.f), 1.f - 0.5f * (y + 1.f) } :
//                                              vec2{ 0.5f * (x + 1.f), 0.5f * (y + 1.f) };
//                uvs.push_back(uv);*/
//
//                x += dx;
//            }
//
//            y += dy;
//        }
//
//        z += dz;
//    }
//}
//
//void SG::Cube::fillVertexAttributes(shared_ptr<Mesh>& mesh, PrimitivesType type, bool splitVertices, uvec3 dims)
//{
//    mesh->setCoordSystem(CoordSystem::cartesian);
//
//    auto& coords = mesh->getCoords();
//    auto& normals = mesh->getNormals();
//    auto& uvs = mesh->getUVs();
//
//    switch (type)
//    {
//        case PrimitivesType::points:
//            fillPointsVertexAttributes(mesh, dims);
//        break;
//
//        case PrimitivesType::lines:
//            fillLinesVertexAttributes(mesh, dims);
//        break;
//
//        case PrimitivesType::triangles:
//            fillTrianglesVertexAttributes(mesh, dims);
//        break;
//    }
//
//    mesh->invalidateCoords();
//    mesh->invalidateNormals();
//    mesh->invalidateUVs();
//}
//
//void SG::Cube::fillIndices(shared_ptr<Mesh>& mesh,
//                           PrimitivesType primitivesType,
//                           uvec3 dims)
//{
//    auto& indices = mesh->getIndices();
//
//    switch (primitivesType)
//    {
//        case PrimitivesType::triangles:
//        {
//        }
//        break;
//
//        case PrimitivesType::triangles:
//        {
//            /*for (int i = 1; i <= rows; i++)
//            {
//                for (int j = 1; j <= cols; j++)
//                {
//                    int a = (rows + 1) * (i - 1) + (j - 1);
//                    int b = (rows + 1) * i + (j - 1);
//                    int c = (rows + 1) * i + j;
//                    int d = (rows + 1) * (i - 1) + j;
//
//                    indices.push_back(a);
//                    indices.push_back(b);
//                    indices.push_back(c);
//
//                    indices.push_back(a);
//                    indices.push_back(c);
//                    indices.push_back(d);
//                }
//            }*/
//        }
//        break;
//
//        case PrimitivesType::lines:
//        {
//            /*for (int i = 0; i <= rows; i++)
//            {
//                for (int j = 0; j <= cols; j++)
//                {
//                    int a = (rows + 1) * i + j;
//
//                    if (i < rows)
//                    {
//                        int b = (rows + 1) * (i + 1) + j;
//                        indices.push_back(a);
//                        indices.push_back(b);
//                    }
//
//                    if (j < cols)
//                    {
//                        int b = (rows + 1) * i + (j + 1);
//                        indices.push_back(a);
//                        indices.push_back(b);
//                    }
//                }
//            }*/
//        }
//        break;
//
//        default:
//            throw "unknown primitives type";
//    }
//
//    mesh->setPrimitivesType(primitivesType);
//    mesh->invalidateIndices();
//}
//
//void SG::Cube::make(shared_ptr<Mesh>& mesh,
//                    PrimitivesType primitivesType,
//                    uvec3 dims)
//{
//    fillVertexAttributes(mesh, dims);
//    fillIndices(mesh, primitivesType, dims);
//}
//
//void SG::Cube::stroke(shared_ptr<Mesh>& mesh, uvec3 dims)
//{
//    make(mesh, PrimitivesType::lines);
//}
//
//void SG::Cube::fill(shared_ptr<Mesh>& mesh, uvec3 dims)
//{
//    make(mesh, PrimitivesType::triangles);
//}

//
//  Created by mutexre on 13/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <SceneGraph/SceneGraph.hpp>

using namespace SG;

Mesh::Mesh()
{}

Mesh::~Mesh()
{}

CoordSystem Mesh::getCoordSystem() const {
    return coordSystem;
}

Mesh& Mesh::setCoordSystem(CoordSystem cs) {
    coordSystem = cs;
    return *this;
}

PrimitivesType Mesh::getPrimitivesType() const {
    return primitivesType;
}

Mesh& Mesh::setPrimitivesType(PrimitivesType type) {
    primitivesType = type;
    return *this;
}

Mesh& Mesh::enableDirectMode(bool enable) {
    directMode.enabled = enable;
    return *this;
}

shared_ptr<Program>& Mesh::getProgram() {
    return program;
}

Mesh& Mesh::setProgram(const shared_ptr<Program>& program) {
    this->program = program;
    return *this;
}

vector<unsigned>& Mesh::getIndices() {
    return data.indices;
}

Mesh& Mesh::setIndices(const vector<unsigned>& v) {
    data.indices = v;
    invalidateIndices();
    return *this;
}

vector<vec4>& Mesh::getCoords() {
    return data.coords;
}

Mesh& Mesh::setCoords(const vector<vec4>& v) {
    data.coords = v;
    invalidateCoords();
    return *this;
}

vector<vec3>& Mesh::getNormals() {
    return data.normals;
}

Mesh& Mesh::setNormals(const vector<vec3>& v) {
    data.normals = v;
    invalidateNormals();
    return *this;
}

vector<vec2>& Mesh::getUVs() {
    return data.uvs;
}

Mesh& Mesh::setUVs(const vector<vec2>& v) {
    data.uvs = v;
    invalidateUVs();
    return *this;
}

void Mesh::clearIndices() {
    data.indices.clear();
}

void Mesh::clearCoords() {
    data.coords.clear();
}

void Mesh::clearNormals() {
    data.normals.clear();
}

void Mesh::clearUVs() {
    data.uvs.clear();
}

void Mesh::clearAll()
{
    clearIndices();
    clearCoords();
    clearNormals();
    clearUVs();
}

void Mesh::invalidateIndices() {
    valid.indices = false;
}

void Mesh::invalidateCoords() {
    valid.coords = false;
}

void Mesh::invalidateNormals() {
    valid.normals = false;
}

void Mesh::invalidateUVs() {
    valid.uvs = false;
}

void Mesh::invalidateAll()
{
    invalidateIndices();
    invalidateCoords();
    invalidateNormals();
    invalidateUVs();
}

Mesh& Mesh::enableNormalsArray(bool enable) {
    enabled.normals = enable;
    return *this;
}

Mesh& Mesh::enableUVsArray(bool enable) {
    enabled.uvs = enable;
    return *this;
}

vec3 sphericToCartesian(const vec3& v) {
    float theta = v.x;
    float phi = v.y;
    float r = v.z;

    float st = sin(theta);
    float ct = cos(theta);
    float cp = cos(phi);
    float sp = sin(phi);

    float x = r * st * cp;
    float y = r * st * sp;
    float z = r * ct;

    return vec3(x, y, z);
}

void Mesh::calcNormals()
{
//    normals.clear();
    auto n = data.indices.size() / 3;
    for (unsigned i = 0; i < n; i++)
    {
        auto a_i = data.indices[3 * i];
        auto b_i = data.indices[3 * i + 1];
        auto c_i = data.indices[3 * i + 2];

        vec3 a(data.coords[a_i]);
        vec3 b(data.coords[b_i]);
        vec3 c(data.coords[c_i]);

        if (coordSystem == CoordSystem::spherical) {
            a = sphericToCartesian(a);
            b = sphericToCartesian(b);
            c = sphericToCartesian(c);
        }

        vec3 v0 = b - a;
        vec3 v1 = c - a;
        vec3 normal = normalize(cross(v0, v1));

        data.normals[a_i] = normal;
        data.normals[b_i] = normal;
        data.normals[c_i] = normal;
    }
}

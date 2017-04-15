//
//  FBX.cpp
//  SceneGraph
//
//  Created by mutexre on 01/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <fbxsdk.h>
#include "SceneGraph.hpp"
#include "FbxHelper.hpp"
#include <Render/GL/GL.hpp>

namespace SG::FBX
{
    class Importer
    {
    private:
        map<FbxUInt64, Id> fbxMaterialUidMap;

    private:
        void loadMaterials(const shared_ptr<Scene>&,
                      FbxScene*,
                      map<string, shared_ptr<Program>>& programs);

        shared_ptr<Node> loadNodesRecursively(const shared_ptr<Scene>&, FbxNode*);
        void loadGlobalSettings(const shared_ptr<Scene>&, FbxScene*);

        shared_ptr<Material>
        loadMaterial(const shared_ptr<Scene>&,
                     FbxSurfaceMaterial*,
                     map<string, shared_ptr<Program>>& programs);

        shared_ptr<Camera>
        loadCamera(const shared_ptr<Scene>&, FbxCamera*);

        shared_ptr<Mesh>
        loadMesh(const shared_ptr<Scene>&, const shared_ptr<Node>&, FbxMesh*);

        shared_ptr<Node>
        loadNode(const shared_ptr<Scene>&,
                 FbxNode*);

        void setupNodeMaterials(const shared_ptr<Node>&,
                                const shared_ptr<Scene>&,
                                FbxNode*);

        void loadChildren(const shared_ptr<Node>&,
                          const shared_ptr<Scene>&,
                          FbxNode*);

        void initNode(const shared_ptr<Scene>&,
                      const shared_ptr<Node>&,
                      FbxNode*);

    public:
        bool initScene(const shared_ptr<Scene>&,
                       FbxScene*,
                       map<string, shared_ptr<Program>>& programs,
                       unsigned lightCount);
    };
}

using namespace SG;
using namespace SG::FBX;

shared_ptr<Material>
Importer::loadMaterial(const shared_ptr<Scene>& scene,
                       FbxSurfaceMaterial* fbxMaterial,
                       map<string, shared_ptr<Program>>& programs)
{
    if (fbxMaterial->GetClassId().Is(FbxSurfacePhong::ClassId)) {
        auto material = make_shared<PhongMaterial>(scene);
        auto phong = (FbxSurfacePhong*)fbxMaterial;

        material->setMode(PhongMaterial::ShadingModel::phong);

        const auto _emissive = phong->Emissive.Get();
        const auto _emissiveFactor = phong->EmissiveFactor.Get();

        material->setEmissive(_emissive[0] * _emissiveFactor,
                              _emissive[1] * _emissiveFactor,
                              _emissive[2] * _emissiveFactor);

        auto ambient = phong->Ambient.Get();
        auto ambientFactor = phong->AmbientFactor.Get();

        material->setAmbient(ambient[0] * ambientFactor,
                                        ambient[1] * ambientFactor,
                                        ambient[2] * ambientFactor);

        auto diffuse = phong->Diffuse.Get();
        auto diffuseFactor = phong->DiffuseFactor.Get();

        material->setDiffuse(diffuse[0] * diffuseFactor,
                                        diffuse[1] * diffuseFactor,
                                        diffuse[2] * diffuseFactor);

        auto specular = phong->Specular.Get();
        auto specularFactor = phong->SpecularFactor.Get();

        material->setSpecular(specular[0] * specularFactor,
                                         specular[1] * specularFactor,
                                         specular[2] * specularFactor);

        material->setOpacity(1.f - phong->TransparencyFactor.Get());
        material->setShininess(phong->Shininess.Get());
        material->setReflectivity(phong->ReflectionFactor.Get());

        material->setProgram(programs["phong"]);
        material->setName(fbxMaterial->GetName());

        return material;
    }
    else if (fbxMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
        auto material = make_shared<PhongMaterial>(scene);
        auto lambert = (FbxSurfaceLambert*)fbxMaterial;

        material->setMode(PhongMaterial::ShadingModel::lambert);

        const auto _emissive = lambert->Emissive.Get();
        const auto _emissiveFactor = lambert->EmissiveFactor.Get();

        material->setEmissive(_emissive[0] * _emissiveFactor,
                              _emissive[1] * _emissiveFactor,
                              _emissive[2] * _emissiveFactor);

        auto ambient = lambert->Ambient.Get();
        auto ambientFactor = lambert->AmbientFactor.Get();

        material->setAmbient(ambient[0] * ambientFactor,
                                        ambient[1] * ambientFactor,
                                        ambient[2] * ambientFactor);

        auto diffuse = lambert->Diffuse.Get();
        auto diffuseFactor = lambert->DiffuseFactor.Get();

        material->setDiffuse(diffuse[0] * diffuseFactor,
                                        diffuse[1] * diffuseFactor,
                                        diffuse[2] * diffuseFactor);

        material->setOpacity(1.f - lambert->TransparencyFactor.Get());

        material->setProgram(programs["lambert"]);
        material->setName(fbxMaterial->GetName());

        return material;
    }

    return nullptr;
}

shared_ptr<Camera>
Importer::loadCamera(const shared_ptr<Scene>& scene, FbxCamera* fbxCamera)
{
    auto camera = scene->createCamera();

    auto type = convert(fbxCamera->ProjectionType.Get());
    if (type) camera->setProjectionType(type.value);

    camera->setFov(fbxCamera->FieldOfView.Get());
    camera->setNear(fbxCamera->NearPlane.Get());
    camera->setFar(fbxCamera->FarPlane.Get());

    camera->updateProjectionMatrix();

    return camera;
}

shared_ptr<Mesh>
Importer::loadMesh(const shared_ptr<Scene>& scene, const shared_ptr<Node>& node, FbxMesh* fbxMesh)
{
    auto mesh = make_shared<Mesh>();

    auto polygonCount = fbxMesh->GetPolygonCount();
    const auto controlPoints = fbxMesh->GetControlPoints();

    vector<vec3> normals;
    const auto eNormal = fbxMesh->GetElementNormal();
    if (eNormal) {
        const auto& indexArray = eNormal->GetIndexArray();
        const auto& directArray = eNormal->GetDirectArray();

        switch (eNormal->GetMappingMode()) {
            case FbxLayerElement::eNone:
            case FbxLayerElement::eByControlPoint: {
                for (unsigned p = 0; p < polygonCount; p++) {
                    auto pSize = fbxMesh->GetPolygonSize(p);
                    for (unsigned v = 0; v < pSize; v++) {
                        auto cp = fbxMesh->GetPolygonVertex(p, v);

                        unsigned i;
                        switch (eNormal->GetReferenceMode()) {
                            case FbxLayerElement::eDirect: i = cp; break;
                            case FbxLayerElement::eIndexToDirect: i = indexArray.GetAt(cp); break;
                            default: break;
                        }

                        auto normal = directArray.GetAt(i);
                        normals.push_back(vec3(float(normal.mData[0]), float(normal.mData[1]), float(normal.mData[2])));
                    }
                }
            }
            break;

            case FbxLayerElement::eByPolygonVertex: {
                unsigned vertex = 0;
                for (unsigned p = 0; p < polygonCount; p++) {
                    auto pSize = fbxMesh->GetPolygonSize(p);
                    for (unsigned v = 0; v < pSize; v++) {
                        unsigned i;
                        switch (eNormal->GetReferenceMode()) {
                            case FbxLayerElement::eDirect: i = vertex; break;
                            case FbxLayerElement::eIndexToDirect: i = indexArray.GetAt(vertex); break;
                            default: break;
                        }

                        auto normal = directArray.GetAt(i);
                        normals.push_back(vec3(float(normal.mData[0]), float(normal.mData[1]), float(normal.mData[2])));

                        vertex++;
                    }
                }
            }
            break;

            case FbxLayerElement::eByPolygon:
            break;

            case FbxLayerElement::eByEdge:
            break;

            case FbxLayerElement::eAllSame:
            break;

            default: break;
        }
    }

    const auto eUV = fbxMesh->GetElementUV();
    vector<vec2> uvs;
    if (eUV) {
        const auto& indexArray = eUV->GetIndexArray();
        const auto& directArray = eUV->GetDirectArray();

        switch (eUV->GetMappingMode()) {
            case FbxLayerElement::eByControlPoint: {
                for (unsigned p = 0; p < polygonCount; p++) {
                    auto pSize = fbxMesh->GetPolygonSize(p);
                    for (unsigned v = 0; v < pSize; v++) {
                        auto cp = fbxMesh->GetPolygonVertex(p, v);

                        unsigned i;
                        switch (eUV->GetReferenceMode()) {
                            case FbxLayerElement::eDirect: i = cp; break;
                            case FbxLayerElement::eIndexToDirect: i = indexArray.GetAt(cp); break;
                            default: break;
                        }

                        auto uv = directArray.GetAt(i);
                        uvs.push_back(vec2(float(uv.mData[0]), float(uv.mData[1])));
                    }
                }
            }
            break;

            case FbxLayerElement::eByPolygonVertex: {
                unsigned vertex = 0;
                for (unsigned p = 0; p < polygonCount; p++) {
                    auto pSize = fbxMesh->GetPolygonSize(p);
                    for (unsigned v = 0; v < pSize; v++) {
    /*                    unsigned i;
                        switch (eUV->GetReferenceMode()) {
                            case FbxLayerElement::eDirect: i = vertex; break;
                            case FbxLayerElement::eIndexToDirect: i = indexArray.GetAt(vertex); break;
                            default: break;
                        }*/

                        auto uv = directArray.GetAt(fbxMesh->GetTextureUVIndex(p, v));
                        uvs.push_back(vec2(float(uv.mData[0]), float(uv.mData[1])));

                        vertex++;
                    }
                }
            }
            break;

            case FbxLayerElement::eByPolygon:
            break;

            case FbxLayerElement::eByEdge:
            break;

            case FbxLayerElement::eAllSame:
            break;

            default: break;
        }
    }

    const auto eMaterial = fbxMesh->GetElementMaterial();
    if (eMaterial) {
        const auto& indexArray = eMaterial->GetIndexArray();

        auto segmentCount = node->getMaterials().size();
        for (unsigned i = 0; i < segmentCount; i++) {
            auto s = scene->createSegment();
            const auto& m = node->getMaterials()[i];
            s->setMaterial(m);
            mesh->addSegment(s);
        }

        auto& segments = mesh->getSegments();

        vector<unsigned> segmentIndices(segmentCount);
        fill(segmentIndices.begin(), segmentIndices.end(), 0);

        unsigned vertex = 0;
        for (unsigned p = 0; p < polygonCount; p++) {
            auto materialIndex = indexArray[p];
            if (materialIndex < 0) materialIndex = 0;

            auto& segment = segments[materialIndex];
            auto& segmentIndex = segmentIndices[materialIndex];

            auto& sCoords = segment->getCoords();
            auto& sNormals = segment->getNormals();
            auto& sUV = segment->getUVs();
            auto& sIndices = segment->getIndices();

            auto pSize = fbxMesh->GetPolygonSize(p);
            for (unsigned v = 0; v < pSize; v++) {
                auto pVertex = fbxMesh->GetPolygonVertex(p, v);
                auto coord = controlPoints[pVertex];

                sCoords.push_back(vec4(float(coord.mData[0]), float(coord.mData[1]), float(coord.mData[2]), 1.0f));
                if (eNormal) sNormals.push_back(normals[vertex]);
                if (eUV) sUV.push_back(uvs[vertex]);
                sIndices.push_back(segmentIndex++);

                vertex++;
            }
        }
        
        for (auto& s : segments) s->update();
    }
    else {
    }

    return mesh;
}

void Importer::setupNodeMaterials(const shared_ptr<Node>& node,
                                  const shared_ptr<Scene>& scene,
                                  FbxNode* fbxNode)
{
    auto materialCount = fbxNode->GetMaterialCount();
    for (int i = 0; i < materialCount; i++) {
        auto uid = fbxMaterialUidMap[fbxNode->GetMaterial(i)->GetUniqueID()];
        node->addMaterial(scene->getMaterial(uid));
    }
}

shared_ptr<Node>
Importer::loadNode(const shared_ptr<Scene>& scene, FbxNode* fbxNode)
{
    auto attr = fbxNode->GetNodeAttribute();
    auto type = attr ? convert(attr->GetAttributeType()) : Node::Type::unknown;

    shared_ptr<Node> node;
    switch (type)
    {
        case Node::Type::camera:
            node = scene->createCamera();
            initNode(scene, node, fbxNode);
        break;

        case Node::Type::light:
            node = scene->createLight();
            initNode(scene, node, fbxNode);
        break;

        default:
            node = scene->createNode();
            initNode(scene, node, fbxNode);
        break;
    }

    return node;
}

void Importer::loadChildren(const shared_ptr<Node>& node,
                            const shared_ptr<Scene>& scene,
                            FbxNode* fbxNode)
{
    auto numberOfChildren = fbxNode->GetChildCount();
    for (int i = 0; i < numberOfChildren; i++) {
        auto child = loadNode(scene, fbxNode->GetChild(i));
        scene->addNode(child, node);
    }
}

void Importer::initNode(const shared_ptr<Scene>& scene,
                        const shared_ptr<Node>& node,
                        FbxNode* fbxNode)
{
    node->setName(fbxNode->GetName());

    auto attr = fbxNode->GetNodeAttribute();
    node->setType(attr ? convert(attr->GetAttributeType()) : Node::Type::unknown);

    node->setScale(convert(fbxNode->LclScaling.Get()));
    auto rotation = (2.f * M_PI / 360.f) * convert(fbxNode->LclRotation.Get());
    node->setRotate(rotation, convert(fbxNode->RotationOrder.Get()));
    node->setTranslate(convert(fbxNode->LclTranslation.Get()));
    node->updateLocalMatrix();

    setupNodeMaterials(node, scene, fbxNode);

    auto fbxMesh = fbxNode->GetMesh();
    if (fbxMesh)
        node->setMesh(loadMesh(scene, node, fbxMesh));

    loadChildren(node, scene, fbxNode);

    node->setVisible(fbxNode->Visibility.Get() != 0.0);
    node->setVisibilityInheritance(fbxNode->VisibilityInheritance.Get());
}

void Importer::loadMaterials(const shared_ptr<Scene>& scene,
                             FbxScene* fbxScene,
                             map<string, shared_ptr<Program>>& programs)
{
    auto materialCount = fbxScene->GetMaterialCount();
    for (int i = 0; i < materialCount; i++) {
        auto fbxMaterial = fbxScene->GetMaterial(i);
        auto m = loadMaterial(scene, fbxMaterial, programs);
        scene->addMaterial(m);
        fbxMaterialUidMap[fbxMaterial->GetUniqueID()] = m->getUID();
    }
}

shared_ptr<Node>
Importer::loadNodesRecursively(const shared_ptr<Scene>& scene, FbxNode* fbxNode)
{
    auto node = scene->createNode("root");
    initNode(scene, node, fbxNode);
    node->updateModelMatrix(mat4(1.0), true);
    return node;
}

void Importer::loadGlobalSettings(const shared_ptr<Scene>& scene, FbxScene* fbxScene)
{
    auto& globalSettings = fbxScene->GetGlobalSettings();

    auto c = globalSettings.GetAmbientColor();
    scene->setGlobalAmbient(vec3(c.mRed, c.mGreen, c.mBlue));

    auto defaultCameraName = globalSettings.GetDefaultCamera();
    if (defaultCameraName && !defaultCameraName.IsEmpty()) {
        auto cameras = scene->getCamera((const char*)defaultCameraName);
        if (!cameras.empty()) {
            auto camera = *cameras.begin();
            scene->setDefaultCamera(camera);
        }
    }
}

bool Importer::initScene(const shared_ptr<Scene>& scene,
                         FbxScene* fbxScene,
                         map<string, shared_ptr<Program>>& programs,
                         unsigned lightCount)
{
    auto fbxRoot = fbxScene->GetRootNode();
    if (fbxRoot) {
        scene->setLightCount(lightCount);

        loadMaterials(scene, fbxScene, programs);

        auto root = loadNodesRecursively(scene, fbxRoot);
        scene->addNode(root, nullptr);
        scene->setRoot(root);

        loadGlobalSettings(scene, fbxScene);

        return true;
    }
    return false;
}

void SG::FBX::import(shared_ptr<Scene>& scene,
                     const char* filepath,
                     map<string, shared_ptr<Program>>& programs,
                     unsigned lightCount)
{
    auto fbxManagerDeleter = [](FbxManager* sdk) {
//        if (sdk) sdk->Destroy();
    };

    unique_ptr<FbxManager, decltype(fbxManagerDeleter)> sdk{ FbxManager::Create(), fbxManagerDeleter };
    if (!sdk) throw runtime_error("FbxManager::Create() failed");

    auto fbxObjectDeleter = [](FbxObject* obj) {
        if (obj) obj->Destroy();
    };

    auto _importer = FbxImporter::Create(sdk.get(), "");
    unique_ptr<FbxImporter, decltype(fbxObjectDeleter)> importer{ _importer, fbxObjectDeleter };
    if (!importer) throw runtime_error("FbxImporter::Create() failed");

    if (!importer->Initialize(filepath, -1, sdk->GetIOSettings())) {
        string log = "FbxImporter::Initialize() failed: ";
        log += importer->GetStatus().GetErrorString();
        throw runtime_error(log);
    }

    auto fbxScene = FbxScene::Create(sdk.get(), "scene");
//    unique_ptr<FbxScene, decltype(fbxObjectDeleter)> fbxScene(_fbxScene, fbxObjectDeleter);
    importer->Import(fbxScene);

    if (!Importer().initScene(scene, fbxScene, programs, lightCount))
        throw runtime_error("FBX import: failed to initialize scene");
}

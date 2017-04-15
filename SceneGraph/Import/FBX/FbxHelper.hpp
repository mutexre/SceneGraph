//
//  FbxHelper.hpp
//  SceneGraph
//
//  Created by mutexre on 13/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

#include <fbxsdk.h>

namespace SG::FBX
{
    tvec2<double, highp> convert(const FbxDouble2&);
    tvec3<double, highp> convert(const FbxDouble3&);
    tvec4<double, highp> convert(const FbxDouble4&);

    RotationOrder convert(FbxEuler::EOrder);
    Node::Type convert(FbxNodeAttribute::EType);
    Option<Camera::ProjectionType> convert(FbxCamera::EProjectionType);

    const char* stringForMappingMode(FbxLayerElement::EMappingMode);
    const char* stringForLayerElementType(FbxLayerElement::EType);
    const char* stringForReferenceMode(FbxLayerElement::EReferenceMode);

    template <typename E>
    void printElementMappingTypes(int count, const function<E(int)>& getElementByIndex);

    void printNormalElements(FbxMesh*);
    void printBinormalElements(FbxMesh*);
    void printTangentElements(FbxMesh*);
    void printMaterialElements(FbxMesh*);
    void printPolygonGroupElements(FbxMesh*);
    void printVertexColorElements(FbxMesh*);
    void printSmoothingElements(FbxMesh*);
    void printVertexCreaseElements(FbxMesh*);
    void printEdgeCreaseElements(FbxMesh*);
    void printHoleElements(FbxMesh* mesh);
    void printVisibilityElements(FbxMesh*);
    void printUvElements(FbxMesh*);

    void printMeshInfo(FbxMesh*, bool verbose = false);
    void PrintNode(FbxNode*);
    FbxString GetAttributeTypeName(FbxNodeAttribute::EType);
    void PrintAttribute(FbxNodeAttribute*);
}

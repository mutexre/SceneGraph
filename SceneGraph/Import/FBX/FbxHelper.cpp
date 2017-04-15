//
//  FbxHelper.cpp
//  SceneGraph
//
//  Created by mutexre on 13/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#include <functional>
#include "SceneGraph.hpp"
#include "FbxHelper.hpp"

using namespace SG;

tvec2<double, highp> SG::FBX::convert(const FbxDouble2& x) {
    return tvec2<double, highp>(x[0], x[1]);
}

tvec3<double, highp> SG::FBX::convert(const FbxDouble3& x) {
    return tvec3<double, highp>(x[0], x[1], x[2]);
}

tvec4<double, highp> SG::FBX::convert(const FbxDouble4& x) {
    return tvec4<double, highp>(x[0], x[1], x[2], x[3]);
}

RotationOrder SG::FBX::convert(FbxEuler::EOrder order) {
    switch (order) {
		case FbxEuler::eOrderXYZ: return RotationOrder::xyz;
		case FbxEuler::eOrderXZY: return RotationOrder::xzy;
		case FbxEuler::eOrderYZX: return RotationOrder::yzx;
		case FbxEuler::eOrderYXZ: return RotationOrder::yxz;
		case FbxEuler::eOrderZXY: return RotationOrder::zxy;
		case FbxEuler::eOrderZYX: return RotationOrder::zyx;
        default: return RotationOrder::none;
//		eOrderSphericXYZ
	};
}

Node::Type SG::FBX::convert(FbxNodeAttribute::EType type) {
    switch (type) {
        case FbxNodeAttribute::eMesh:
            return Node::Type::mesh;

        case FbxNodeAttribute::eCamera:
            return Node::Type::camera;

        case FbxNodeAttribute::eLight:
            return Node::Type::light;

        default:
            return Node::Type::unknown;
    }
}

Option<Camera::ProjectionType> SG::FBX::convert(FbxCamera::EProjectionType type) {
    switch (type) {
        case FbxCamera::ePerspective: return Option<Camera::ProjectionType>(Camera::ProjectionType::perspective);
        case FbxCamera::eOrthogonal: return Option<Camera::ProjectionType>(Camera::ProjectionType::orthogonal);
        default: break;
    }
    return Option<Camera::ProjectionType>();
}

const char* SG::FBX::stringForLayerElementType(FbxLayerElement::EType type) {
    switch (type) {
        case FbxLayerElement::eUnknown:
            return "Unknown";

        //Non-Texture layer element types
        case FbxLayerElement::eNormal:
            return "normal";

        case FbxLayerElement::eBiNormal:
            return "bi-normal";

        case FbxLayerElement::eTangent:
            return "tangent";

        case FbxLayerElement::eMaterial:
            return "material";

        case FbxLayerElement::ePolygonGroup:
            return "polygon group";

        case FbxLayerElement::eUV:
            return "uv";

        case FbxLayerElement::eVertexColor:
            return "vertex color";

        case FbxLayerElement::eSmoothing:
            return "smoothing";

        case FbxLayerElement::eVertexCrease:
            return "vertex crease";

        case FbxLayerElement::eEdgeCrease:
            return "edge crease";

        case FbxLayerElement::eHole:
            return "hole";

        case FbxLayerElement::eUserData:
            return "user data";

        case FbxLayerElement::eVisibility:
            return "visibility";

        //Texture layer element types
        case FbxLayerElement::eTextureDiffuse:
            return "texture diffuse";

        case FbxLayerElement::eTextureDiffuseFactor:
            return "texture diffuse factor";

        case FbxLayerElement::eTextureEmissive:
            return "texture emissive";

        case FbxLayerElement::eTextureEmissiveFactor:
            return "texture emissive factor";

        case FbxLayerElement::eTextureAmbient:
            return "texture ambient";

        case FbxLayerElement::eTextureAmbientFactor:
            return "texture ambient factor";

        case FbxLayerElement::eTextureSpecular:
            return "texture specular";

        case FbxLayerElement::eTextureSpecularFactor:
            return "texture specular factor";

        case FbxLayerElement::eTextureShininess:
            return "texture shininess";

        case FbxLayerElement::eTextureNormalMap:
            return "texture normal map";

        case FbxLayerElement::eTextureBump:
            return "texture bump";

        case FbxLayerElement::eTextureTransparency:
            return "texture transparency";

        case FbxLayerElement::eTextureTransparencyFactor:
            return "texture transparency factor";

        case FbxLayerElement::eTextureReflection:
            return "texture reflection";

        case FbxLayerElement::eTextureReflectionFactor:
            return "texture reflection factor";

        case FbxLayerElement::eTextureDisplacement:
            return "texture displacement";

        case FbxLayerElement::eTextureDisplacementVector:
            return "texture displacement vector";

        default: return "";
    }
}

const char* SG::FBX::stringForMappingMode(FbxLayerElement::EMappingMode mode) {
    switch (mode) {
        case FbxLayerElement::eNone:
            return "none";

        case FbxLayerElement::eByControlPoint:
            return "by control point";

        case FbxLayerElement::eByPolygonVertex:
            return "by polygon vertex";

        case FbxLayerElement::eByPolygon:
            return "by polygon";

        case FbxLayerElement::eByEdge:
            return "by edge";

        case FbxLayerElement::eAllSame:
            return "all same";

        default: return "";
    }
}

const char* SG::FBX::stringForReferenceMode(FbxLayerElement::EReferenceMode type) {
    switch (type) {
        case FbxLayerElement::eDirect:
            return "direct";

        case FbxLayerElement::eIndex:
            return "index";

        case FbxLayerElement::eIndexToDirect:
            return "index to direct";

        default: return "";
    }
}

template <typename E>
void SG::FBX::printElementMappingTypes(int count, const function<E(int)>& getElementByIndex) {
    for (int i = 0; i < count; i++) {
        auto element = getElementByIndex(i);
        if (element) {
            auto mapMode = element->GetMappingMode();
            auto refMode = element->GetReferenceMode();
            printf("%s / %s", stringForMappingMode(mapMode), stringForReferenceMode(refMode));
            if (i < count - 1) printf(", ");
        }
    }
}

void SG::FBX::printNormalElements(FbxMesh* mesh) {
    auto count = mesh->GetElementNormalCount();
    printf("normal elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementNormal*>(count, [mesh](int i) {
            return mesh->GetElementNormal(i);
        });
    printf("\n");
}

void SG::FBX::printBinormalElements(FbxMesh* mesh) {
    auto count = mesh->GetElementBinormalCount();
    printf("bi-normal elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementBinormal*>(count, [mesh](int i) {
            return mesh->GetElementBinormal(i);
        });
    printf("\n");
}

void SG::FBX::printTangentElements(FbxMesh* mesh) {
    auto count = mesh->GetElementTangentCount();
    printf("tangent elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementTangent*>(count, [mesh](int i) {
            return mesh->GetElementTangent(i);
        });
    printf("\n");
}

void SG::FBX::printMaterialElements(FbxMesh* mesh) {
    auto count = mesh->GetElementMaterialCount();
    printf("material elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementMaterial*>(count, [mesh](int i) {
            return mesh->GetElementMaterial(i);
        });
    printf("\n");
}

void SG::FBX::printPolygonGroupElements(FbxMesh* mesh) {
    auto count = mesh->GetElementPolygonGroupCount();
    printf("polygon group elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementPolygonGroup*>(count, [mesh](int i) {
            return mesh->GetElementPolygonGroup(i);
        });
    printf("\n");
}

void SG::FBX::printVertexColorElements(FbxMesh* mesh) {
    auto count = mesh->GetElementVertexColorCount();
    printf("vertex color elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementVertexColor*>(count, [mesh](int i) {
            return mesh->GetElementVertexColor(i);
        });
    printf("\n");
}

void SG::FBX::printSmoothingElements(FbxMesh* mesh) {
    auto count = mesh->GetElementSmoothingCount();
    printf("smoothing elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementSmoothing*>(count, [mesh](int i) {
            return mesh->GetElementSmoothing(i);
        });
    printf("\n");
}

void SG::FBX::printVertexCreaseElements(FbxMesh* mesh) {
    auto count = mesh->GetElementVertexCreaseCount();
    printf("vertex crease elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementCrease*>(count, [mesh](int i) {
            return mesh->GetElementVertexCrease(i);
        });
    printf("\n");
}

void SG::FBX::printEdgeCreaseElements(FbxMesh* mesh) {
    auto count = mesh->GetElementEdgeCreaseCount();
    printf("edge crease elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementCrease*>(count, [mesh](int i) {
            return mesh->GetElementEdgeCrease(i);
        });
    printf("\n");
}

void SG::FBX::printHoleElements(FbxMesh* mesh) {
    auto count = mesh->GetElementHoleCount();
    printf("hole elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementHole*>(count, [mesh](int i) {
            return mesh->GetElementHole(i);
        });
    printf("\n");
}

void SG::FBX::printVisibilityElements(FbxMesh* mesh) {
    auto count = mesh->GetElementVisibilityCount();
    printf("visibility elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementVisibility*>(count, [mesh](int i) {
            return mesh->GetElementVisibility(i);
        });
    printf("\n");
}

void SG::FBX::printUvElements(FbxMesh* mesh) {
    auto count = mesh->GetElementUVCount();
    printf("UV elements: ");
    if (count > 0)
        printElementMappingTypes<FbxGeometryElementUV*>(count, [mesh](int i) {
            return mesh->GetElementUV(i);
        });
    printf("\n");
}

void SG::FBX::printMeshInfo(FbxMesh* mesh, bool verbose) {
    auto numberOfControlPoints = mesh->GetControlPointsCount();
    auto numberOfPolygons = mesh->GetPolygonCount();
    auto numberOfPolygonVertices = mesh->GetPolygonVertexCount();
    auto numberOfUvLayers = mesh->GetUVLayerCount();

    printf("control points: %u\n"
           "polygons: %u\n"
           "polygon vertices: %u\n"
           "UV layers: %u\n",
        numberOfControlPoints,
        numberOfPolygons,
        numberOfPolygonVertices,
        numberOfUvLayers);

    printNormalElements(mesh);
    printBinormalElements(mesh);
    printTangentElements(mesh);
    printMaterialElements(mesh);
    printPolygonGroupElements(mesh);
    printVertexColorElements(mesh);
    printSmoothingElements(mesh);
    printVertexCreaseElements(mesh);
    printEdgeCreaseElements(mesh);
    printHoleElements(mesh);
    printVisibilityElements(mesh);
    printUvElements(mesh);

    FbxStringList uvSetNameList;
    mesh->GetUVSetNames(uvSetNameList);
    for (int i = 0; i < uvSetNameList.GetCount(); i++)
    {
        const char* name = uvSetNameList.GetStringAt(i);

        const FbxGeometryElementUV* element = mesh->GetElementUV(name);
        auto mappingMode = element->GetMappingMode();
        printf("uv set: %s, mapping mode=%s\n", name, stringForMappingMode(mappingMode));
    }

    if (verbose) {
        printf("Control points:\n");
        for (int cp = 0; cp < numberOfControlPoints; cp++) {
            FbxVector4 coord = mesh->GetControlPointAt(cp);
            printf("%f %f %f\n", coord.mData[0], coord.mData[1], coord.mData[2]);
        }
        printf("\n");

/*        auto normalElement = mesh->GetElementNormal();
        if (normalElement)
        {
            printf("Normals:\n");

            auto array = normalElement->GetDirectArray();
            for (int vertex = 0; vertex < array.GetCount(); vertex++) {
                FbxVector4 normal = array.GetAt(vertex);
                printf("%f %f %f\n", normal[0], normal[1], normal[2]);
            }
        }
        printf("\n");*/

        auto uvElement = mesh->GetElementUV();
        if (uvElement)
        {
            printf("UVs:\n");

            switch (uvElement->GetMappingMode()) {
                case FbxGeometryElement::eNone: break;

                case FbxGeometryElement::eByControlPoint:
                break;

                case FbxGeometryElement::eByPolygonVertex: {
                    int vertex = 0;
                    for (int poligon = 0; poligon < numberOfPolygons; poligon++)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            FbxVector2 uv = uvElement->GetDirectArray().GetAt(vertex);
                            vertex++;
                            printf("%f %f\n", uv[0], uv[1]);
                        }
                    }
                }
                break;

                case FbxGeometryElement::eByPolygon:
                break;

                case FbxGeometryElement::eByEdge:
                break;

                case FbxGeometryElement::eAllSame:
                break;
            }

            printf("\n");
        }

        printf("Indices:\n");
        auto indices = mesh->GetPolygonVertices();
        for (int polygonVertex = 0; polygonVertex < numberOfPolygonVertices; polygonVertex++)
            printf("%u ", indices[polygonVertex]);
        printf("\n\n");

        if (numberOfUvLayers > 0) {
            printf("UV layers:\n");

            for (int layer = 0; layer < numberOfUvLayers; layer++) {
                auto uvs = mesh->GetAllChannelUV(layer);
                for (int uvIndex = 0; uvIndex < uvs.Size(); uvIndex++) {
                    auto uv = uvs[uvIndex];
                    printf("%s\n", stringForLayerElementType(uv));
                }
            }

            printf("\n");
        }
    }
}

/* Tab character ("\t") counter */
int numTabs = 0; 

/**
 * Print the required number of tabs.
 */
void PrintTabs() {
    for(int i = 0; i < numTabs; i++)
        printf("\t");
}

/**
 * Return a string-based representation based on the attribute type.
 */
FbxString SG::FBX::GetAttributeTypeName(FbxNodeAttribute::EType type) {
    switch(type) {
        case FbxNodeAttribute::eUnknown:
            return "unknown";

        case FbxNodeAttribute::eNull:
            return "null";

        case FbxNodeAttribute::eMarker:
            return "marker";

        case FbxNodeAttribute::eSkeleton:
            return "skeleton";

        case FbxNodeAttribute::eMesh:
            return "mesh";

        case FbxNodeAttribute::eNurbs:
            return "NURBs";

        case FbxNodeAttribute::ePatch:
            return "patch";

        case FbxNodeAttribute::eCamera:
            return "camera";

        case FbxNodeAttribute::eCameraStereo:
            return "stereo camera";

        case FbxNodeAttribute::eCameraSwitcher:
            return "camera switcher";

        case FbxNodeAttribute::eLight:
            return "light";

        case FbxNodeAttribute::eOpticalReference:
            return "optical reference";

        case FbxNodeAttribute::eOpticalMarker:
            return "optical marker";

        case FbxNodeAttribute::eNurbsCurve:
            return "nurbs curve";

        case FbxNodeAttribute::eTrimNurbsSurface:
            return "trim nurbs surface";

        case FbxNodeAttribute::eBoundary:
            return "boundary";

        case FbxNodeAttribute::eNurbsSurface:
            return "nurbs surface";

        case FbxNodeAttribute::eShape:
            return "shape";

        case FbxNodeAttribute::eLODGroup:
            return "LOD group";

        case FbxNodeAttribute::eSubDiv:
            return "subdiv";

        case FbxNodeAttribute::eCachedEffect:
            return "cached effect";

        case FbxNodeAttribute::eLine:
            return "line";

        default: return "unknown";
    }
}

/**
 * Print an attribute.
 */
void SG::FBX::PrintAttribute(FbxNodeAttribute* pAttribute) {
    if(!pAttribute) return;
 
    FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
    FbxString attrName = pAttribute->GetName();
    PrintTabs();
    // Note: to retrieve the chararcter array of a FbxString, use its Buffer() method.
    printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
}

/**
 * Print a node, its attributes, and all its children recursively.
 */
void SG::FBX::PrintNode(FbxNode* pNode) {
    PrintTabs();
    const char* nodeName = pNode->GetName();
    FbxDouble3 translation = pNode->LclTranslation.Get();
    FbxDouble3 rotation = pNode->LclRotation.Get();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    // print the contents of the node.
    printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n", 
        nodeName, 
        translation[0], translation[1], translation[2],
        rotation[0], rotation[1], rotation[2],
        scaling[0], scaling[1], scaling[2]
        );
    numTabs++;

    // Print the node's attributes.
    for(int i = 0; i < pNode->GetNodeAttributeCount(); i++)
        PrintAttribute(pNode->GetNodeAttributeByIndex(i));

    // Recursively print the children nodes.
    for(int j = 0; j < pNode->GetChildCount(); j++)
        PrintNode(pNode->GetChild(j));

    numTabs--;
    PrintTabs();
    printf("</node>\n");
}

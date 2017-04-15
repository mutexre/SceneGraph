//
//  SceneGraph.h
//  SceneGraph
//
//  Created by mutexre on 21/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <chrono>
#include <assert.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;
using namespace glm;

namespace SG
{
    class Object;
    class Context;
    class Scene;
    class Node;
    class MeshNode;
    class Camera;
    class Light;
    class Mesh;
    class Material;
    class Program;
    class Image;
    class Image3D;
    class ImageFX;
    class ImageFX3D;
    class Texture;
    class Transform;
    class Renderbuffer;
    class OffScreenBuffer;
    class Surface;
    
    template <typename T>
    class ImagePyramid;
    
    enum class ColorComponents;
    enum class PixelDataType;
}

#include <SceneGraph/Object.hpp>
#include <SceneGraph/Types.hpp>
#include <SceneGraph/Log.hpp>
#include <SceneGraph/Misc/Option.hpp>
#include <SceneGraph/Misc/Either.hpp>
#include <SceneGraph/Settings/Settings.hpp>
#include <SceneGraph/Texture.hpp>
#include <SceneGraph/Program.hpp>
#include <SceneGraph/Misc/Helper.hpp>
#include <SceneGraph/Misc/Text.hpp>
#include <SceneGraph/Surface/Surface.hpp>
#include <SceneGraph/Context.hpp>
#include <SceneGraph/Scene.hpp>
#include <SceneGraph/Node.hpp>
#include <SceneGraph/MeshNode.hpp>
#include <SceneGraph/Camera.hpp>
#include <SceneGraph/Light.hpp>
#include <SceneGraph/Mesh.hpp>
#include <SceneGraph/Material/Material.hpp>
#include <SceneGraph/Material/PhongMaterial.hpp>
#include <SceneGraph/Material/ColorMaterial.hpp>
#include <SceneGraph/Material/TextureMaterial.hpp>
#include <SceneGraph/Material/TextureMaterialRGBA.hpp>
#include <SceneGraph/Material/TextureMaterialYUV.hpp>
#include <SceneGraph/Material/TextureMaterialYUVA.hpp>
#include <SceneGraph/Image/Image.hpp>
#include <SceneGraph/Image/Image3D.hpp>
#include <SceneGraph/Image/ImagePyramid.hpp>
#include <SceneGraph/Mesh/Rectangle.hpp>
//#include <SceneGraph/Mesh/Cube.hpp>
//#include <SceneGraph/Mesh/Sphere.hpp>
#include <SceneGraph/Transform.hpp>
#include <SceneGraph/Surface/Renderbuffer.hpp>

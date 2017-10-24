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
    class ImageStack;
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
#include <SceneGraph/Option.hpp>
#include <SceneGraph/Either.hpp>
#include <SceneGraph/Types.hpp>
#include <SceneGraph/PixelFormat.hpp>
#include <SceneGraph/Log.hpp>
#include <SceneGraph/Settings.hpp>
#include <SceneGraph/Texture.hpp>
#include <SceneGraph/Program.hpp>
#include <SceneGraph/Helper.hpp>
#include <SceneGraph/Text.hpp>
#include <SceneGraph/Surface.hpp>
#include <SceneGraph/Context.hpp>
#include <SceneGraph/Scene.hpp>
#include <SceneGraph/Node.hpp>
#include <SceneGraph/MeshNode.hpp>
#include <SceneGraph/Camera.hpp>
#include <SceneGraph/Light.hpp>
#include <SceneGraph/Mesh.hpp>
#include <SceneGraph/Material.hpp>
#include <SceneGraph/ColorMaterial.hpp>
#include <SceneGraph/TextureMaterial.hpp>
#include <SceneGraph/TextureMaterialRGBA.hpp>
#include <SceneGraph/TextureMaterialYUV.hpp>
#include <SceneGraph/TextureMaterialYUVA.hpp>
#include <SceneGraph/PhongMaterial.hpp>
#include <SceneGraph/SkyboxMaterial.hpp>
#include <SceneGraph/Image.hpp>
#include <SceneGraph/ImageStack.hpp>
#include <SceneGraph/ImagePyramid.hpp>
#include <SceneGraph/Rectangle.hpp>
#include <SceneGraph/Cube.hpp>
#include <SceneGraph/Grid2D.hpp>
#include <SceneGraph/Grid3D.hpp>
//#include <SceneGraph/Sphere.hpp>
#include <SceneGraph/Transform.hpp>
#include <SceneGraph/Renderbuffer.hpp>

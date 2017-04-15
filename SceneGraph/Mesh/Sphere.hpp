//
//  Sphere.hpp
//  SceneGraph
//
//  Created by mutexre on 29/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG
{
    class Sphere : public Mesh
    {
    public:
        Sphere(const shared_ptr<Scene>&,
               const shared_ptr<Material>&,
               unsigned m, unsigned n,
               bool sphericalCoords = false);
    };
}

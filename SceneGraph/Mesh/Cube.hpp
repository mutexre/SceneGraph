//
//  CubeMesh.hpp
//  SceneGraph
//
//  Created by mutexre on 27/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG
{
    class Cube : public Mesh
    {
    public:
        Cube(const shared_ptr<Scene>&, const shared_ptr<Material>&);
    };
}

//
//  Created by mutexre on 27/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG::Cube
{
    void fillVertexAttributes(shared_ptr<Mesh>&, PrimitivesType, uvec3 dims);

    void fillIndices(shared_ptr<Mesh>&,
                     PrimitivesType,
                     uvec3 dims = uvec3(1));

    void make(shared_ptr<Mesh>&,
              PrimitivesType,
              uvec3 dims = uvec3(1));
    
    void stroke(shared_ptr<Mesh>&, uvec3 dims = uvec3(1));
    void fill(shared_ptr<Mesh>&, uvec3 dims = uvec3(1));
}

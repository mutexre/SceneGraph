//
//  Created by mutexre on 23/04/2017.
//  Copyright © 2016 mutexre. All rights reserved.
//

#pragma once

namespace SG::Grid2D
{
    void fillVertexAttributes(shared_ptr<Mesh>&,
                              uvec2 dims = uvec2(1),
                              bool verticallyFlipUVs = true);

    void fillIndices(shared_ptr<Mesh>&,
                     PrimitivesType,
                     uvec2 dims = uvec2(1));

    void make(shared_ptr<Mesh>&,
              PrimitivesType,
              uvec2 dims = uvec2(1),
              bool verticallyFlipUVs = true);
    
    void stroke(shared_ptr<Mesh>&,
                uvec2 dims = uvec2(1),
                bool verticallyFlipUVs = true);
    
    void fill(shared_ptr<Mesh>&,
              uvec2 dims = uvec2(1),
              bool verticallyFlipUVs = true);
}

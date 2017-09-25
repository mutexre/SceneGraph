//
//  Created by mutexre on 31/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG::Rect
{
    void fillVertexAttributes(shared_ptr<Mesh>&, bool verticallyFlipUVs = true);

    void fillIndices(shared_ptr<Mesh>&, PrimitivesType);

    void make(shared_ptr<Mesh>&,
              PrimitivesType,
              bool verticallyFlipUVs = true);
    
    void stroke(shared_ptr<Mesh>&, bool verticallyFlipUVs = true);
    
    void fill(shared_ptr<Mesh>&, bool verticallyFlipUVs = true);
}

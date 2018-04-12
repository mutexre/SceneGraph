//
//  Created by mutexre on 31/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG::Rect
{
    void fillVertexAttributes(std::shared_ptr<Mesh>&, bool verticallyFlipUVs = true);

    void fillIndices(std::shared_ptr<Mesh>&, PrimitivesType);

    void make(std::shared_ptr<Mesh>&,
              PrimitivesType,
              bool verticallyFlipUVs = true);
    
    void stroke(std::shared_ptr<Mesh>&, bool verticallyFlipUVs = true);
    
    void fill(std::shared_ptr<Mesh>&, bool verticallyFlipUVs = true);
}

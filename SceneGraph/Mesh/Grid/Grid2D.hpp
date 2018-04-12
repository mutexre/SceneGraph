//
//  Created by mutexre on 23/04/2017.
//  Copyright © 2016 mutexre. All rights reserved.
//

#pragma once

namespace SG::Grid2D
{
    void fillVertexAttributes(std::shared_ptr<Mesh>&,
                              glm::uvec2 dims = glm::uvec2(1),
                              bool verticallyFlipUVs = true);

    void fillIndices(std::shared_ptr<Mesh>&,
                     PrimitivesType,
                     glm::uvec2 dims = glm::uvec2(1));

    void make(std::shared_ptr<Mesh>&,
              PrimitivesType,
              glm::uvec2 dims = glm::uvec2(1),
              bool verticallyFlipUVs = true);
    
    void stroke(std::shared_ptr<Mesh>&,
                glm::uvec2 dims = glm::uvec2(1),
                bool verticallyFlipUVs = true);
    
    void fill(std::shared_ptr<Mesh>&,
              glm::uvec2 dims = glm::uvec2(1),
              bool verticallyFlipUVs = true);
}

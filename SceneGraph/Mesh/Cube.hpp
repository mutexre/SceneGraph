//
//  Created by mutexre on 27/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG::Cube
{
    void fillVertexAttributes(std::shared_ptr<Mesh>&);
    void fillIndices(std::shared_ptr<Mesh>&, PrimitivesType);
    void make(std::shared_ptr<Mesh>&, PrimitivesType);
    
    void stroke(std::shared_ptr<Mesh>&);
    void fill(std::shared_ptr<Mesh>&);
}

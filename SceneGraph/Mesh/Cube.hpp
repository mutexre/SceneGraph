//
//  Created by mutexre on 27/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG::Cube
{
    void fillVertexAttributes(shared_ptr<Mesh>&);
    void fillIndices(shared_ptr<Mesh>&, PrimitivesType);
    void make(shared_ptr<Mesh>&, PrimitivesType);
    
    void stroke(shared_ptr<Mesh>&);
    void fill(shared_ptr<Mesh>&);
}

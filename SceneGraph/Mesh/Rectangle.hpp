//
//  Quad.hpp
//  SceneGraph
//
//  Created by mutexre on 31/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG
{
    void fillRectVertexAttributes(shared_ptr<Mesh>&,
                                  unsigned rows = 1,
                                  unsigned cols = 1,
                                  bool verticallyFlipUVs = true);

    void fillRectIndices(shared_ptr<Mesh>&,
                         PrimitivesType,
                         unsigned rows = 1,
                         unsigned cols = 1);

    void makeRectangles(shared_ptr<Mesh>&,
                        PrimitivesType,
                        unsigned rows = 1,
                        unsigned cols = 1,
                        bool verticallyFlipUVs = true);
    
    void strokeRectangles(shared_ptr<Mesh>&,
                          unsigned rows = 1,
                          unsigned cols = 1,
                          bool verticallyFlipUVs = true);
    
    void fillRectangles(shared_ptr<Mesh>&,
                        unsigned rows = 1,
                        unsigned cols = 1,
                        bool verticallyFlipUVs = true);
}

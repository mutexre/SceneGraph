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
    void fillEllipseVertexAttributes(shared_ptr<Mesh>&,
                                     float a, float b,
                                     unsigned pointsCount);

    void fillEllipseIndices(shared_ptr<Mesh>&,
                            PrimitivesType,
                            unsigned pointsCount);

    void makeEllipse(shared_ptr<Mesh>&,
                     PrimitivesType,
                     float a, float b,
                     unsigned pointsCount);
    
    void strokeEllipse(shared_ptr<Mesh>&,
                       float a, float b,
                       unsigned pointsCount);
    
    void fillEllipse(shared_ptr<Mesh>&,
                     float a, float b,
                     unsigned pointsCount);
}

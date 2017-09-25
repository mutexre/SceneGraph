//
//  Created by mutexre on 07/01/16.
//  Copyright © 2016 mutexre. All rights reserved.
//

#pragma once

namespace SG::Assimp
{
    shared_ptr<Scene>
    import(const char* filepath,
           map<string, shared_ptr<Program>>& programs,
           unsigned lightCount);
}

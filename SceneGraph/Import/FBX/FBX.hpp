//
//  Created by mutexre on 01/11/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

#pragma once

namespace SG::FBX
{
    void import(shared_ptr<Scene>&,
                const char* filepath,
                map<string, shared_ptr<Program>>& programs,
                unsigned lightCount);
}

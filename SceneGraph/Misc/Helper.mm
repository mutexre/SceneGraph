//
//  Created by mutexre on 01/02/2017.
//  Copyright © 2017 Some Organization. All rights reserved.
//

#import <SceneGraph/SceneGraph.hpp>
#import <Foundation/Foundation.h>

double SG::getTime() {
    return [[NSProcessInfo processInfo] systemUptime];
}

//
//  Created by mutexre on 22/04/2017.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    struct PixelFormat_
    {
        enum class Component : int
        {
            red = 0, green, blue, alpha,
            depth, stencil,
            luminance
        };
        
        struct Range
        {
            enum class Type {
                fixed, fixed_snorm,
                fp, fp_mantissa, fp_exponent,
                i, ui,
                pad
            };
            
            Type type;
            int size;
        };
        
        std::vector<Range> ranges;
        std::vector<int> rangeOffsets;
        int components = 0;
        std::map<Component, int> componentRanges;
        
        bool hasComponent(Component c)
        {
            return components & int(c);
        }
        
        Option<int> getComponent(Component c)
        {
            if (components & int(c))
                return componentRanges[c];
            
            return Option<int>();
        }
        
        void setComponent(Component c, int range)
        {
            components |= int(c);
            componentRanges[c] = range;
        }
        
        void removeComponent(Component c)
        {
            components &= ~ int(c);
            componentRanges.erase(c);
        }
    };
}

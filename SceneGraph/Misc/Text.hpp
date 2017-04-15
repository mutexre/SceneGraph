//
//  Text.hpp
//  sensee
//
//  Created by mutexre on 12/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

namespace SG
{
    vec2 getTextRectSize(const char* text,
                         const char* fontName,
                         float fontSize,
                         float maxWidth = 0,
                         float maxHeight = 0);

    vector<char>
    createTextBitmap(const char* text,
                     const char* fontName,
                     float fontSize,
                     vec4 backgroundColor,
                     vec4 fontColor,
                     unsigned w, unsigned h);
    
    shared_ptr<Texture>
    createTextureFromText(const char* text,
                          const char* fontName,
                          float fontSize,
                          vec4 backgroundColor,
                          vec4 fontColor,
                          unsigned w, unsigned h,
                          const shared_ptr<Context>&);
}

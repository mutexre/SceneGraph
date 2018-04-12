//
//  Created by mutexre on 12/10/2016.
//  Copyright © 2016 Some Organization. All rights reserved.
//

namespace SG
{
    glm::vec2
    getTextRectSize(const char* text,
                    const char* fontName,
                    float fontSize,
                    float maxWidth = 0,
                    float maxHeight = 0);

    std::vector<char>
    createTextBitmap(const char* text,
                     const char* fontName,
                     float fontSize,
                     glm::vec4 backgroundColor,
                     glm::vec4 fontColor,
                     unsigned w, unsigned h);
    
    std::shared_ptr<Texture>
    createTextureFromText(const char* text,
                          const char* fontName,
                          float fontSize,
                          glm::vec4 backgroundColor,
                          glm::vec4 fontColor,
                          unsigned w, unsigned h,
                          const std::shared_ptr<Context>&);
}

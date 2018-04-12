//
//  Created by mutexre on 06/10/16.
//  Copyright © 2016 Some Organization. All rights reserved.
//

namespace SG
{
    struct Settings
    {
    public:
        struct CullFace
        {
        public:
            enum class Mode {
                front, back, frontAndBack
            };
            
            Option<bool> enabled;
            Option<Mode> mode;
        
        public:
            CullFace();
            CullFace(Mode);
            
            void enable(Mode);
            void disable();
            
            bool operator==(const CullFace&) const;
            bool operator!=(const CullFace&) const;
        };
        
        struct Blend
        {
        public:
            enum class Func
            {
                zero, one,
                srcColor, dstColor,
                srcAlpha, dstAlpha,
                oneMinusSrcColor, oneMinusDstColor,
                oneMinusSrcAlpha, oneMinusDstAlpha,
                srcAlphaSaturate,
                constColor,
                oneMinusConstColor,
                constAlpha,
                oneMinusConstAlpha
            };

            enum class Equation {
                add, subtract, reverseSubtract, min, max
            };
        
        public:
            Option<bool> enabled;
            Option<glm::vec4> color;
            
            bool separate;
            
            struct {
                Option<Func> srcRGB, dstRGB;
                Option<Func> srcAlpha, dstAlpha;
            }
            func;
            
            struct {
                Option<Equation> rgb, alpha;
            }
            equation;
            
        public:
            Blend();
            
            Blend(Func src, Func dst,
                  Equation eq = Equation::add,
                  glm::vec4 color = { 1, 1, 1, 1 });
            
            Blend(Func srcRGB, Func srcAlpha,
                  Func dstRGB, Func dstAlpha,
                  Equation eqRGB = Equation::add,
                  Equation eqAlpha = Equation::add,
                  glm::vec4 color = { 1, 1, 1, 1 });
            
            void disable();
            
            bool operator==(const Blend&) const;
            bool operator!=(const Blend&) const;
        };
        
        struct Scissor
        {
            Option<bool> enabled;
            Option<glm::ivec4> rect;
            
            Scissor();
            Scissor(glm::ivec4);
            Scissor(unsigned x, unsigned y, unsigned w, unsigned h);
            
            void disable();
            void enable(glm::ivec4);
            void enable(unsigned x, unsigned y, unsigned w, unsigned h);
            
            bool operator==(const Scissor&) const;
            bool operator!=(const Scissor&) const;
        };
        
        struct ColorMask
        {
            bool r, g, b, a;
            ColorMask(bool r = true, bool g = true, bool b = true, bool a = true);
            
            bool operator==(const ColorMask&) const;
            bool operator!=(const ColorMask&) const;
        };
    
    public:
        Option<bool> depthTest;
        Option<bool> depthClamp;
        Option<bool> writeDepth;
        Option<bool> seamlessCubemaps;
        Option<bool> smoothPoints;
        Option<CullFace> cullFace;
        Option<Blend> blend;
        Option<glm::ivec4> viewport;
        Option<Scissor> scissor;
        //Option<Stencil> stencil;
        Option<ColorMask> colorMask;
    
    public:
        void apply(const Settings&);
    };
}

//
//  Created by mutexre on 21/10/15.
//  Copyright © 2015 mutexre. All rights reserved.
//

namespace SG
{
    enum class OS {
        ios,
        macOS,
        android,
        windows,
        linux
    };
    
    enum class CoordSystem {
        cartesian,
        spherical,
        cylindrical
    };
    
    enum class PrimitivesType {
        points = 0, lines, triangles
    };
    
    enum class BufferBit : int
    {
        color   = 1 << 0,
        depth   = 1 << 1,
        accum   = 1 << 2,
        stencil = 1 << 3
    };
    
    enum class ColorComponents
    {
        red, green, blue, alpha,
        rg,
        rgb, bgr,
        rgba, bgra,
        luminance, luminance_alpha,
        stencil, depth, depth_stencil
    };

    enum class PixelDataType
    {
        u8, s8,
        u16, s16,
        u32, s32,
        f16, f32,
        snorm8, snorm16,
        u332, u233_rev,
        u565, u565_rev,
        u4444, u4444_rev,
        u5551, u1555_rev,
        u8888, u8888_rev,
        u10_10_10_2, u2_10_10_10_rev,
        u24_u8, f32_u8,
        f11_f11_f10,
        f9_9_9_5,
        f5_9_9_9_rev
    };

    enum class PixelFormat
    {
    // R
        r8, r8i, r8ui, r8_snorm,      // 8-bit
        r16i, r16ui, r16f, r16_snorm, // 16-bit
        r32i, r32ui, r32f,            // 32-bit
        
    // RG
        rg8, rg8i, rg8ui, rg8_snorm,      //  8-bit per component
        rg16, rg16i, rg16ui, rg16f, rg16_snorm, // 16-bit per component
        rg32i, rg32ui, rg32f,             // 32-bit per component
        
    // RGB
        rgb8, srgb8, rgb8i, rgb8ui, rgb8_snorm,    //  8-bit per component
        rgb16i, rgb16ui, rgb16f, rgb16_snorm,      // 16-bit per component
        rgb32i, rgb32ui, rgb32f,                   // 32-bit per component
        rgb4, rgb5, rgb10, rgb12,
        r3_g3_b2, rgb565, r11f_g11f_b10f, rgb9_e5,
        
    // RGBA
        rgba8, srgb8_alpha8, rgba8i, rgba8ui, rgba8_snorm, //  8-bit per component
        rgba16i, rgba16ui, rgba16f, rgba16_snorm,          // 16-bit per component
        rgba32i, rgba32ui, rgba32f,                        // 32-bit per component
        rgba2, rgba4, rgb5_a1, rgb10_a2, rgb10_a2_ui,
        
    // Other
        alpha,
        luminance,
        luminance_alpha,
        depth16, depth24, depth32, depth32f,
        depth24_stencil8, depth32f_stencil8
    };
}

namespace SG
{
    enum class CoordSystem {
        cartesian,
        spherical,
        cylindrical
    };
    
    enum class PrimitivesType {
        points, lines, triangles
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
        snorm8,
        u332, u233_rev,
        u565, u565_rev,
        u4444, u4444_rev,
        u5551, u1555_rev,
        u8888, u8888_rev,
        u10_10_10_2, u2_10_10_10_rev,
        u24_8,
        f11_f11_f10,
        f5_9_9_9_rev
    };

    enum class PixelFormat
    {
        r8, r8_snorm, r16f, r32f, r8i, r8ui, r16i, r16ui, r32i, r32ui,
        rg8, rg8_snorm, rg16f, rg32f, rg8i, rg8ui, rg16i, rg16ui, rg32i, rg32ui,
        rgb8, rgb8_snorm, rgb565, srgb8, rgb16f, rgb32f, r11f_g11f_b10f, rgb9_e5, rgb8i, rgb8ui, rgb16i, rgb16ui, rgb32i, rgb32ui,
        rgba4, rgb5_a1, rgba8, rgba8_snorm, rgb10_a2, rgb10_a2ui, srgb8_alpha8, rgba16f, rgba32f, rgba8i, rgba8ui, rgba16i, rgba16ui, rgba32i, rgba32ui,
        alpha,
        luminance,
        luminance_alpha
    };
}

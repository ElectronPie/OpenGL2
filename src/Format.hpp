#pragma once

#include "Renderer.hpp"

enum class ImageFormat
{
    RGB = GL_RGB,

    RGB4 = GL_RGB4,

    RGB5 = GL_RGB5,

    RGB8      = GL_RGB8,
    RGB8snorm = GL_RGB8_SNORM,
    RGB8i     = GL_RGB8I,
    RGB8ui    = GL_RGB8UI,

    RGB12 = GL_RGB12,

    RGB16      = GL_RGB16,
    RGB16snorm = GL_RGB16_SNORM,
    RGB16i     = GL_RGB16I,
    RGB16ui    = GL_RGB16UI,
    RGB16f     = GL_RGB16F,

    RGB32i  = GL_RGB32I,
    RGB32ui = GL_RGB32UI,
    RGB32f  = GL_RGB32F,

    RGBA = GL_RGBA,

    RGBA2 = GL_RGBA2,

    RGBA4 = GL_RGBA4,

    RGBA8      = GL_RGBA8,
    RGBA8snorm = GL_RGBA8_SNORM,
    RGBA8i     = GL_RGBA8I,
    RGBA8ui    = GL_RGBA8UI,

    RGBA12 = GL_RGBA12,

    RGBA16      = GL_RGBA16,
    RGBA16snorm = GL_RGBA16_SNORM,
    RGBA16i     = GL_RGBA16I,
    RGBA16ui    = GL_RGBA16UI,
    RGBA16f     = GL_RGBA16F,

    RGBA32i  = GL_RGBA32I,
    RGBA32ui = GL_RGBA32UI,
    RGBA32f  = GL_RGBA32F,

    R3G3B2       = GL_R3_G3_B2,
    R11fG11fB10f = GL_R11F_G11F_B10F,
    RGB9E5       = GL_RGB9_E5,
    RGB565       = GL_RGB565,
    RGB5A1       = GL_RGB5_A1,
    RGB10A2      = GL_RGB10_A2,
    RGB10A2ui    = GL_RGB10_A2UI,

    SRGB8   = GL_SRGB8,
    SRGB8A8 = GL_SRGB8_ALPHA8,

    CompressedRed   = GL_COMPRESSED_RED,
    CompressedRG    = GL_COMPRESSED_RG,
    CompressedRGB   = GL_COMPRESSED_RGB,
    CompressedRGBA  = GL_COMPRESSED_RGBA,
    CompressedSRGB  = GL_COMPRESSED_SRGB,
    CompressedSRGBA = GL_COMPRESSED_SRGB_ALPHA,

    CompressedRedRGTC1       = GL_COMPRESSED_RED_RGTC1,
    CompressedSignedRedRGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
    CompressedRGRGTC2        = GL_COMPRESSED_RG_RGTC2,
    CompressedSignedRGRGTC2  = GL_COMPRESSED_SIGNED_RG_RGTC2,

    CompressedRGBABPTCunorm  = GL_COMPRESSED_RGBA_BPTC_UNORM,
    CompressedSRGBABPTCunorm = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
    CompressedRGBBPTCsf      = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
    CompressedRGBBPTCuf      = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,

    Depth    = GL_DEPTH_COMPONENT,
    Depth16  = GL_DEPTH_COMPONENT16,
    Depth24  = GL_DEPTH_COMPONENT24,
    Depth32  = GL_DEPTH_COMPONENT32,
    Depth32f = GL_DEPTH_COMPONENT32F,

    DepthStencil     = GL_DEPTH_STENCIL,
    Depth24Stencil8  = GL_DEPTH24_STENCIL8,
    Depth32fStencil8 = GL_DEPTH32F_STENCIL8,
};

enum class DataType
{
    UByte             = GL_UNSIGNED_BYTE,
    UShort            = GL_UNSIGNED_SHORT,
    Short             = GL_SHORT,
    UInt              = GL_UNSIGNED_INT,
    Int               = GL_INT,
    Float             = GL_FLOAT,
    UByte3_3_2        = GL_UNSIGNED_BYTE_3_3_2,
    UByte2_3_3Rev     = GL_UNSIGNED_BYTE_2_3_3_REV,
    UShort5_6_5       = GL_UNSIGNED_SHORT_5_6_5,
    UShort5_6_5Rev    = GL_UNSIGNED_SHORT_5_6_5_REV,
    UShort4_4_4_4     = GL_UNSIGNED_SHORT_4_4_4_4,
    UShort4_4_4_4Rev  = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    UShort5_5_5_1     = GL_UNSIGNED_SHORT_5_5_5_1,
    UShort1_5_5_5Rev  = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    UInt8_8_8_8       = GL_UNSIGNED_INT_8_8_8_8,
    UInt8_8_8_8Rev    = GL_UNSIGNED_INT_8_8_8_8_REV,
    UInt10_10_10_2    = GL_UNSIGNED_INT_10_10_10_2,
    UInt2_10_10_10Rev = GL_UNSIGNED_INT_2_10_10_10_REV,

    UInt24_8 = GL_UNSIGNED_INT_24_8,
};

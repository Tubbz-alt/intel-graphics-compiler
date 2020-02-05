/*===================== begin_copyright_notice ==================================

Copyright (c) 2017 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


======================= end_copyright_notice ==================================*/
#pragma once

#include "inc/common/Compiler/API/SurfaceFormats.h"
#include "../Platform/cmd_media_enum_g8.h"
#include "../Platform/cmd_shared_enum_g8.h"
#include "patch_list.h"
#include "../CommandStream/SamplerTypes.h"
#include "../CommandStream/SurfaceTypes.h"

namespace iOpenCL
{

/*****************************************************************************\
CONST: g_cConvertSamplerTextureAddressMode
\*****************************************************************************/
static const G6HWC::GFXSHAREDSTATE_TEXCOORDMODE g_cConvertSamplerTextureAddressMode[] =
{
    G6HWC::GFXSHAREDSTATE_TEXCOORDMODE_WRAP,            // SAMPLER_TEXTURE_ADDRESS_MODE_WRAP
    G6HWC::GFXSHAREDSTATE_TEXCOORDMODE_MIRROR,          // SAMPLER_TEXTURE_ADDRESS_MODE_MIRROR
    G6HWC::GFXSHAREDSTATE_TEXCOORDMODE_CLAMP,           // SAMPLER_TEXTURE_ADDRESS_MODE_CLAMP
    G6HWC::GFXSHAREDSTATE_TEXCOORDMODE_CLAMP_BORDER,    // SAMPLER_TEXTURE_ADDRESS_MODE_BORDER
    G6HWC::GFXSHAREDSTATE_TEXCOORDMODE_MIRROR_ONCE,      // SAMPLER_TEXTURE_ADDRESS_MODE_MIRRORONCE
    G6HWC::GFXSHAREDSTATE_TEXCOORDMODE_MIRROR_101      // SAMPLER_TEXTURE_ADDRESS_MODE_MIRROR101
};

C_ASSERT( sizeof(g_cConvertSamplerTextureAddressMode) ==
    sizeof(G6HWC::GFXSHAREDSTATE_TEXCOORDMODE) * NUM_SAMPLER_TEXTURE_ADDRESS_MODES );

/*****************************************************************************\
CONST: g_cConvertSamplerMapFilter
\*****************************************************************************/
static const G6HWC::GFXSHAREDSTATE_MAPFILTER g_cConvertSamplerMapFilter[] =
{
    G6HWC::GFXSHAREDSTATE_MAPFILTER_NEAREST,        // SAMPLER_MAPFILTER_POINT
    G6HWC::GFXSHAREDSTATE_MAPFILTER_LINEAR,         // SAMPLER_MAPFILTER_LINEAR
    G6HWC::GFXSHAREDSTATE_MAPFILTER_ANISOTROPIC,    // SAMPLER_MAPFILTER_ANISOTROPIC
    G6HWC::GFXSHAREDSTATE_MAPFILTER_NEAREST,        // SAMPLER_MAPFILTER_GAUSSIANQUAD
    G6HWC::GFXSHAREDSTATE_MAPFILTER_NEAREST,        // SAMPLER_MAPFILTER_PYRAMIDALQUAD
    G6HWC::GFXSHAREDSTATE_MAPFILTER_MONO            // SAMPLER_MAPFILTER_MONO
};

C_ASSERT( sizeof(g_cConvertSamplerMapFilter) ==
    sizeof(G6HWC::GFXSHAREDSTATE_MAPFILTER) * NUM_SAMPLER_MAPFILTER_TYPES );

/*****************************************************************************\
CONST: g_cConvertSamplerMipFilter
\*****************************************************************************/
static const G6HWC::GFXSHAREDSTATE_MIPFILTER g_cConvertSamplerMipFilter[] =
{
    G6HWC::GFXSHAREDSTATE_MIPFILTER_NEAREST,        // SAMPLER_MIPFILTER_POINT
    G6HWC::GFXSHAREDSTATE_MIPFILTER_LINEAR,         // SAMPLER_MIPFILTER_LINEAR
    G6HWC::GFXSHAREDSTATE_MIPFILTER_NONE            // SAMPLER_MIPFILTER_NONE
};

C_ASSERT(sizeof(g_cConvertSamplerMipFilter) ==
    sizeof(G6HWC::GFXSHAREDSTATE_MAPFILTER) * NUM_SAMPLER_MIPFILTER_TYPES);

/*****************************************************************************\
CONST: g_cConvertCompareFunc
\*****************************************************************************/
static const G6HWC::GFXSHAREDSTATE_PREFILTER_OPERATION g_cConvertCompareFunc[] =
{
    G6HWC::GFXSHAREDSTATE_PREFILTER_NEVER,     // SAMPLER_COMPARE_FUNC_ALWAYS
    G6HWC::GFXSHAREDSTATE_PREFILTER_ALWAYS,    // SAMPLER_COMPARE_FUNC_NEVER
    G6HWC::GFXSHAREDSTATE_PREFILTER_LEQUAL,    // SAMPLER_COMPARE_FUNC_LESS
    G6HWC::GFXSHAREDSTATE_PREFILTER_NOTEQUAL,  // SAMPLER_COMPARE_FUNC_EQUAL
    G6HWC::GFXSHAREDSTATE_PREFILTER_LESS,      // SAMPLER_COMPARE_FUNC_LESS_EQUAL
    G6HWC::GFXSHAREDSTATE_PREFILTER_GEQUAL,    // SAMPLER_COMPARE_FUNC_GREATER
    G6HWC::GFXSHAREDSTATE_PREFILTER_EQUAL,     // SAMPLER_COMPARE_FUNC_NOT_EQUAL
    G6HWC::GFXSHAREDSTATE_PREFILTER_GREATER    // SAMPLER_COMPARE_FUNC_GREATER_EQUAL
};

C_ASSERT(sizeof(g_cConvertCompareFunc) ==
    sizeof(G6HWC::GFXSHAREDSTATE_PREFILTER_OPERATION) * NUM_SAMPLER_COMPARE_FUNC_TYPES);

/*****************************************************************************\
CONST: g_cConvertSurfaceFormat
\*****************************************************************************/
static const G6HWC::GFXSHAREDSTATE_SURFACEFORMAT g_cConvertSurfaceFormat[] =
{
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_UNKNOWN
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R64G64B64A64_FLOAT,         // IGC::SURFACE_FORMAT_R64G64B64A64_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R64G64B64_FLOAT,            // IGC::SURFACE_FORMAT_R64G64B64_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R64G64_FLOAT,               // IGC::SURFACE_FORMAT_R64G64_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R64_FLOAT,                  // IGC::SURFACE_FORMAT_R64_FLOAT
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R64G64B64A64_PASSTHRU
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R64G64B64_PASSTHRU
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R64G64_PASSTHRU
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R64_PASSTHRU
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32A32_FLOAT,         // IGC::SURFACE_FORMAT_R32G32B32A32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32A32_SINT,          // IGC::SURFACE_FORMAT_R32G32B32A32_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32A32_UINT,          // IGC::SURFACE_FORMAT_R32G32B32A32_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32A32_UNORM,         // IGC::SURFACE_FORMAT_R32G32B32A32_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32A32_SNORM,         // IGC::SURFACE_FORMAT_R32G32B32A32_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32A32_USCALED,       // IGC::SURFACE_FORMAT_R32G32B32A32_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32A32_SSCALED,       // IGC::SURFACE_FORMAT_R32G32B32A32_SSCALED
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R32G32B32A32_SFIXED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32X32_FLOAT,         // IGC::SURFACE_FORMAT_R32G32B32X32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32_FLOAT,            // IGC::SURFACE_FORMAT_R32G32B32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32_SINT,             // IGC::SURFACE_FORMAT_R32G32B32_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32_UINT,             // IGC::SURFACE_FORMAT_R32G32B32_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32_UNORM,            // IGC::SURFACE_FORMAT_R32G32B32_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32_SNORM,            // IGC::SURFACE_FORMAT_R32G32B32_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32_USCALED,          // IGC::SURFACE_FORMAT_R32G32B32_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32B32_SSCALED,          // IGC::SURFACE_FORMAT_R32G32B32_SSCALED
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R32G32B32_SFIXED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32_FLOAT,               // IGC::SURFACE_FORMAT_R32G32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32_SINT,                // IGC::SURFACE_FORMAT_R32G32_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32_UINT,                // IGC::SURFACE_FORMAT_R32G32_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32_UNORM,               // IGC::SURFACE_FORMAT_R32G32_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32_SNORM,               // IGC::SURFACE_FORMAT_R32G32_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32_USCALED,             // IGC::SURFACE_FORMAT_R32G32_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32G32_SSCALED,             // IGC::SURFACE_FORMAT_R32G32_SSCALED
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R32G32_SFIXED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32_FLOAT,                  // IGC::SURFACE_FORMAT_R32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32_SINT,                   // IGC::SURFACE_FORMAT_R32_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32_UINT,                   // IGC::SURFACE_FORMAT_R32_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32_UNORM,                  // IGC::SURFACE_FORMAT_R32_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32_SNORM,                  // IGC::SURFACE_FORMAT_R32_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32_USCALED,                // IGC::SURFACE_FORMAT_R32_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32_SSCALED,                // IGC::SURFACE_FORMAT_R32_SSCALED
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R32_SFIXED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R32_FLOAT_X8X24_TYPELESS,   // IGC::SURFACE_FORMAT_R32_FLOAT_X8X24_TYPELESS
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R32_FLOAT_S8_UINT_X24_TYPELESS
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_X32_TYPELESS_G8X24_UINT,    // IGC::SURFACE_FORMAT_X32_TYPELESS_G8X24_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R24_UNORM_X8_TYPELESS,      // IGC::SURFACE_FORMAT_R24_UNORM_X8_TYPELESS
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R24_UNORM_S8_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_X24_TYPELESS_G8_UINT,       // IGC::SURFACE_FORMAT_X24_TYPELESS_G8_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16A16_FLOAT,         // IGC::SURFACE_FORMAT_R16G16B16A16_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16A16_SINT,          // IGC::SURFACE_FORMAT_R16G16B16A16_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16A16_UINT,          // IGC::SURFACE_FORMAT_R16G16B16A16_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16A16_UNORM,         // IGC::SURFACE_FORMAT_R16G16B16A16_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16A16_SNORM,         // IGC::SURFACE_FORMAT_R16G16B16A16_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16A16_USCALED,       // IGC::SURFACE_FORMAT_R16G16B16A16_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16A16_SSCALED,       // IGC::SURFACE_FORMAT_R16G16B16A16_SSCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16X16_UNORM,         // IGC::SURFACE_FORMAT_R16G16B16X16_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16X16_FLOAT,         // IGC::SURFACE_FORMAT_R16G16B16X16_FLOAT
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R16G16B16_SINT
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R16G16B16_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16_UNORM,            // IGC::SURFACE_FORMAT_R16G16B16_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16_SNORM,            // IGC::SURFACE_FORMAT_R16G16B16_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16_USCALED,          // IGC::SURFACE_FORMAT_R16G16B16_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16B16_SSCALED,          // IGC::SURFACE_FORMAT_R16G16B16_SSCALED
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R16G16B16_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16_FLOAT,               // IGC::SURFACE_FORMAT_R16G16_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16_SINT,                // IGC::SURFACE_FORMAT_R16G16_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16_UINT,                // IGC::SURFACE_FORMAT_R16G16_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16_UNORM,               // IGC::SURFACE_FORMAT_R16G16_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16_SNORM,               // IGC::SURFACE_FORMAT_R16G16_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16_USCALED,             // IGC::SURFACE_FORMAT_R16G16_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16G16_SSCALED,             // IGC::SURFACE_FORMAT_R16G16_SSCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16_FLOAT,                  // IGC::SURFACE_FORMAT_R16_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16_SINT,                   // IGC::SURFACE_FORMAT_R16_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16_UINT,                   // IGC::SURFACE_FORMAT_R16_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16_UNORM,                  // IGC::SURFACE_FORMAT_R16_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16_SNORM,                  // IGC::SURFACE_FORMAT_R16_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16_USCALED,                // IGC::SURFACE_FORMAT_R16_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R16_SSCALED,                // IGC::SURFACE_FORMAT_R16_SSCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R11G11B10_FLOAT,            // IGC::SURFACE_FORMAT_R11G11B10_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R10G10B10A2_UNORM,          // IGC::SURFACE_FORMAT_R10G10B10A2_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R10G10B10A2_UNORM_SRGB,     // IGC::SURFACE_FORMAT_R10G10B10A2_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R10G10B10A2_UINT,           // IGC::SURFACE_FORMAT_R10G10B10A2_UINT
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R10G10B10A2_SNORM
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R10G10B10A2_USCALED
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R10G10B10A2_SSCALED
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R10G10B10A2_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R10G10B10_SNORM_A2_UNORM,   // IGC::SURFACE_FORMAT_R10G10B10_SNORM_A2_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R10G10B10X2_USCALED,        // IGC::SURFACE_FORMAT_R10G10B10X2_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B10G10R10A2_UNORM,          // IGC::SURFACE_FORMAT_B10G10R10A2_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B10G10R10A2_UNORM_SRGB,     // IGC::SURFACE_FORMAT_B10G10R10A2_UNORM_SRGB
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_B10G10R10A2_UINT
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_B10G10R10A2_SNORM
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_B10G10R10A2_USCALED
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_B10G10R10A2_SSCALED
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_B10G10R10A2_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B10G10R10X2_UNORM,          // IGC::SURFACE_FORMAT_B10G10R10X2_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R9G9B9E5_SHAREDEXP,         // IGC::SURFACE_FORMAT_R9G9B9E5_SHAREDEXP
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8A8_SINT,              // IGC::SURFACE_FORMAT_R8G8B8A8_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8A8_UINT,              // IGC::SURFACE_FORMAT_R8G8B8A8_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8A8_UNORM,             // IGC::SURFACE_FORMAT_R8G8B8A8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8A8_UNORM_SRGB,        // IGC::SURFACE_FORMAT_R8G8B8A8_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8A8_SNORM,             // IGC::SURFACE_FORMAT_R8G8B8A8_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8A8_USCALED,           // IGC::SURFACE_FORMAT_R8G8B8A8_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8A8_SSCALED,           // IGC::SURFACE_FORMAT_R8G8B8A8_SSCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8X8_UNORM,             // IGC::SURFACE_FORMAT_R8G8B8X8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8X8_UNORM_SRGB,        // IGC::SURFACE_FORMAT_R8G8B8X8_UNORM_SRGB
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R8G8_SNORM_B8X8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B8G8R8A8_UNORM,             // IGC::SURFACE_FORMAT_B8G8R8A8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B8G8R8A8_UNORM_SRGB,        // IGC::SURFACE_FORMAT_B8G8R8A8_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B8G8R8X8_UNORM,             // IGC::SURFACE_FORMAT_B8G8R8X8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B8G8R8X8_UNORM_SRGB,        // IGC::SURFACE_FORMAT_B8G8R8X8_UNORM_SRGB
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R8G8B8_SINT
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R8G8B8_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8_UNORM,               // IGC::SURFACE_FORMAT_R8G8B8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8_SNORM,               // IGC::SURFACE_FORMAT_R8G8B8_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8_USCALED,             // IGC::SURFACE_FORMAT_R8G8B8_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8B8_SSCALED,             // IGC::SURFACE_FORMAT_R8G8B8_SSCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8_SINT,                  // IGC::SURFACE_FORMAT_R8G8_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8_UINT,                  // IGC::SURFACE_FORMAT_R8G8_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8_UNORM,                 // IGC::SURFACE_FORMAT_R8G8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8_SNORM,                 // IGC::SURFACE_FORMAT_R8G8_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8_USCALED,               // IGC::SURFACE_FORMAT_R8G8_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8_SSCALED,               // IGC::SURFACE_FORMAT_R8G8_SSCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8_SINT,                    // IGC::SURFACE_FORMAT_R8_SINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8_UINT,                    // IGC::SURFACE_FORMAT_R8_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8_UNORM,                   // IGC::SURFACE_FORMAT_R8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8_SNORM,                   // IGC::SURFACE_FORMAT_R8_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8_USCALED,                 // IGC::SURFACE_FORMAT_R8_USCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8_SSCALED,                 // IGC::SURFACE_FORMAT_R8_SSCALED
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B5G6R5_UNORM,               // IGC::SURFACE_FORMAT_B5G6R5_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B5G6R5_UNORM_SRGB,          // IGC::SURFACE_FORMAT_B5G6R5_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B5G5R5A1_UNORM,             // IGC::SURFACE_FORMAT_B5G5R5A1_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B5G5R5A1_UNORM_SRGB,        // IGC::SURFACE_FORMAT_B5G5R5A1_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B5G5R5X1_UNORM,             // IGC::SURFACE_FORMAT_B5G5R5X1_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B5G5R5X1_UNORM_SRGB,        // IGC::SURFACE_FORMAT_B5G5R5X1_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R5G5_SNORM_B6_UNORM,        // IGC::SURFACE_FORMAT_R5G5_SNORM_B6_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B4G4R4A4_UNORM,             // IGC::SURFACE_FORMAT_B4G4R4A4_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_B4G4R4A4_UNORM_SRGB,        // IGC::SURFACE_FORMAT_B4G4R4A4_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R1_UINT,                    // IGC::SURFACE_FORMAT_R1_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R1_UINT,                    // IGC::SURFACE_FORMAT_R1_UINT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_I32X32_FLOAT,               // IGC::SURFACE_FORMAT_I32X32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L32A32_FLOAT,               // IGC::SURFACE_FORMAT_L32A32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L32X32_FLOAT,               // IGC::SURFACE_FORMAT_L32X32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_A32X32_FLOAT,               // IGC::SURFACE_FORMAT_A32X32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_I24X8_UNORM,                // IGC::SURFACE_FORMAT_I24X8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L24X8_UNORM,                // IGC::SURFACE_FORMAT_L24X8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_A24X8_UNORM,                // IGC::SURFACE_FORMAT_A24X8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_I32_FLOAT,                  // IGC::SURFACE_FORMAT_I32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L32_FLOAT,                  // IGC::SURFACE_FORMAT_L32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_A32_FLOAT,                  // IGC::SURFACE_FORMAT_A32_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L16A16_FLOAT,               // IGC::SURFACE_FORMAT_L16A16_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L16A16_UNORM,               // IGC::SURFACE_FORMAT_L16A16_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_I16_FLOAT,                  // IGC::SURFACE_FORMAT_I16_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_I16_UNORM,                  // IGC::SURFACE_FORMAT_I16_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L16_FLOAT,                  // IGC::SURFACE_FORMAT_L16_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L16_UNORM,                  // IGC::SURFACE_FORMAT_L16_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_A16_FLOAT,                  // IGC::SURFACE_FORMAT_A16_FLOAT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_A16_UNORM,                  // IGC::SURFACE_FORMAT_A16_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L8A8_UNORM,                 // IGC::SURFACE_FORMAT_L8A8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L8A8_UNORM_SRGB,            // IGC::SURFACE_FORMAT_L8A8_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_I8_UNORM,                   // IGC::SURFACE_FORMAT_I8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L8_UNORM,                   // IGC::SURFACE_FORMAT_L8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_L8_UNORM_SRGB,              // IGC::SURFACE_FORMAT_L8_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_A8_UNORM,                   // IGC::SURFACE_FORMAT_A8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_P4A4_UNORM,                 // IGC::SURFACE_FORMAT_P4A4_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_A4P4_UNORM,                 // IGC::SURFACE_FORMAT_A4P4_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_P8_UNORM,                   // IGC::SURFACE_FORMAT_P8_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_P2_UNORM,                   // IGC::SURFACE_FORMAT_P2_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC1_UNORM,                  // IGC::SURFACE_FORMAT_BC1_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC2_UNORM,                  // IGC::SURFACE_FORMAT_BC2_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC3_UNORM,                  // IGC::SURFACE_FORMAT_BC3_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC4_UNORM,                  // IGC::SURFACE_FORMAT_BC4_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC5_UNORM,                  // IGC::SURFACE_FORMAT_BC5_UNORM
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_BC7_UNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC1_UNORM_SRGB,             // IGC::SURFACE_FORMAT_BC1_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC2_UNORM_SRGB,             // IGC::SURFACE_FORMAT_BC2_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC3_UNORM_SRGB,             // IGC::SURFACE_FORMAT_BC3_UNORM_SRGB
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_BC7_UNORM_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC4_SNORM,                  // IGC::SURFACE_FORMAT_BC4_SNORM
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_BC5_SNORM,                  // IGC::SURFACE_FORMAT_BC5_SNORM
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_BC6H_UF16
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_BC6H_SF16
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_DXT1_RGB,                   // IGC::SURFACE_FORMAT_DXT1_RGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_DXT1_RGB_SRGB,              // IGC::SURFACE_FORMAT_DXT1_RGB_SRGB
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_FXT1,                       // IGC::SURFACE_FORMAT_FXT1
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_YCRCB_NORMAL,               // IGC::SURFACE_FORMAT_YCRCB_NORMAL
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_YCRCB_SWAPUVY,              // IGC::SURFACE_FORMAT_YCRCB_SWAPUVY
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_YCRCB_SWAPUV,               // IGC::SURFACE_FORMAT_YCRCB_SWAPUV
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_YCRCB_SWAPY,                // IGC::SURFACE_FORMAT_YCRCB_SWAPY
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8_UNORM,                   // IGC::SURFACE_FORMAT_PLANAR_Y
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8_UNORM,                   // IGC::SURFACE_FORMAT_PLANAR_U
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8_UNORM,                   // IGC::SURFACE_FORMAT_PLANAR_V
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_R8G8_UNORM,                 // IGC::SURFACE_FORMAT_PLANAR_UV
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R16G16B16_SINT_OGL_VIRT
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R16G16B16_UINT_OGL_VIRT
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R8G8B8_SINT_OGL_VIRT
    (G6HWC::GFXSHAREDSTATE_SURFACEFORMAT)0x0FF,                     // IGC::SURFACE_FORMAT_R8G8B8_UINT_OGL_VIRT
    G6HWC::GFXSHAREDSTATE_SURFACEFORMAT_RAW,                        // IGC::SURFACE_FORMAT_RAW
};

C_ASSERT( sizeof(g_cConvertSurfaceFormat) ==
    sizeof(G6HWC::GFXSHAREDSTATE_SURFACEFORMAT) * IGC::NUM_SURFACE_FORMATS );

/*****************************************************************************\
CONST: g_cConvertSurfaceMipMapLayout
\*****************************************************************************/
static const G6HWC::GFXSHAREDSTATE_SURFACE_MIPMAPLAYOUT g_cConvertSurfaceMipMapLayout[] =
{
    G6HWC::GFXSHAREDSTATE_SURFACE_MIPMAPLAYOUT_BELOW,   // RESOURCE_MIPMAP_LAYOUT_BELOW
    G6HWC::GFXSHAREDSTATE_SURFACE_MIPMAPLAYOUT_RIGHT,   // RESOURCE_MIPMAP_LAYOUT_RIGHT
};

C_ASSERT( sizeof(g_cConvertSurfaceMipMapLayout) ==
    sizeof(G6HWC::GFXSHAREDSTATE_SURFACE_MIPMAPLAYOUT) * NUM_RESOURCE_MIPMAP_LAYOUT_MODES );

/*****************************************************************************\
CONST: g_cConvertSurfaceType
\*****************************************************************************/
static const G6HWC::GFXSHAREDSTATE_SURFACETYPE g_cConvertSurfaceType[] =
{
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_NULL,     // SURFACE_UNKNOWN
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_NULL,     // SURFACE_NULL
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_1D,       // SURFACE_1D
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_1D,       // SURFACE_1D_ARRAY
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_2D,       // SURFACE_2D
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_2D,       // SURFACE_2D_ARRAY
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_3D,       // SURFACE_3D
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_CUBE,     // SURFACE_CUBE
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_CUBE,     // SURFACE_CUBE_ARRAY
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_BUFFER,   // SURFACE_CONSTANT
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_BUFFER,   // SURFACE_BUFFER
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_2D,       // SURFACE_2D_MEDIA
    G6HWC::GFXSHAREDSTATE_SURFACETYPE_2D        // SURFACE_2D_MEDIA_BLOCK
};

C_ASSERT( sizeof(g_cConvertSurfaceType) ==
    sizeof(G6HWC::GFXSHAREDSTATE_SURFACETYPE) * NUM_SURFACE_TYPES );

#if 0
/*****************************************************************************\
CONST: g_cConvertResourceType
\*****************************************************************************/
static const iOpenCL::IMAGE_MEMORY_OBJECT_TYPE g_cConvertResourceType[] =
{
    iOpenCL::IMAGE_MEMORY_OBJECT_INVALID,   // SHADER_RESOURCE_INVALID
    iOpenCL::IMAGE_MEMORY_OBJECT_BUFFER,    // SHADER_RESOURCE_BUFFER
    iOpenCL::IMAGE_MEMORY_OBJECT_1D,        // SHADER_RESOURCE_1D
    iOpenCL::IMAGE_MEMORY_OBJECT_1D_ARRAY,  // SHADER_RESOURCE_1D_ARRAY
    iOpenCL::IMAGE_MEMORY_OBJECT_2D,        // SHADER_RESOURCE_2D
    iOpenCL::IMAGE_MEMORY_OBJECT_2D_ARRAY,  // SHADER_RESOURCE_2D_ARRAY
    iOpenCL::IMAGE_MEMORY_OBJECT_3D,        // SHADER_RESOURCE_3D
    iOpenCL::IMAGE_MEMORY_OBJECT_CUBE,      // SHADER_RESOURCE_CUBE
    iOpenCL::IMAGE_MEMORY_OBJECT_CUBE_ARRAY,// SHADER_RESOURCE_CUBE_ARRAY
    iOpenCL::IMAGE_MEMORY_OBJECT_2D_MEDIA,  // SHADER_RESOURCE_2D_MEDIA
};

C_ASSERT( sizeof(g_cConvertResourceType) ==
    sizeof(iOpenCL::IMAGE_MEMORY_OBJECT_TYPE) * USC::NUM_SHADER_RESOURCE_TYPES );
#endif

} // namespace iOpenCL

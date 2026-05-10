#pragma once
// Auto-generated: _D3DCAPS9

#include "_D3DDEVTYPE.h"
#include "_D3DPSHADERCAPS2_0.h"
#include "_D3DVSHADERCAPS2_0.h"

class _D3DCAPS9 {
public:
    _D3DDEVTYPE DeviceType; // +0x0
    unsigned int AdapterOrdinal; // +0x4
    unsigned long Caps; // +0x8
    unsigned long Caps2; // +0xC
    unsigned long Caps3; // +0x10
    unsigned long PresentationIntervals; // +0x14
    unsigned long CursorCaps; // +0x18
    unsigned long DevCaps; // +0x1C
    unsigned long PrimitiveMiscCaps; // +0x20
    unsigned long RasterCaps; // +0x24
    unsigned long ZCmpCaps; // +0x28
    unsigned long SrcBlendCaps; // +0x2C
    unsigned long DestBlendCaps; // +0x30
    unsigned long AlphaCmpCaps; // +0x34
    unsigned long ShadeCaps; // +0x38
    unsigned long TextureCaps; // +0x3C
    unsigned long TextureFilterCaps; // +0x40
    unsigned long CubeTextureFilterCaps; // +0x44
    unsigned long VolumeTextureFilterCaps; // +0x48
    unsigned long TextureAddressCaps; // +0x4C
    unsigned long VolumeTextureAddressCaps; // +0x50
    unsigned long LineCaps; // +0x54
    unsigned long MaxTextureWidth; // +0x58
    unsigned long MaxTextureHeight; // +0x5C
    unsigned long MaxVolumeExtent; // +0x60
    unsigned long MaxTextureRepeat; // +0x64
    unsigned long MaxTextureAspectRatio; // +0x68
    unsigned long MaxAnisotropy; // +0x6C
    float MaxVertexW; // +0x70
    float GuardBandLeft; // +0x74
    float GuardBandTop; // +0x78
    float GuardBandRight; // +0x7C
    float GuardBandBottom; // +0x80
    float ExtentsAdjust; // +0x84
    unsigned long StencilCaps; // +0x88
    unsigned long FVFCaps; // +0x8C
    unsigned long TextureOpCaps; // +0x90
    unsigned long MaxTextureBlendStages; // +0x94
    unsigned long MaxSimultaneousTextures; // +0x98
    unsigned long VertexProcessingCaps; // +0x9C
    unsigned long MaxActiveLights; // +0xA0
    unsigned long MaxUserClipPlanes; // +0xA4
    unsigned long MaxVertexBlendMatrices; // +0xA8
    unsigned long MaxVertexBlendMatrixIndex; // +0xAC
    float MaxPointSize; // +0xB0
    unsigned long MaxPrimitiveCount; // +0xB4
    unsigned long MaxVertexIndex; // +0xB8
    unsigned long MaxStreams; // +0xBC
    unsigned long MaxStreamStride; // +0xC0
    unsigned long VertexShaderVersion; // +0xC4
    unsigned long MaxVertexShaderConst; // +0xC8
    unsigned long PixelShaderVersion; // +0xCC
    float PixelShader1xMaxValue; // +0xD0
    unsigned long DevCaps2; // +0xD4
    float MaxNpatchTessellationLevel; // +0xD8
    unsigned long Reserved5; // +0xDC
    unsigned int MasterAdapterOrdinal; // +0xE0
    unsigned int AdapterOrdinalInGroup; // +0xE4
    unsigned int NumberOfAdaptersInGroup; // +0xE8
    unsigned long DeclTypes; // +0xEC
    unsigned long NumSimultaneousRTs; // +0xF0
    unsigned long StretchRectFilterCaps; // +0xF4
    _D3DVSHADERCAPS2_0 VS20Caps; // +0xF8
    _D3DPSHADERCAPS2_0 PS20Caps; // +0x108
    unsigned long VertexTextureFilterCaps; // +0x11C
    unsigned long MaxVShaderInstructionsExecuted; // +0x120
    unsigned long MaxPShaderInstructionsExecuted; // +0x124
    unsigned long MaxVertexShader30InstructionSlots; // +0x128
    unsigned long MaxPixelShader30InstructionSlots; // +0x12C
    // total size: 0x130 (304)

};

#pragma once
// Auto-generated: CD3DEnumeration

class CArrayList;
class IDirect3D9;

class CD3DEnumeration {
public:
    IDirect3D9 * m_pD3D; // +0x0
    CArrayList * m_pAdapterInfoList; // +0x4
    void * * ConfirmDeviceCallback; // +0x8
    unsigned int AppMinFullscreenWidth; // +0xC
    unsigned int AppMinFullscreenHeight; // +0x10
    unsigned int AppMinColorChannelBits; // +0x14
    unsigned int AppMinAlphaChannelBits; // +0x18
    unsigned int AppMinDepthBits; // +0x1C
    unsigned int AppMinStencilBits; // +0x20
    unsigned char AppUsesDepthBuffer; // +0x24
    unsigned char AppUsesMixedVP; // +0x25
    unsigned char AppRequiresWindowed; // +0x26
    unsigned char AppRequiresFullscreen; // +0x27
    CArrayList * m_pAllowedAdapterFormatList; // +0x28
    // total size: 0x2C (44)

};

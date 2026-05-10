#pragma once
// Auto-generated: _D3DPRESENT_PARAMETERS_

#include "_D3DFORMAT.h"
#include "_D3DMULTISAMPLE_TYPE.h"
#include "_D3DSWAPEFFECT.h"

class HWND__;

class _D3DPRESENT_PARAMETERS_ {
public:
    unsigned int BackBufferWidth; // +0x0
    unsigned int BackBufferHeight; // +0x4
    _D3DFORMAT BackBufferFormat; // +0x8
    unsigned int BackBufferCount; // +0xC
    _D3DMULTISAMPLE_TYPE MultiSampleType; // +0x10
    unsigned long MultiSampleQuality; // +0x14
    _D3DSWAPEFFECT SwapEffect; // +0x18
    HWND__ * hDeviceWindow; // +0x1C
    int Windowed; // +0x20
    int EnableAutoDepthStencil; // +0x24
    _D3DFORMAT AutoDepthStencilFormat; // +0x28
    unsigned long Flags; // +0x2C
    unsigned int FullScreen_RefreshRateInHz; // +0x30
    unsigned int PresentationInterval; // +0x34
    // total size: 0x38 (56)

};

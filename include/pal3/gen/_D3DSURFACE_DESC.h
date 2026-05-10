#pragma once
// Auto-generated: _D3DSURFACE_DESC

#include "_D3DFORMAT.h"
#include "_D3DMULTISAMPLE_TYPE.h"
#include "_D3DPOOL.h"
#include "_D3DRESOURCETYPE.h"

class _D3DSURFACE_DESC {
public:
    _D3DFORMAT Format; // +0x0
    _D3DRESOURCETYPE Type; // +0x4
    unsigned long Usage; // +0x8
    _D3DPOOL Pool; // +0xC
    _D3DMULTISAMPLE_TYPE MultiSampleType; // +0x10
    unsigned long MultiSampleQuality; // +0x14
    unsigned int Width; // +0x18
    unsigned int Height; // +0x1C
    // total size: 0x20 (32)

};

#pragma once
// Auto-generated: _D3DXPASS_DESC

#include "_D3DXSEMANTIC.h"

class _D3DXPASS_DESC {
public:
    char * Name; // +0x0
    unsigned int Annotations; // +0x4
    unsigned long VSVersion; // +0x8
    unsigned long PSVersion; // +0xC
    unsigned int VSSemanticsUsed; // +0x10
    _D3DXSEMANTIC VSSemantics[64]; // +0x14
    unsigned int PSSemanticsUsed; // +0x214
    _D3DXSEMANTIC PSSemantics[64]; // +0x218
    unsigned int PSSamplersUsed; // +0x418
    char * PSSamplers[16]; // +0x41C
    // total size: 0x45C (1116)

};

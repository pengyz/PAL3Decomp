#pragma once
// Auto-generated: gbPixelFormat

#include "gbPixelFmtType.h"

class gbPixelFormat {
public:
    gbPixelFmtType Type; // +0x0
    int Bpp; // +0x4
    gbColorQuad * Pal; // +0x8
    unsigned int r_mask; // +0xC
    unsigned int g_mask; // +0x10
    unsigned int b_mask; // +0x14
    unsigned int a_mask; // +0x18
    unsigned int r_shift; // +0x1C
    unsigned int g_shift; // +0x20
    unsigned int b_shift; // +0x24
    unsigned int a_shift; // +0x28
    // total size: 0x2C (44)

};

#pragma once
// Auto-generated: UILBColumn

#include "PtrArray.h"

class UILBColumn {
public:
    char head[64]; // +0x0
    PtrArray items; // +0x40
    int width; // +0x50
    unsigned char rightalign; // +0x54
    int rightoffset; // +0x58
    // total size: 0x5C (92)

    static void Destroy(); // 0x0043DCC0
};

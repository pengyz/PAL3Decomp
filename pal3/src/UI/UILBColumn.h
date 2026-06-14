#pragma once
// Auto-generated: UILBColumn

#include "PtrArray.h"

class UILBColumn {
public:
    char head[64]; // +0x0
    PtrArray items; // +0x40
    char _gap_044[12]; // +0x44
    int width; // +0x50
    // total size: 0x54 (84)

    UILBColumn(); // 0x0043DCA0
    void _UILBColumn(); // 0x0043DCB0
    void Destroy(); // 0x0043DCC0
};

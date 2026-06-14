#pragma once
// Auto-generated: ColRet

#include "Triangle.h"
#include "gbengine/gbengine_types.h"

class ColRet {
public:
    float dist; // +0x0
    gbVec3D pt; // +0x4
    char _gap_008[8]; // +0x8
    BYTE have; // +0x10
    char _gap_011[3]; // +0x11
    int counter; // +0x14
    Triangle tri; // +0x18
    char _tail_01C[44]; // +0x1C
    // total size: 0x48 (72)

};

#pragma once
// Auto-generated: OBJHELPER

#include "gbengine/gbengine_types.h"

class OBJHELPER {
public:
    BYTE bValid; // +0x0
    char _gap_001[3]; // +0x1
    int nType; // +0x4
    tagRECT rTouchArea; // +0x8
    char _gap_00C[12]; // +0xC
    tagPOINT pGroundPt; // +0x18
    char _gap_01C[4]; // +0x1C
    int nEffRunID; // +0x20
    gbVec3D vEffPos; // +0x24
    char _tail_028[8]; // +0x28
    // total size: 0x30 (48)

};

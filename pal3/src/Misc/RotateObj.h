#include "PalScriptWaitObj.h"
#pragma once
// Auto-generated: RotateObj

#include "gbengine/gbengine_types.h"

class RotateObj : public PalScriptWaitObj {
public:
    char _gap_000[8]; // +0x0
    float m_passedtime; // +0x8
    BYTE end; // +0xC
    char _gap_00D[3]; // +0xD
    gbVec3D m_rotate; // +0x10
    char _gap_014[8]; // +0x14
    float m_rotatetime; // +0x1C
    BYTE m_mode; // +0x20
    char _tail_021[3]; // +0x21
    // total size: 0x24 (36)

};

#pragma once
// Auto-generated: UI3DObj

#include "gbengine/gbengine_types.h"

class Actor;

class UI3DObj {
public:
    BYTE m_mouseoff; // +0x0
    char _gap_001[3]; // +0x1
    int m_enable; // +0x4
    int m_needdel; // +0x8
    int m_type; // +0xC
    Actor * m_actor; // +0x10
    gbVec3D m_pos; // +0x14
    char _tail_018[8]; // +0x18
    // total size: 0x20 (32)

};

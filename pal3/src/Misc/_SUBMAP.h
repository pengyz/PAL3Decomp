#pragma once
// Auto-generated: _SUBMAP

#include "gbengine/gbTexture.h"

class _SUBMAP {
public:
    BYTE m_bShow; // +0x0
    char _gap_001[3]; // +0x1
    tagRECT m_pos; // +0x4
    char _gap_008[12]; // +0x8
    tagRECT m_notepos; // +0x14
    char _gap_018[12]; // +0x18
    float m_fposX; // +0x24
    float m_fposY; // +0x28
    gbTexture * m_pMap; // +0x2C
    int m_MapLeftToScreenLeft; // +0x30
    int m_MapLeftToScreenRight; // +0x34
    int m_MapTopToScreenTop; // +0x38
    int m_MapTopToScreenBottom; // +0x3C
    int m_NoteLeft; // +0x40
    int m_NoteRight; // +0x44
    int m_NoteTop; // +0x48
    int m_NoteBottom; // +0x4C
    // total size: 0x50 (80)

};

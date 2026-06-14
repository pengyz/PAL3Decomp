#pragma once
// Auto-generated: BtnGroup

#include "UIButton.h"
#include "_BGM.h"

class BtnGroup {
public:
    tagRECT upRc; // +0x0
    char _gap_004[12]; // +0x4
    tagRECT dwRc; // +0x10
    char _gap_014[12]; // +0x14
    UIButton m_btnUp; // +0x20
    char _gap_024[340]; // +0x24
    UIButton m_btnDw; // +0x178
    char _gap_17C[340]; // +0x17C
    int m_sizex; // +0x2D0
    int m_sizey; // +0x2D4
    _BGM m_mode; // +0x2D8
    int m_Interval; // +0x2DC
    BYTE m_opt; // +0x2E0
    char _tail_2E1[3]; // +0x2E1
    // total size: 0x2E4 (740)

};

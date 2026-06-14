#include "PalScriptWaitObj.h"
#pragma once
// Auto-generated: ScreenEffect

class ScreenEffect : public PalScriptWaitObj {
public:
    char _gap_000[8]; // +0x0
    int m_nType; // +0x8
    int m_life; // +0xC
    float m_age; // +0x10
    BYTE m_hold; // +0x14
    char _tail_015[3]; // +0x15
    // total size: 0x18 (24)

    void Apply(); // 0x004B4DC0
    ScreenEffect(); // 0x004BDFB0
    void CopyParams(int *pParams); // 0x004BE830
};

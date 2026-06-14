#pragma once
// Auto-generated: ArcMsic

#include "tagPlayerSet.h"

class ArcMsic {
public:
    _BYTE m_bigMapElement[40]; // +0x0
    UINT m_dwCombatTimes; // +0x28
    BYTE bPXVariance; // +0x2C
    BYTE bHaveNimbus; // +0x2D
    char _gap_02E[2]; // +0x2E
    int nNimbus[5]; // +0x30
    tagPlayerSet m_Player[11]; // +0x44
    char _gap_070[528]; // +0x70
    int nImbibeNimbusTimes; // +0x280
    BYTE bShowStatuary; // +0x284
    _BYTE reverse[99]; // +0x285
    // total size: 0x2E8 (744)

};

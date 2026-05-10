#pragma once
// Auto-generated: ArcMsic

#include "tagPlayerSet.h"

class ArcMsic {
public:
    unsigned char m_bigMapElement[40]; // +0x0
    unsigned long m_dwCombatTimes; // +0x28
    unsigned char bPXVariance; // +0x2C
    unsigned char bHaveNimbus; // +0x2D
    int nNimbus[5]; // +0x30
    tagPlayerSet m_Player[11]; // +0x44
    int nImbibeNimbusTimes; // +0x280
    unsigned char bShowStatuary; // +0x284
    unsigned char reverse[99]; // +0x285
    // total size: 0x2E8 (744)

};

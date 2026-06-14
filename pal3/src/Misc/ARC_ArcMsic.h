#pragma once
// Auto-generated: ARC_ArcMsic

#include "ARC_WuLing.h"

class ARC_ArcMsic {
public:
    _BYTE byte6forwishPool[12]; // +0x0
    _BYTE m_isPurged[5][2]; // +0xC
    _BYTE m_isAllPurged[5]; // +0x16
    char _gap_01B[1]; // +0x1B
    int m_totalNum; // +0x1C
    BYTE m_isyjfx; // +0x20
    _BYTE m_ComSkill[8][5]; // +0x21
    BYTE m_SDTY; // +0x49
    BYTE m_APPR; // +0x4A
    BYTE m_SKEE; // +0x4B
    UINT m_isSword; // +0x4C
    UINT m_isJusticeBook; // +0x50
    int g_dwWeaponWU; // +0x54
    _BYTE m_bigMapElement[40]; // +0x58
    UINT g_nWolfCounter; // +0x80
    float com_quantum[5][8]; // +0x84
    ARC_WuLing m_PurgeNum; // +0x124
    _BYTE byteoffset[256]; // +0x128
    // total size: 0x228 (552)

};

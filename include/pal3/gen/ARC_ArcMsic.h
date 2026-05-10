#pragma once
// Auto-generated: ARC_ArcMsic

#include "ARC_WuLing.h"

class ARC_ArcMsic {
public:
    BYTE byte6forwishPool[12]; // +0x0
    BYTE m_isPurged[5][2]; // +0xC
    BYTE m_isAllPurged[5]; // +0x16
    int m_totalNum; // +0x1C
    BYTE m_isyjfx; // +0x20
    BYTE m_ComSkill[8][5]; // +0x21
    BYTE m_SDTY; // +0x49
    BYTE m_APPR; // +0x4A
    BYTE m_SKEE; // +0x4B
    DWORD m_isSword; // +0x4C
    DWORD m_isJusticeBook; // +0x50
    int g_dwWeaponWU; // +0x54
    BYTE m_bigMapElement[40]; // +0x58
    DWORD g_nWolfCounter; // +0x80
    float com_quantum[5][8]; // +0x84
    ARC_WuLing m_PurgeNum; // +0x124
    BYTE byteoffset[162177]; // +0x128
    // total size: 0x27AAC (162476)

};

#pragma once
// Auto-generated: ARC_ArcMsic

#include "ARC_WuLing.h"

class ARC_ArcMsic {
public:
    unsigned char byte6forwishPool[12]; // +0x0
    unsigned char m_isPurged[5][2]; // +0xC
    unsigned char m_isAllPurged[5]; // +0x16
    int m_totalNum; // +0x1C
    unsigned char m_isyjfx; // +0x20
    unsigned char m_ComSkill[8][5]; // +0x21
    unsigned char m_SDTY; // +0x49
    unsigned char m_APPR; // +0x4A
    unsigned char m_SKEE; // +0x4B
    unsigned long m_isSword; // +0x4C
    unsigned long m_isJusticeBook; // +0x50
    int g_dwWeaponWU; // +0x54
    unsigned char m_bigMapElement[40]; // +0x58
    unsigned long g_nWolfCounter; // +0x80
    float com_quantum[5][8]; // +0x84
    ARC_WuLing m_PurgeNum; // +0x124
    unsigned char byteoffset[162177]; // +0x128
    // total size: 0x27AAC (162476)

};

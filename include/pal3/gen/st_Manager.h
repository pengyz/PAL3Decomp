#pragma once
// Auto-generated: st_Manager

class FightItem;

class st_Manager {
public:
    BYTE m_Type; // +0x0
    BYTE m_Dicker; // +0x1
    WORD m_ID; // +0x2
    char m_Name[256]; // +0x4
    BYTE m_C; // +0x104
    int m_Patience; // +0x108
    char m_BeginTalk[256]; // +0x10C
    char m_EntryBuy[256]; // +0x20C
    char m_EntrySale[256]; // +0x30C
    char m_NormalAcptTalk[256]; // +0x40C
    char m_NormalCnslTalk[256]; // +0x50C
    char m_NoEnoughMoney[256]; // +0x60C
    char m_Leave[256]; // +0x70C
    char m_HarshTalkbuy[256]; // +0x80C
    float m_AcptQuantum[5]; // +0x90C
    char m_AcptTalk[256][2][5]; // +0x920
    float m_RfusQuantum[5]; // +0x1320
    char m_RfusTalk[256][2][5]; // +0x1334
    float m_HarshQuantum[5]; // +0x1D34
    char m_HarshTalk[256][2][5]; // +0x1D48
    char m_ForceAcptTalk[256][2][5]; // +0x2748
    char m_ForceAcptTalkback[256][5]; // +0x3148
    int m_StoreNum[2]; // +0x3648
    DWORD m_StoreID[200][2]; // +0x3650
    FightItem * m_StoreData[200][2]; // +0x3C90
    BYTE m_IsCtrl[200][2]; // +0x42D0
    // total size: 0x4460 (17504)

};

#pragma once
// Auto-generated: DealData

#include "PAL_GDB.h"
#include "TxtFile.h"
#include "st_Manager.h"

class DealData {
public:
    BYTE m_isHarshRfus; // +0x0
    char _gap_001[3]; // +0x1
    TxtFile m_LoadTxt; // +0x4
    char _gap_008[520]; // +0x8
    PAL_GDB m_LoadGDB; // +0x210
    char _gap_214[814520]; // +0x214
    BYTE m_IsLang; // +0xC6FCC
    char _gap_C6FCD[3]; // +0xC6FCD
    TxtFile m_LoadLang; // +0xC6FD0
    char _gap_C6FD4[520]; // +0xC6FD4
    char m_lastFile[256]; // +0xC71DC
    st_Manager m_ManagerData; // +0xC72DC
    char _tail_C72E0[17500]; // +0xC72E0
    // total size: 0xCB73C (833340)

    DealData(); // 0x00457260
    int CompareString(LPCSTR lpString1, LPCSTR lpString2); // 0x004573C0
    LPSTR LoadStoreConfig(CHAR *lpString2); // 0x00457490
};

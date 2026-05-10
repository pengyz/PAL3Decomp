#pragma once
// Auto-generated: DealData

#include "PAL_GDB.h"
#include "TxtFile.h"
#include "st_Manager.h"

class DealData {
public:
    unsigned char m_IsLoadTxt; // +0x0
    TxtFile m_LoadTxt; // +0x4
    PAL_GDB m_LoadGDB; // +0x210
    unsigned char m_IsLang; // +0xC6FCC
    TxtFile m_LoadLang; // +0xC6FD0
    char m_lastFile[256]; // +0xC71DC
    char buf[256]; // +0x0
    st_Manager m_ManagerData; // +0xC72DC
    unsigned char m_isHarshRfus; // +0x0
    char m_LangInfo[256][512]; // +0x0
    // total size: 0xCB73C (833340)

};

#pragma once
// Auto-generated: SoundMgr

#include "CPK.h"
#include "TxtFile.h"

class SoundMgr {
public:
    unsigned char m_bScriptMusic; // +0x4
    char m_szScriptMusic[16]; // +0x8 (std::basic_string<char,std::char_traits<char>,std::allocator<char> >)
    int m_nScriptLoop; // +0x18
    char m_szSceneMusic[256]; // +0x1C
    TxtFile m_MusicTable; // +0x11C
    gbAudioManager * m_audiodrv; // +0x328
    float DEF3DMasterVol; // +0x32C
    float DEF2DMasterVol; // +0x330
    float DEFMusicMasterVol; // +0x334
    unsigned char m_bValidDetectSceneMusic; // +0x338
    char m_cbbuf[16]; // +0x33C (std::vector<SoundItem,std::allocator<SoundItem> >)
    int m_cbcursor; // +0x34C
    CPK m_Cpk; // +0x350
    // total size: 0xE050C (918796)

};

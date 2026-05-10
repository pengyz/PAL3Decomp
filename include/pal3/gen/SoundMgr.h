#pragma once
// Auto-generated: SoundMgr

#include "CPK.h"
#include "TxtFile.h"

class SoundMgr {
public:
    unsigned char m_bScriptMusic; // +0x4
    struct allocator<char> > {}; // nested type stub
    allocator<char> > m_szScriptMusic; // +0x8
    int m_nScriptLoop; // +0x18
    char m_szSceneMusic[256]; // +0x1C
    TxtFile m_MusicTable; // +0x11C
    gbAudioManager * m_audiodrv; // +0x328
    float DEF3DMasterVol; // +0x32C
    float DEF2DMasterVol; // +0x330
    float DEFMusicMasterVol; // +0x334
    unsigned char m_bValidDetectSceneMusic; // +0x338
    struct allocator<SoundItem> > {}; // nested type stub
    allocator<SoundItem> > m_cbbuf; // +0x33C
    int m_cbcursor; // +0x34C
    CPK m_Cpk; // +0x350
    // total size: 0xE050C (918796)

};

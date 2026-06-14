#pragma once
// Auto-generated: SoundMgr

#include "gbengine/gbVFileSystem.h"
#include "TxtFile.h"
#include "gbengine/gbAudio.h"

class SoundMgr {
public:
    char _gap_000[4]; // +0x0
    BYTE m_bScriptMusic; // +0x4
    char _gap_005[3]; // +0x5
    char m_szScriptMusic[16]; // +0x8
    int m_nScriptLoop; // +0x18
    char m_szSceneMusic[256]; // +0x1C
    TxtFile m_MusicTable; // +0x11C
    char _gap_120[520]; // +0x120
    gbAudioManager * m_audiodrv; // +0x328
    int DEF3DMasterVol; // +0x32C
    int DEF2DMasterVol; // +0x330
    float DEFMusicMasterVol; // +0x334
    BYTE m_bValidDetectSceneMusic; // +0x338
    char _gap_339[3]; // +0x339
    char m_cbbuf[16]; // +0x33C
    int m_cbcursor; // +0x34C
    CPK m_Cpk; // +0x350
    char _tail_354[917944]; // +0x354
    // total size: 0xE050C (918796)

    char InitCPK(int nVal, int nVal2); // 0x0053C340
    int PlayCPKStream(); // 0x0053EA80
};

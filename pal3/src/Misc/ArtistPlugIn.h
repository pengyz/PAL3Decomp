#pragma once
// Auto-generated: ArtistPlugIn

#include "UIPosMaker.h"

class _PlugInfo;

class ArtistPlugIn {
public:
    FILE * pFile; // +0x0
    char _libfolder[512]; // +0x4
    _PlugInfo * pInfo; // +0x204
    UINT m_infoNum; // +0x208
    BYTE m_alreadyLoad; // +0x20C
    char _gap_20D[3]; // +0x20D
    tagRECT m_tRect; // +0x210
    char _gap_214[12]; // +0x214
    BYTE m_bOptmize; // +0x220
    char _gap_221[3]; // +0x221
    UIPosMaker m_posMaker; // +0x224
    char _tail_228[8]; // +0x228
    // total size: 0x230 (560)

};

#pragma once
// Auto-generated: ArcLocale

#include "ArcLocaleMusic.h"
#include "ArcLocaleRole.h"
#include "RC_ARG.h"
#include "SceneInfo.h"
#include "gbengine/gbGfxManager.h"

class ArcLocale {
public:
    SceneInfo scene; // +0x0
    char _gap_004[128]; // +0x4
    RC_ARG camera; // +0x84
    char _gap_088[24]; // +0x88
    ArcLocaleRole player[5]; // +0xA0
    char _gap_0B4[120]; // +0xB4
    BYTE underctrl; // +0x12C
    char px_mdl[32]; // +0x12D
    char _gap_14D[3]; // +0x14D
    PlayerMgr::PoisonState * pstate; // +0x150
    char _gap_154[28]; // +0x154
    BYTE g_bYouDi; // +0x170
    char _gap_171[3]; // +0x171
    float m_fFStime; // +0x174
    ArcLocaleMusic music; // +0x178
    char _gap_17C[14]; // +0x17C
    BYTE grayscale; // +0x18A
    BYTE underwater; // +0x18B
    BYTE rain; // +0x18C
    BYTE snow; // +0x18D
    BYTE watermagic; // +0x18E
    char _gap_18F[1]; // +0x18F
    gbFogParam fog; // +0x190
    char _gap_194[48]; // +0x194
    _BYTE reverse[32]; // +0x1C4
    // total size: 0x1E4 (484)

};

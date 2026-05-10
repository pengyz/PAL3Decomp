#pragma once
// Auto-generated: ArcLocale

#include "ArcLocaleMusic.h"
#include "ArcLocaleRole.h"
#include "RC_ARG.h"
#include "SceneInfo.h"

class gbFogParam;

class ArcLocale {
public:
    SceneInfo scene; // +0x0
    RC_ARG camera; // +0x84
    ArcLocaleRole player[5]; // +0xA0
    BYTE underctrl; // +0x12C
    char px_mdl[32]; // +0x12D
    char pstate[32]; // +0x150 (PlayerMgr::PoisonState)
    BYTE g_bYouDi; // +0x170
    float m_fFStime; // +0x174
    ArcLocaleMusic music; // +0x178
    BYTE grayscale; // +0x18A
    BYTE underwater; // +0x18B
    BYTE rain; // +0x18C
    BYTE snow; // +0x18D
    BYTE watermagic; // +0x18E
    gbFogParam fog; // +0x190
    BYTE reverse[32]; // +0x1C4
    // total size: 0x1E4 (484)

};

#pragma once
// Auto-generated: ArcLocale

#include "ArcLocaleMusic.h"
#include "ArcLocaleRole.h"
#include "RC_ARG.h"
#include "SceneInfo.h"
#include "gbFogParam.h"

class ArcLocale {
public:
    SceneInfo scene; // +0x0
    RC_ARG camera; // +0x84
    ArcLocaleRole player[5]; // +0xA0
    unsigned char underctrl; // +0x12C
    char px_mdl[32]; // +0x12D
    struct PoisonState {}; // nested type stub
    PoisonState pstate; // +0x150
    unsigned char g_bYouDi; // +0x170
    float m_fFStime; // +0x174
    ArcLocaleMusic music; // +0x178
    unsigned char grayscale; // +0x18A
    unsigned char underwater; // +0x18B
    unsigned char rain; // +0x18C
    unsigned char snow; // +0x18D
    unsigned char watermagic; // +0x18E
    gbFogParam fog; // +0x190
    unsigned char reverse[32]; // +0x1C4
    // total size: 0x1E4 (484)

};

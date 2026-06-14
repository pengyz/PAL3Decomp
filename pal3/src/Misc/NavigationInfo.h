#pragma once
// Auto-generated: NavigationInfo

#include "NavFaceLayer.h"
#include "NavTileLayer.h"

class NavigationInfo {
public:
    int m_numlayer; // +0x0
    NavTileLayer m_tilelayer[2]; // +0x4
    char _gap_00C[320]; // +0xC
    NavFaceLayer m_facelayer[2]; // +0x14C
    char _tail_154[24]; // +0x154
    // total size: 0x16C (364)

};

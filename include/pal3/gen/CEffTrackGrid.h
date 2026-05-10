#pragma once
// Auto-generated: CEffTrackGrid

#include "CEffGrid.h"

class t3DModel;

class CEffTrackGrid : public CEffGrid {
public:
    t3DModel * m_pTrack; // +0x10B8
    float m_fTrackSpeed; // +0x10BC
    float m_fTrackDecPart; // +0x10C0
    int m_nCurrTrackPos; // +0x10C4
    float m_fx; // +0x10C8
    float m_fy; // +0x10CC
    float m_fz; // +0x10D0
    // total size: 0x10D4 (4308)

};

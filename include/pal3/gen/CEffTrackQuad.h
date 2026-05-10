#pragma once
// Auto-generated: CEffTrackQuad

#include "CEffQuad.h"

class t3DModel;

class CEffTrackQuad : public CEffQuad {
public:
    t3DModel * m_pTrack; // +0x10B0
    float m_fTrackSpeed; // +0x10B4
    float m_fTrackDecPart; // +0x10B8
    int m_nCurrTrackPos; // +0x10BC
    float m_fx; // +0x10C0
    float m_fy; // +0x10C4
    float m_fz; // +0x10C8
    // total size: 0x10CC (4300)

};

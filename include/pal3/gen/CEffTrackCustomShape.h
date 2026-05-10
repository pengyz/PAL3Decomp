#pragma once
// Auto-generated: CEffTrackCustomShape

#include "CEffCustomShape.h"

class t3DModel;

class CEffTrackCustomShape : public CEffCustomShape {
public:
    t3DModel * m_pTrack; // +0xAC
    float m_fTrackSpeed; // +0xB0
    float m_fTrackDecPart; // +0xB4
    int m_nCurrTrackPos; // +0xB8
    float m_fx; // +0xBC
    float m_fy; // +0xC0
    float m_fz; // +0xC4
    // total size: 0xC8 (200)

};

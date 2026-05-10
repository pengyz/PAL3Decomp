#pragma once
// Auto-generated: CEffTrackCylinder

#include "CEffCylinder.h"

class t3DModel;

class CEffTrackCylinder : public CEffCylinder {
public:
    t3DModel * m_pTrack; // +0x10C4
    float m_fTrackSpeed; // +0x10C8
    float m_fTrackDecPart; // +0x10CC
    int m_nCurrTrackPos; // +0x10D0
    float m_fx; // +0x10D4
    float m_fy; // +0x10D8
    float m_fz; // +0x10DC
    // total size: 0x10E0 (4320)

};

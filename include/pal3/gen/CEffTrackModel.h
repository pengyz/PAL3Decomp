#pragma once
// Auto-generated: CEffTrackModel

#include "CEffModel.h"

class t3DModel;

class CEffTrackModel : public CEffModel {
public:
    t3DModel * m_pTrack; // +0x68
    float m_fTrackSpeed; // +0x6C
    float m_fTrackDecPart; // +0x70
    int m_nCurrTrackPos; // +0x74
    float m_fx; // +0x78
    float m_fy; // +0x7C
    float m_fz; // +0x80
    // total size: 0x84 (132)

};

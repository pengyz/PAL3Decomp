#pragma once
// Auto-generated: CEffTrackSParticle

#include "CEffSParticle.h"

class t3DModel;

class CEffTrackSParticle : public CEffSParticle {
public:
    t3DModel * m_pTrack; // +0x64
    float m_fTrackSpeed; // +0x68
    float m_fTrackDecPart; // +0x6C
    int m_nCurrTrackPos; // +0x70
    // total size: 0x74 (116)

};

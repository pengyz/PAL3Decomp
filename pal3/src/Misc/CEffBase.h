#include "CEffObj.h"
#pragma once
// Auto-generated: CEffBase

class CEffBase : public CEffObj {
public:
    char _gap_000[12]; // +0x0
    int m_nTaskIndex; // +0xC
    float m_fPrevTime; // +0x10
    float m_fDeltaTime; // +0x14
    char * m_pSegData; // +0x18
    float m_fDuration; // +0x1C
    float m_fTimeScale; // +0x20
    int m_nMaxTask; // +0x24
    int m_nSegments; // +0x28
    int m_nVertPerSeg; // +0x2C
    // total size: 0x30 (48)

};

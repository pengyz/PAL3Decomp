#pragma once
// Auto-generated: SkyboxEff

#include "EffModeParam.h"

class SkyboxEffTex;

class SkyboxEff {
public:
    gbRenderEffect * m_pEffectNormal; // +0x0
    SkyboxEffTex * m_pEffTex; // +0x4
    int m_nFrameNum; // +0x8
    float m_fWaitTime; // +0xC
    float m_fValidTime; // +0x10
    float m_fps; // +0x14
    float m_fSizeScale; // +0x18
    float m_nEffWidth; // +0x1C
    float m_nEffHeight; // +0x20
    EffModeParam m_eEffMode; // +0x24
    gbVec3D m_vHalfSize; // +0x30
    float m_fTime; // +0x3C
    float m_fPassTime; // +0x40
    int m_nCurFrame; // +0x44
    float m_fWidth; // +0x48
    float m_fHeight; // +0x4C
    unsigned char m_bIsTime; // +0x50
    unsigned char m_bOver; // +0x51
    unsigned char m_bValid; // +0x52
    unsigned char m_bDelyTime; // +0x53
    float m_fNoteTime; // +0x54
    unsigned long m_nameCrc; // +0x58
    gbRenderEffect * m_pSkyboxEff; // +0x5C
    gbVec3D m_vRender[4]; // +0x60
    // total size: 0x90 (144)

};

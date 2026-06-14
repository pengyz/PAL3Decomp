#pragma once
// Auto-generated: SkyboxEff

#include "EffModeParam.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbengine_types.h"

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
    char _gap_028[8]; // +0x28
    gbVec3D m_vHalfSize; // +0x30
    char _gap_034[8]; // +0x34
    float m_fTime; // +0x3C
    float m_fPassTime; // +0x40
    int m_nCurFrame; // +0x44
    float m_fWidth; // +0x48
    float m_fHeight; // +0x4C
    BYTE m_bIsTime; // +0x50
    BYTE m_bOver; // +0x51
    BYTE m_bValid; // +0x52
    BYTE m_bDelyTime; // +0x53
    float m_fNoteTime; // +0x54
    UINT m_nameCrc; // +0x58
    gbRenderEffect * m_pSkyboxEff; // +0x5C
    gbVec3D m_vRender[4]; // +0x60
    char _tail_070[32]; // +0x70
    // total size: 0x90 (144)

};

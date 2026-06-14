#pragma once
// Auto-generated: RoleShadow

#include "gbengine/gbMesh.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"

class FrameTex;

class RoleShadow {
public:
    char _gap_000[4]; // +0x0
    gbTexture * m_shadowtex; // +0x4
    gbRenderEffect * m_effect; // +0x8
    gbRenderEffect * m_effectFog; // +0xC
    gbRenderEffect * m_effectFrame; // +0x10
    gbGeomQuad m_quad[77]; // +0x14
    char _gap_148[4928]; // +0x148
    gbGeomQuad m_CtrlRoleQuad; // +0x1488
    char _gap_148C[64]; // +0x148C
    FrameTex * m_pFrameShadow; // +0x14CC
    int m_nFrameNum; // +0x14D0
    int m_nCurFrame; // +0x14D4
    int m_nFrameFPS; // +0x14D8
    BYTE m_bFrameShadow; // +0x14DC
    char _tail_14DD[3]; // +0x14DD
    // total size: 0x14E0 (5344)

    int InitParticles(); // 0x0044D290
    int InitFromTemplate(int nVal); // 0x00453FA0
    int CreateFromTemplate(unsigned __int8 pData); // 0x00454420
    int LoadQuadData(int *p_DWORD); // 0x00524E00
    int UpdateShadow(); // 0x00524F90
};

#pragma once
// Auto-generated: RoleShadow

class FrameTex;

class RoleShadow {
public:
    gbTexture * m_shadowtex; // +0x4
    gbRenderEffect * m_effect; // +0x8
    gbRenderEffect * m_effectFog; // +0xC
    gbRenderEffect * m_effectFrame; // +0x10
    gbGeomQuad m_quad[77]; // +0x14
    gbGeomQuad m_CtrlRoleQuad; // +0x1488
    FrameTex * m_pFrameShadow; // +0x14CC
    int m_nFrameNum; // +0x14D0
    int m_nCurFrame; // +0x14D4
    int m_nFrameFPS; // +0x14D8
    unsigned char m_bFrameShadow; // +0x14DC
    // total size: 0x14E0 (5344)

};

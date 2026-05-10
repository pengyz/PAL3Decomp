#pragma once
// Auto-generated: CCBStageShadow

class CCBStage;
class gbTextureArray;

class CCBStageShadow {
public:
    CCBStage * m_pStage; // +0x0
    gbTexture * m_pTexture; // +0x4
    gbRenderEffect * m_pEffect; // +0x8
    gbTextureArray * m_pTextureArray; // +0xC
    gbGeomQuad m_ShadowInitQuad[11]; // +0x10
    gbGeomQuad m_ShadowQuad[11]; // +0x2FC
    float m_fShadowRadius[11]; // +0x5E8
    // total size: 0x614 (1556)

    CCBStageShadow(); // 0x00511EE0
    ~CCBStageShadow(); // 0x00511F90
    char Reset(); // 0x00511FC0
    void Create(); // 0x00512080
    float * Destroy(); // 0x00512240
    static int Update(); // 0x005122E0
    static int Render(); // 0x005122F0
    static void FillShadowQuad(); // 0x00512300
};

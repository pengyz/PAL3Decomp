#pragma once
// Auto-generated: CCBStageShadow

#include "gbengine/gbMesh.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"

class CCBStage;

class CCBStageShadow {
public:
    CCBStage * m_pStage; // +0x0
    gbTexture * m_pTexture; // +0x4
    gbRenderEffect * m_pEffect; // +0x8
    gbTextureArray * m_pTextureArray; // +0xC
    gbGeomQuad m_ShadowInitQuad[11]; // +0x10
    char _gap_03C[704]; // +0x3C
    gbGeomQuad m_ShadowQuad[11]; // +0x2FC
    char _gap_328[704]; // +0x328
    float m_fShadowRadius[11]; // +0x5E8
    // total size: 0x614 (1556)

    float * UpdateShadowMesh(); // 0x00511E80
    CCBStageShadow(); // 0x00511EE0
    void _CCBStageShadow(); // 0x00511F90
    void Reset(); // 0x00511FC0
    void Create(); // 0x00512080
    float * Destroy(); // 0x00512240
    void Update(); // 0x005122E0
    void Render(); // 0x005122F0
    void FillShadowQuad(); // 0x00512300
};

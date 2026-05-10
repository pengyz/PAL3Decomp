#pragma once
// Auto-generated: SceneMgr

#include "RoleSystem.h"

class SceneMgr {
public:
    gbGfxManager * m_pGfxMgr; // +0x0
    gbSceneGraph * m_pSceneRoot; // +0x4
    gbRenderEffect * m_pAddEffect2; // +0x8
    gbRenderEffect * m_pAlphaEffect2; // +0xC
    gbRenderEffect * m_pAddEffect; // +0x10
    gbRenderEffect * m_pAlphaEffect; // +0x14
    gbCamera * m_pCamera; // +0x18
    char _preArray[620]; // +0x1C
    char m_slot0[1408]; // +0x288
    char m_slot1[1408]; // +0x808
    char m_slot2[1408]; // +0xD88
    char m_slot3[1408]; // +0x1308
    char _gap_1888[840]; // +0x1888
    RoleSystem m_RoleSystem[5]; // +0x1BD0
    int m_pGameData; // +0xC5D0
    int _c5d4; // +0xC5D4
    int m_pCameraCtrl; // +0xC5D8
    int m_pScriptCtrl; // +0xC5DC
    char _gap_c5e0[856]; // +0xC5E0
    int m_nCameraState; // +0xC938
    char _gap_c93c[108]; // +0xC93C
    char m_szUIString[512]; // +0xC9A8
    char _gap_cba8[356]; // +0xCBA8
    float m_fMoveParam; // +0xCD0C
    char _gap_cd10[1612]; // +0xCD10
    int m_pCollisionNode; // +0xD35C
    char _tail[4]; // +0xD360
    // total size: 0xD364 (54116)

    void * Create(gbGfxManager *gfxMgr, gbCamera *cam, gbSceneGraph *pRoot); // 0x004CDA10
    char RenderAll(); // 0x004CDBF0
    char RenderUpdate(); // 0x004CDC20
};

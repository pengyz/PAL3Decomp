#pragma once
// Auto-generated: SceneMgr

#include "RoleSystem.h"
#include "SceneMgrCamBlock.h"
#include "SceneMgrSlot.h"

class CCBAI;
class CGameData;
class CameraCtrl;
class PalScriptMgr;

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
    SceneMgrSlot m_slot[4]; // +0x288
    char m_extraSlot[792]; // +0x1888
    CCBAI * m_pCombatAI; // +0x1BA0
    char _gap_1BA4[36]; // +0x1BA4
    char m_bGameFlags[5]; // +0x1BC8
    char _gap_1BCD[3]; // +0x1BCD
    RoleSystem m_RoleSystem[5]; // +0x1BD0
    CGameData * m_pGameData; // +0xC5D0
    int _unkC5D4; // +0xC5D4
    CameraCtrl * m_pCameraCtrl; // +0xC5D8
    PalScriptMgr * m_pScriptCtrl; // +0xC5DC
    SceneMgrCamBlock m_camBlock; // +0xC5E0
    int m_nCameraState; // +0xC938
    char _gap_C93C[108]; // +0xC93C
    char m_szUIString[512]; // +0xC9A8
    char _gap_CBA8[356]; // +0xCBA8
    float m_fMoveParam; // +0xCD0C
    char _gap_CD10[1612]; // +0xCD10
    gbGeomNode * m_pCollisionNode; // +0xD35C
    char _end[4]; // +0xD360
    // total size: 0xD364 (54116)

    void * Create(gbGfxManager *gfxMgr, gbCamera *cam, gbSceneGraph *pRoot); // 0x004CDA10
    char RenderAll(); // 0x004CDBF0
    char RenderUpdate(); // 0x004CDC20
};

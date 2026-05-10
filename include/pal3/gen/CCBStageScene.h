#pragma once
// Auto-generated: CCBStageScene

#include "ECBBattleFieldAttr.h"
#include "ECBFiveMagic.h"
#include "ECBForce.h"

class CCBStage;
class CUtil;
class gbTextureArray;
class gbVisNode;

class CCBStageScene {
public:
    CCBStage * m_pStage; // +0x0
    CUtil * m_pUtil; // +0x4
    gbVec3D m_vecFiveLineup[7]; // +0x8
    gbVec3D m_vecInitFiveLineup[7]; // +0x5C
    gbVec3D m_vecEnemyLineup[7]; // +0xB0
    gbVec3D m_vecInitEnemyLineup[7]; // +0x104
    unsigned char m_bLoaded; // +0x158
    char m_sLastScene[256]; // +0x159
    gbGeomNode * m_pGeomNode; // +0x25C
    gbGeomNode * m_pCvd; // +0x260
    gbVisNode * m_pLights; // +0x264
    gbGeomNode * m_pPointer; // +0x268
    gbGeomNode * m_pCorpse[11]; // +0x26C
    gbGeomNode * m_pFling; // +0x298
    gbVec3D m_vecFling; // +0x29C
    gbVec3D m_rotFling; // +0x2A8
    unsigned char m_bShowFling; // +0x2B4
    gbRenderEffect * m_pFiveLineupEffect; // +0x2B8
    gbTexture * m_pFiveLineupTexture; // +0x2BC
    gbTextureArray * m_pFiveLineupTextureArray; // +0x2C0
    gbTexture * m_pFiveLineupCenterTexture; // +0x2C4
    gbTextureArray * m_pFiveLineupCenterTextureArray; // +0x2C8
    gbGeomQuad m_FiveLineupQuad; // +0x2CC
    gbGeomQuad m_FiveLineupCenterQuad; // +0x310
    gbGeomQuad m_EnemyFiveLineupQuad; // +0x354
    gbVec3D m_vecFiveLineupPos; // +0x398
    gbVec3D m_vecFiveLineupInitPos; // +0x3A4
    float m_fFiveLineupRadius; // +0x3B0
    float m_fFiveLineupInitRadius; // +0x3B4
    float m_fFiveLineupRoll; // +0x3B8
    float m_fFiveLineupInitRoll; // +0x3BC
    gbVec3D m_vecEnemyFiveLineupPos; // +0x3C0
    float m_fEnemyFiveLineupRadius; // +0x3CC
    float m_fEnemyFiveLineupRoll; // +0x3D0
    gbVec3D m_vecPointerPos; // +0x3D4
    unsigned char m_bShowPointer; // +0x3E0
    unsigned char m_bShowAxis; // +0x3E1
    unsigned char m_bShowRoleIndex; // +0x3E2
    unsigned char m_bShowFiveLineup; // +0x3E3
    unsigned char m_bFiveLineupSelected; // +0x3E4
    ECBFiveMagic m_eSceneFiveMagicAttrib; // +0x3E8
    ECBBattleFieldAttr m_eBattleFieldAttr; // +0x3EC
    ECBForce m_eBFAForce; // +0x3F0
    // total size: 0x3F4 (1012)

    int Update(); // 0x0050FE50
    char Reset(); // 0x00510180
    int Create(); // 0x00510540
    void Destroy(); // 0x00510610
    int Init(); // 0x005107C0
    int SetBattleFieldAttr(); // 0x00510C80
    void GetBattleFieldSubdueAttr(gbMatrixStack *a2); // 0x00510CA0
    void GetBFASubdueFM(); // 0x00510E00
    char IsSameBattleFieldAttr(); // 0x00510F50
    void LoadPointer(char a2); // 0x00511030
    bool LoadFlingNode(); // 0x00511110
    int SetFlingRotX(); // 0x005112B0
    _DWORD * SetFlingRotY(); // 0x005112F0
    char Render(); // 0x00511790
    char ShowAxis(); // 0x00511970
    char ShowRoleIndex(); // 0x00511AE0
    static int ShowEnemyFiveLineupEx(); // 0x00511C00
    static int IsFiveLineupUnderMouse(); // 0x00511C10
    static void ResetFiveLineupToInit(); // 0x00511C20
    static void ResetRolePosToInit(); // 0x00511C30
    static int LoadScene(); // 0x00511C40
    static int DestroyScene(); // 0x00511C50
    static int SaveRolePos(); // 0x00511C90
    static int LoadFiveLineupData(); // 0x00511CE0
    static int SaveFiveLineupDate(); // 0x00511CF0
};

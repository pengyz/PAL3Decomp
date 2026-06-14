#pragma once
// Auto-generated: CCBStageScene

#include "ECBBattleFieldAttr.h"
#include "ECBFiveMagic.h"
#include "ECBForce.h"
#include "gbengine/gbGeomNode.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbengine_internal.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbVisNode.h"

class CCBStage;
class CUtil;

class CCBStageScene {
public:
    CCBStage * m_pStage; // +0x0
    CUtil * m_pUtil; // +0x4
    gbVec3D m_vecFiveLineup[7]; // +0x8
    char _gap_024[56]; // +0x24
    gbVec3D m_vecInitFiveLineup[3]; // +0x5C
    char _gap_068[24]; // +0x68
    int m_nRender; // +0x80
    float m_fLineupCamY; // +0x84
    float m_fLineupCamZ; // +0x88
    float m_fRender; // +0x8C
    float m_fLineupPrevY; // +0x90
    float m_fLineupPrevZ; // +0x94
    float m_fLineupDefaultX; // +0x98
    float m_fLineupDefaultY; // +0x9C
    float m_fLineupDefaultZ; // +0xA0
    float m_fLineupExtraX; // +0xA4
    float m_fLineupExtraY; // +0xA8
    float m_fLineupExtraZ; // +0xAC
    gbVec3D m_vecEnemyLineup[7]; // +0xB0
    char _gap_0CC[56]; // +0xCC
    gbVec3D m_vecInitEnemyLineup[7]; // +0x104
    char _gap_120[56]; // +0x120
    BYTE m_bLoaded; // +0x158
    char m_sLastScene[256]; // +0x159
    char _gap_259[3]; // +0x259
    gbGeomNode * m_pGeomNode; // +0x25C
    gbGeomNode * m_pCvd; // +0x260
    gbVisNode * m_pLights; // +0x264
    gbGeomNode * m_pPointer; // +0x268
    gbGeomNode * m_pCorpse[11]; // +0x26C
    char _gap_270[40]; // +0x270
    gbGeomNode * m_pFling; // +0x298
    float m_vecFling; // +0x29C
    int m_nLoadPointer; // +0x2A0
    int m_nFlingState; // +0x2A4
    float m_rotFling; // +0x2A8
    float m_fDirSinA; // +0x2AC
    float m_fBlendA; // +0x2B0
    BYTE m_bShowFling; // +0x2B4
    char _gap_2B5[3]; // +0x2B5
    gbRenderEffect * m_pFiveLineupEffect; // +0x2B8
    gbTexture * m_pFiveLineupTexture; // +0x2BC
    gbTextureArray * m_pFiveLineupTextureArray; // +0x2C0
    gbTexture * m_pFiveLineupCenterTexture; // +0x2C4
    gbTextureArray * m_pFiveLineupCenterTextureArray; // +0x2C8
    gbGeomQuad * m_FiveLineupQuad; // +0x2CC
    float m_fDirSinB; // +0x2D0
    float m_fBlendB; // +0x2D4
    float m_fDirCosB; // +0x2D8
    float m_fBlendRectAX; // +0x2DC
    float m_fBlendRectAY; // +0x2E0
    float m_fBlendRectAW; // +0x2E4
    float m_fBlendRectAH; // +0x2E8
    BYTE m_bLoadPointer; // +0x2EC
    BYTE m_nPointerIndex1; // +0x2ED
    BYTE m_nPointerIndex2; // +0x2EE
    BYTE m_nPointerData; // +0x2EF
    int m_nInit; // +0x2F0
    int m_nCamState; // +0x2F4
    float m_fCamPosX; // +0x2F8
    float m_fCamPosZ; // +0x2FC
    float m_fInit; // +0x300
    float m_fCamTargX; // +0x304
    float m_fCamTargZ; // +0x308
    float m_fInitBlend; // +0x30C
    gbGeomQuad * m_FiveLineupCenterQuad; // +0x310
    float m_fBlendTime; // +0x314
    int m_nBlendState; // +0x318
    float m_fBlendSpeed; // +0x31C
    float m_fBlendRectBX; // +0x320
    float m_fBlendRectBY; // +0x324
    float m_fBlendRectBW; // +0x328
    float m_fBlendRectBH; // +0x32C
    int m_nReset; // +0x330
    float m_fDirSinC; // +0x334
    float m_fBlendC; // +0x338
    float m_fDirCosC; // +0x33C
    float m_fDirSinD; // +0x340
    float m_fBlendD; // +0x344
    float m_fDirCosD; // +0x348
    float m_fDirSinE; // +0x34C
    float m_fBlendE; // +0x350
    gbGeomQuad * m_EnemyFiveLineupQuad; // +0x354
    float m_fDirSinF; // +0x358
    float m_fBlendF; // +0x35C
    float m_fDirCosF; // +0x360
    float m_fBlendWeight0; // +0x364
    float m_fBlendWeight1; // +0x368
    float m_fBlendWeight2; // +0x36C
    float m_fBlendWeight3; // +0x370
    char _gap_374[4]; // +0x374
    float m_fCurAxisX; // +0x378
    float m_fCurAxisY; // +0x37C
    float m_fCurAxisZ; // +0x380
    float m_fInitAxisX; // +0x384
    float m_fInitAxisY; // +0x388
    float m_fInitAxisZ; // +0x38C
    float m_fCurRotParam; // +0x390
    float m_fInitRotParam; // +0x394
    gbVec3D m_vecFiveLineupPos; // +0x398
    char _gap_39C[8]; // +0x39C
    gbVec3D m_vecFiveLineupInitPos; // +0x3A4
    char _gap_3A8[8]; // +0x3A8
    float m_fFiveLineupRadius; // +0x3B0
    float m_fFiveLineupInitRadius; // +0x3B4
    float m_fFiveLineupRoll; // +0x3B8
    float m_fFiveLineupInitRoll; // +0x3BC
    gbVec3D m_vecEnemyFiveLineupPos; // +0x3C0
    char _gap_3C4[8]; // +0x3C4
    float m_fEnemyFiveLineupRadius; // +0x3CC
    float m_fEnemyFiveLineupRoll; // +0x3D0
    gbVec3D m_vecPointerPos; // +0x3D4
    char _gap_3D8[8]; // +0x3D8
    BYTE m_bShowPointer; // +0x3E0
    BYTE m_bShowAxis; // +0x3E1
    BYTE m_bShowRoleIndex; // +0x3E2
    BYTE m_bShowFiveLineup; // +0x3E3
    BYTE m_bFiveLineupSelected; // +0x3E4
    char _gap_3E5[3]; // +0x3E5
    ECBFiveMagic m_eSceneFiveMagicAttrib; // +0x3E8
    ECBBattleFieldAttr m_eBattleFieldAttr; // +0x3EC
    ECBForce m_eBFAForce; // +0x3F0
    // total size: 0x3F4 (1012)

    int ResetSceneState(); // 0x004FBA70
    CCBStageScene(CCBStage *pCBStage); // 0x0050FD00
    void Update(); // 0x0050FE50
    CCBStageScene(); // 0x0050FEE0
    void _CCBStageScene(); // 0x005100D0
    void Reset(); // 0x00510180
    bool Create(); // 0x00510540
    void Destroy(); // 0x00510610
    bool Init(); // 0x005107C0
    void SetBattleFieldAttr(); // 0x00510C80
    void GetBattleFieldSubdueAttr(gbMatrixStack *pMatrixStack); // 0x00510CA0
    void GetBFASubdueFM(); // 0x00510E00
    bool IsSameBattleFieldAttr(); // 0x00510F50
    void LoadPointer(char pData); // 0x00511030
    bool LoadFlingNode(); // 0x00511110
    void SetFlingRotX(); // 0x005112B0
    int * SetFlingRotY(); // 0x005112F0
    bool LoadModel(const char *pszName); // 0x00511340
    void Render(); // 0x00511790
    void ShowAxis(); // 0x00511970
    void ShowRoleIndex(); // 0x00511AE0
    void ShowEnemyFiveLineupEx(unsigned __int8 byAlpha); // 0x00511C00
    bool IsFiveLineupUnderMouse(); // 0x00511C10
    void ResetFiveLineupToInit(); // 0x00511C20
    void ResetRolePosToInit(); // 0x00511C30
    bool LoadScene(const char *const pFilename); // 0x00511C40
    void DestroyScene(); // 0x00511C50
    bool SaveRolePos(); // 0x00511C90
    bool LoadFiveLineupData(); // 0x00511CE0
    bool SaveFiveLineupDate(); // 0x00511CF0
    int * InitCameraPositions(); // 0x0052B1E0
    void CleanupCamera(); // 0x0052B2A0
    int SetCameraDefaults(); // 0x0052B350
    char CreateCamera(); // 0x0052B3B0
};

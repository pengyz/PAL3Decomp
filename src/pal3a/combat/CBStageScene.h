#ifndef PAL3A_CBSTAGESCENE_H
#define PAL3A_CBSTAGESCENE_H

#include "pal3a_types.h"

class CCBStageScene {
public:
    char _data[1012];

    ECBBattleFieldAttr GetBattleFieldSubdueAttr();
    ECBFiveMagic GetBFASubdueFM();
    void Update();
    void Reset();
    void LoadCorpse();
    void ShowRoleIndex();
    void ShowAxis();
    ~CCBStageScene();
    bool LoadScene(char * pFilename);
    void ResetFiveLineupToInit();
    bool SaveRolePos();
    bool IsFiveLineupUnderMouse();
    CCBStageScene(CCBStage * pStage);
    bool Create();
    bool LoadFiveLineupData();
    void SetBattleFieldAttr(ECBBattleFieldAttr attr, ECBForce force);
    void ShowFiveLineupEx(uchar byAlpha);
    void ShowEnemyFiveLineupEx(uchar byAlpha);
    bool Destroy();
    void LoadFlingNode(ulong dwItemID);
    void ResetRolePosToInit();
    bool IsSameBattleFieldAttr(ECBFiveMagic FM);
    bool Init();
    void UpdateFiveLineupData();
    bool LoadRolePos();
    void Render(gbMatrixStack * pView);
    void DestroyScene();
    bool SaveFiveLineupDate();
    void LoadPointer();
    void SetFlingRotY(float yrot);
    void SetFlingRotX(float xrot);
    void SetFlingRotZ(float zrot);
};

#endif // PAL3A_CBSTAGESCENE_H

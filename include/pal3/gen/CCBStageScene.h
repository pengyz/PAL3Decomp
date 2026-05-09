#pragma once
// Auto-generated from IDA decomp - CCBStageScene
// 28 methods

class CCBStageScene {
public:
    int Update();  // 0x0050FE50
    char CCBStageScene();  // 0x0050FEE0
    char ~CCBStageScene();  // 0x005100D0
    char Reset();  // 0x00510180
    int Create();  // 0x00510540
    void Destroy();  // 0x00510610
    int Init();  // 0x005107C0
    int SetBattleFieldAttr();  // 0x00510C80
    void GetBattleFieldSubdueAttr(gbMatrixStack *a2);  // 0x00510CA0
    void GetBFASubdueFM();  // 0x00510E00
    char IsSameBattleFieldAttr();  // 0x00510F50
    void LoadPointer(char a2);  // 0x00511030
    bool LoadFlingNode();  // 0x00511110
    int SetFlingRotX();  // 0x005112B0
    static _DWORD *__thiscall(_DWORD *this) SetFlingRotY();  // 0x005112F0
    char Update();  // 0x00511690
    char Render();  // 0x00511790
    char ShowAxis();  // 0x00511970
    char ShowRoleIndex();  // 0x00511AE0
    static int() ShowEnemyFiveLineupEx();  // 0x00511C00
    static int() IsFiveLineupUnderMouse();  // 0x00511C10
    static void() ResetFiveLineupToInit();  // 0x00511C20
    static void() ResetRolePosToInit();  // 0x00511C30
    static int() LoadScene();  // 0x00511C40
    static int() DestroyScene();  // 0x00511C50
    static int() SaveRolePos();  // 0x00511C90
    static int() LoadFiveLineupData();  // 0x00511CE0
    static int() SaveFiveLineupDate();  // 0x00511CF0
};

#pragma once
// Auto-generated: RoleSystem

class RoleAtt;

class RoleSystem {
public:
    char _gap_0000[4]; // +0x0
    float m_fTargetX; // +0x4
    float m_fTargetY; // +0x8
    float m_fTargetZ; // +0xC
    int _d010; // +0x10
    int _d014; // +0x14
    char _gap_0018[136]; // +0x18
    float m_fPosX; // +0xA0
    float m_fPosY; // +0xA4
    float m_fPosZ; // +0xA8
    char m_nFacing; // +0xAC
    char m_nActionState; // +0xAD
    char m_nAnimState; // +0xAE
    char _gap_00AF[453]; // +0xAF
    int m_nState; // +0x274
    char _gap_0278[4]; // +0x278
    int m_nBaseStats[12]; // +0x27C
    char _gap_02AC[176]; // +0x2AC
    RoleAtt * m_pEquipAtt0; // +0x35C
    char _gap_0360[8]; // +0x360
    RoleAtt * m_pEquipAtt1; // +0x368
    char _gap_036C[8]; // +0x36C
    RoleAtt * m_pEquipAtt2; // +0x374
    char _gap_0378[8]; // +0x378
    RoleAtt * m_pEquipAtt3; // +0x380
    char _gap_0384[8]; // +0x384
    RoleAtt * m_pEquipAtt4; // +0x38C
    char _gap_0390[8]; // +0x390
    RoleAtt * m_pSelfAtt; // +0x398
    int m_nComputedStats[12]; // +0x39C
    int m_nDisplayStats[12]; // +0x3CC
    char _gap_03FC[208]; // +0x3FC
    int m_nPathState; // +0x4CC
    int m_nPathStep; // +0x4D0
    int _d4D4; // +0x4D4
    float m_fPathTargetX; // +0x4D8
    float m_fPathTargetY; // +0x4DC
    float m_fPathTargetZ; // +0x4E0
    float _f4E4; // +0x4E4
    int _d4E8; // +0x4E8
    int m_nPrevMoveMode; // +0x4EC
    int m_nMoveMode; // +0x4F0
    int m_nMoveSubMode; // +0x4F4
    char _gap_04F8[12]; // +0x4F8
    int m_nCoreState; // +0x504
    int m_nTransformState; // +0x508
    float _f50C; // +0x50C
    float m_fRotAxisX; // +0x510
    float m_fRotAxisY; // +0x514
    float m_fRotAxisZ; // +0x518
    int _d51C; // +0x51C
    int _d520; // +0x520
    char _gap_0524[28]; // +0x524
    float m_fRotAngle; // +0x540
    float _f544; // +0x544
    float _f548; // +0x548
    char _gap_054C[32]; // +0x54C
    int _d56C; // +0x56C
    int m_nRoleCount; // +0x570
    char _gap_0574[44]; // +0x574
    gbGeomNode * m_pRenderObj; // +0x5A0
    char m_bRenderFlag1; // +0x5A4
    char m_bRenderFlag2; // +0x5A5
    char _gap_05A6[18]; // +0x5A6
    int m_nRetryCount; // +0x5B8
    char _gap_05BC[12]; // +0x5BC
    float m_fMoveTargetX; // +0x5C8
    float m_fMoveTargetY; // +0x5CC
    float m_fMoveTargetZ; // +0x5D0
    char _end[7212]; // +0x5D4
    // total size: 0x2200 (8704)

    int * Init(); // 0x0040BE50
    int LoadData(char a2); // 0x0040BE80
    static int CheckVisible(int a1); // 0x00410E40
    void RenderRole(void *pStack, int a3); // 0x00412400
    int UpdateTransform(); // 0x00412710
    int UpdatePath(int a2); // 0x00412940
    int MoveRole(float *pPos, int a3, int a4, int a5); // 0x00412E60
    char UpdateRole(int a2, int a3, int a4); // 0x00413010
    void GetPosition(void *pOut, int a3); // 0x00414980
    int PathFind(float *pTarget); // 0x00414A30
    void UpdateAnimation(int a2); // 0x00416790
    int GetActiveRole(); // 0x00416F10
    char SetState(int state); // 0x00417AC0
    int GetDirection(float *pOut); // 0x00419A80
    int GetCount(); // 0x0041BBE0
    int SetActive(int a2); // 0x0041C170
    int GetRolePtr(int index); // 0x00420F30
};

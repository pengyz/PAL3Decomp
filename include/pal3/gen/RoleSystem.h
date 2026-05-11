#pragma once
// Auto-generated: RoleSystem

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
    char _gap_00AC[456]; // +0xAC
    int m_nState; // +0x274
    char _gap_0278[596]; // +0x278
    int _d4CC; // +0x4CC
    int _d4D0; // +0x4D0
    int _d4D4; // +0x4D4
    int _d4D8; // +0x4D8
    float _f4DC; // +0x4DC
    int _d4E0; // +0x4E0
    float _f4E4; // +0x4E4
    int _d4E8; // +0x4E8
    int _d4EC; // +0x4EC
    int _d4F0; // +0x4F0
    int _d4F4; // +0x4F4
    char _gap_04F8[12]; // +0x4F8
    int m_nCoreState; // +0x504
    int _d508; // +0x508
    float _f50C; // +0x50C
    float _f510; // +0x510
    float _f514; // +0x514
    float _f518; // +0x518
    int _d51C; // +0x51C
    int _d520; // +0x520
    char _gap_0524[28]; // +0x524
    float _f540; // +0x540
    float _f544; // +0x544
    float _f548; // +0x548
    char _gap_054C[32]; // +0x54C
    int _d56C; // +0x56C
    int m_nRoleCount; // +0x570
    char _gap_0574[68]; // +0x574
    int _d5B8; // +0x5B8
    char _gap_05BC[20]; // +0x5BC
    int _d5D0; // +0x5D0
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

#pragma once
// Auto-generated from IDA decomp - RoleSystem
// 17 methods

class RoleSystem {
public:
    static int *__thiscall(RoleSystem *this) Init();  // 0x0040BE50
    int LoadData(char a2);  // 0x0040BE80
    static int CheckVisible(int a1);  // 0x00410E40
    void RenderRole(void *pStack, int a3);  // 0x00412400
    int UpdateTransform();  // 0x00412710
    int UpdatePath(int a2);  // 0x00412940
    int MoveRole(float *pPos, int a3, int a4, int a5);  // 0x00412E60
    char UpdateRole(int a2, int a3, int a4);  // 0x00413010
    void GetPosition(void *pOut, int a3);  // 0x00414980
    int PathFind(float *pTarget);  // 0x00414A30
    void UpdateAnimation(int a2);  // 0x00416790
    int GetActiveRole();  // 0x00416F10
    char SetState(int state);  // 0x00417AC0
    int GetDirection(float *pOut);  // 0x00419A80
    int GetCount();  // 0x0041BBE0
    int SetActive(int a2);  // 0x0041C170
    int GetRolePtr(int index);  // 0x00420F30
};

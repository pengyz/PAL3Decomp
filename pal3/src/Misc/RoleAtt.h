#pragma once
// Auto-generated: RoleAtt

#include "gbengine/gbVFileSystem.h"

class UIWnd;

class RoleAtt {
public:
    // vtable (7 methods, order matches binary layout)

    UINT id; // +0x0
    WORD type; // +0x4
    char Remark[512]; // +0x6
    char ModelID[30]; // +0x206
    char ImageID[30]; // +0x224
    char _gap_242[2]; // +0x242
    int att[5]; // +0x244
    char name[32]; // +0x258
    float lv; // +0x278
    int rolevalue[12]; // +0x27C
    _BYTE fightstate[31]; // +0x2AC
    char _gap_2CB[1]; // +0x2CB
    float RoundNum; // +0x2CC
    BYTE SAID; // +0x2D0
    char _gap_2D1[3]; // +0x2D1
    float Escape; // +0x2D4
    WORD haogan[5]; // +0x2D8
    char _gap_2E2[2]; // +0x2E2
    float exp; // +0x2E4
    WORD gold; // +0x2E8
    char _gap_2EA[2]; // +0x2EA
    UINT NormalAtkID; // +0x2EC
    BYTE height; // +0x2F0
    BYTE move; // +0x2F1
    BYTE attackrange; // +0x2F2
    BYTE speed1; // +0x2F3
    BYTE speed2; // +0x2F4
    char _gap_2F5[3]; // +0x2F5
    UINT skill[4]; // +0x2F8
    _BYTE skill_lv[3]; // +0x308
    char _gap_30B[1]; // +0x30B
    int RoleQiAdd; // +0x30C
    float append[10]; // +0x310
    UINT normalplunder; // +0x338
    short normalplundernum; // +0x33C
    char _gap_33E[2]; // +0x33E
    UINT shikuai; // +0x340
    UINT shikuaiskill; // +0x344
    short shikuaisucc; // +0x348
    short stealmoney; // +0x34A
    UINT steal; // +0x34C
    short stealnum; // +0x350
    short getmoney; // +0x352
    // total size: 0x354 (852)

    virtual void ShowWindow(); // 0x00451740
    virtual void ** Render(); // 0x004512F0
    virtual int HandleInput(int nVal, int nVal2); // 0x004515E0
    virtual void Destroy(); // 0x00451320
    virtual int OnMessage(int nVal, LPCSTR lpString1, int nVal2); // 0x004515A0
    static void _RoleAtt(UIWnd *pWnd); // 0x00450EB0
    BOOL IsValid(); // 0x00450F80
    void FormatAttributeText(); // 0x00457F90
    void LoadGeomNode(int a2); // 0x0052F8E0
    void LoadModelAndInit(); // 0x00530810
    int SetSAIDAndImage(int *pnVal); // 0x00530960
    void ApplySpeedFactor(float fVal); // 0x00531010
    void UpdateTimedBuff(float fDelta); // 0x005310C0
    char InterpolateStats(int nVal); // 0x00531160
    int SetPageParam(int nVal); // 0x005322D0
    int SetPageParam2(int nVal); // 0x005322E0
    int SwitchPage(int nPageIdx, int nParam); // 0x005322F0
    int ResetNameField(); // 0x00533DB0
    void UpdatePosition(float fX, float fY, float fZ); // 0x00533FE0
    void SetPositionFromInts(int nX, int nY, int nZ); // 0x00534210
    void InterpolateMotion(float f1, float f2, float f3, float f4, float f5); // 0x00534450
    void UpdateDirectionalMotion(gbVec3D pData, float fVal, float fVal2); // 0x00534810
    int SetFightState(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, char pData, char pData2); // 0x00534BA0
    int ResetFightState(); // 0x00534BF0
    double UpdateOscillation(); // 0x00534C50
};

#pragma once
// Auto-generated from IDA decomp - CEffMgr
// 10 methods

class CEffMgr {
public:
    static char() CEffMgr();  // 0x004CE100
    static char() ~CEffMgr();  // 0x004CE2A0
    int Init(int a2, int a3, int a4, int a5, int a6);  // 0x004CE340
    char Render(int a2);  // 0x004CE580
    static int SetTimeScale(int a1);  // 0x004CE5F0
    static char CreateEff(int a1);  // 0x004CE690
    int RunEffGroup(const char *a2, int a3, const char *a4);  // 0x004CEDA0
    int IsAllEffGroupStop(const char *a2, int a3, const char *a4);  // 0x004CF100
    int CopyObjInGroup(const char *a2, int a3, const char *a4);  // 0x004CF7C0
    static _DWORD *__thiscall(CEffMgr *this) Reset();  // 0x004D58A0
};

#pragma once
// Auto-generated from IDA decomp - CEffectSystem
// 16 methods

class CEffectSystem {
public:
    static _DWORD *__thiscall(_DWORD *this, int a2) CEffectSystem();  // 0x004C61A0
    static _DWORD *__thiscall(_DWORD *this, int a2) ~CEffectSystem();  // 0x004C6240
    static _DWORD *__thiscall(_DWORD *Block, char a2) Reset();  // 0x004C6260
    int Init();  // 0x004C6280
    char Destroy(int a2, int a3, int a4, int a5, int a6);  // 0x004C6290
    static int() GetEffectIndex();  // 0x004C6330
    static int() CreateEffect();  // 0x004C6340
    static void() GetEffect();  // 0x004C6350
    static void() DestroyEffect();  // 0x004C6360
    int DestroyEffect();  // 0x004C6370
    static void *() DestroyAllEffect();  // 0x004C6410
    char IsVisible();  // 0x004C6460
    void SetVisible(float a2);  // 0x004C65C0
    void HandleViewMove(int a2);  // 0x004C65F0
    char Update();  // 0x004C6670
    static _DWORD *__thiscall(_DWORD *this) FillDefaultUVSet();  // 0x004C6870
};

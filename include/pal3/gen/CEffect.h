#pragma once
// Auto-generated from IDA decomp - CEffect
// 6 methods

class CEffect {
public:
    static _DWORD *() CEffect();  // 0x004C6940
    int Reset(int a2, float a3, float a4, float a5);  // 0x004C6A70
    void CreateOnePartical(float a2);  // 0x004C7150
    void FillQuadByPartical(_DWORD *a2);  // 0x004C7450
    int SetParam(int a2);  // 0x004CA400
    int Render(int a2);  // 0x004CE460
};

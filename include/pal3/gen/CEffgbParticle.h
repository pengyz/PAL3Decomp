#pragma once
// Auto-generated from IDA decomp - CEffgbParticle
// 10 methods

class CEffgbParticle {
public:
    int ~CEffgbParticle(int a2, int a3, int a4, _DWORD *a5, int a6, int a7);  // 0x004C8650
    static void *__thiscall(void *Block, char a2) Create();  // 0x004C87A0
    int Init(int a2);  // 0x004C8830
    static char *__thiscall(char *this, char a2) Attach();  // 0x004C88C0
    static _DWORD *__thiscall(_DWORD *this) Render();  // 0x004C88D0
    static _DWORD *() SetTimeScale();  // 0x004C8930
    static void Destroy(_DWORD *a1);  // 0x004C8970
    char CreateTask(int a2);  // 0x004C8A40
    void ProcCommonTask(float a2);  // 0x004C8BF0
    void GetEditorTaskDescription();  // 0x004C8E10
};

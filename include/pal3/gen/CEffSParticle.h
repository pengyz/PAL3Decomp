#pragma once
// Auto-generated from IDA decomp - CEffSParticle
// 10 methods

class CEffSParticle {
public:
    static _DWORD *() CEffSParticle();  // 0x004D4EE0
    int ~CEffSParticle();  // 0x004D4F20
    int Create(float a2);  // 0x004D4FC0
    void Init(_DWORD *a2);  // 0x004D51B0
    int Attach(int a2);  // 0x004D53E0
    static void *__stdcall(int a1) Update();  // 0x004D5620
    int Render(int a2, int a3, int a4, _DWORD *a5, int a6, int a7);  // 0x004D56B0
    static void *__thiscall(void *Block, char a2) SetTimeScale();  // 0x004D5790
    static char *__thiscall(_DWORD *this, char a2) CreateTask();  // 0x004D5860
    int GetEditorTaskDescription(unsigned __int8 *a2);  // 0x004D58D0
};

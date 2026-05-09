#pragma once
// Auto-generated from IDA decomp - CEffQuad
// 6 methods

class CEffQuad {
public:
    char Create(int a2);  // 0x004D1090
    char DestroyOneQuad(const void *a2);  // 0x004D1BE0
    int SetQuad(int a2);  // 0x004D1CA0
    static _DWORD *__thiscall(_DWORD *this, int a2) DestroyAllQuad();  // 0x004D1E50
    static _DWORD *__thiscall(int this, int a2) ToNextFrame();  // 0x004D1F30
    int CreateTask(_DWORD *a2);  // 0x004D2080
};

#pragma once
// Auto-generated from IDA decomp - C3DSpark
// 7 methods

class C3DSpark {
public:
    static _DWORD *__thiscall(_DWORD *this) C3DSpark();  // 0x004D6670
    void ~C3DSpark();  // 0x004D6960
    char CreateSingle(const void *a2);  // 0x004D6A60
    char CreateOne(int a2, int a3, int a4);  // 0x004D6AC0
    static _BYTE *__thiscall(_DWORD *this) DestroyAll();  // 0x004D6BA0
    static void Render(int a1@<ecx>, struct gbVec3D *a2@<edi>);  // 0x004D6BC0
    int Update(float a2);  // 0x004D6D30
};

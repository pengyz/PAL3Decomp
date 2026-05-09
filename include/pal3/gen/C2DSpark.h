#pragma once
// Auto-generated from IDA decomp - C2DSpark
// 9 methods

class C2DSpark {
public:
    int C2DSpark(int a2, int a3);  // 0x004D5AB0
    void ~C2DSpark();  // 0x004D5DC0
    char CreateSingle(const void *a2);  // 0x004D5EC0
    char CreateTrack(char a2);  // 0x004D5F20
    int SetEnableMouseTrack(int a2, int a3);  // 0x004D5F40
    char CreateMore(int a2, int a3, int a4, int a5);  // 0x004D6050
    static _BYTE *__thiscall(_DWORD *this) CreateStars();  // 0x004D61A0
    int DestroyAll();  // 0x004D61C0
    int Render(float a2);  // 0x004D6380
};

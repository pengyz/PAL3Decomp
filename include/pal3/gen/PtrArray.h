#pragma once
// Auto-generated from IDA decomp - PtrArray
// 7 methods

class PtrArray {
public:
    static int PtrArray(int a1, int a2, char a3);  // 0x00434130
    static int ~PtrArray(int a1);  // 0x004341E0
    static void() SetSize();  // 0x00434240
    static char *__cdecl(unsigned __int16 a1, int a2) SetAtGrow();  // 0x004343B0
    static char *__cdecl(const char *a1) RemoveAt();  // 0x004343F0
    void Remove();  // 0x00434490
    static struct gbVFile *__thiscall(int this, const char *a2) InsertAt();  // 0x004344F0
};

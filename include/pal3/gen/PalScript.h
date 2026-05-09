#pragma once
// Auto-generated from IDA decomp - PalScript
// 13 methods

class PalScript {
public:
    int LoadScript(int pathAddr);  // 0x00430290
    static char *__thiscall(PalScript *this, char *name) SetAppName();  // 0x00430570
    static void *__thiscall(PalScript *this, char *filename) LoadFromFile();  // 0x004318B0
    int SetDirectory(char *dir);  // 0x004319F0
    int HasNext();  // 0x00431A60
    int LoadNext();  // 0x00431B60
    static int() PalScript();  // 0x00431D80
    static int() AddWaitObj();  // 0x00431F00
    static int AddCamObj(int a1);  // 0x00431F10
    static void __cdecl() ClearAllCamObj();  // 0x00431F40
    int ClearAllWaitObj();  // 0x00431FA0
    int Update();  // 0x00431FB0
    int Reset();  // 0x0043A250
};

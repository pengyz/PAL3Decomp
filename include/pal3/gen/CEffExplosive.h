#pragma once
// Auto-generated from IDA decomp - CEffExplosive
// 9 methods

class CEffExplosive {
public:
    char Create(int a2);  // 0x004C6C10
    void Destroy();  // 0x004C6F20
    int ProcCommonTask(int a2);  // 0x004C7680
    static void *__stdcall(int a1) GetEditorTaskDescription();  // 0x004C7A70
    static void *__stdcall(int a1) GetEditorObjDescription();  // 0x004C7B70
    void InitDefaultUVSet(int a2, int a3);  // 0x004C7C00
    static _DWORD *__thiscall(int this, int a2) LoadTexture();  // 0x004C7CB0
    int CreateGeom();  // 0x004C7D40
    int UpdateExplosive(float a2, int a3);  // 0x004C8370
};

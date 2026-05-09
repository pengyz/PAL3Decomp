#pragma once
// Auto-generated from IDA decomp - CEffCylinder
// 12 methods

class CEffCylinder {
public:
    static void CEffCylinder(int a1);  // 0x004C3DD0
    void ~CEffCylinder();  // 0x004C3EB0
    int Init(int a2, float a3, float a4, float a5);  // 0x004C3EC0
    char Create(int a2);  // 0x004C4060
    void Destroy();  // 0x004C4370
    void CreateTask(float a2);  // 0x004C45A0
    void ProcInitTask(_DWORD *a2);  // 0x004C48D0
    int ProcCommonTask(int a2);  // 0x004C4B00
    static void *__stdcall(int a1) GetEditorTaskDescription();  // 0x004C5010
    static void *__stdcall(int a1) GetEditorObjDescription();  // 0x004C5150
    void InitDefaultUVSet(int a2, int a3);  // 0x004C5210
    static _DWORD *__thiscall(int this, int a2) LoadTexture();  // 0x004C52C0
};

#pragma once
// Auto-generated from IDA decomp - _TextureLib_Data
// 9 methods

class _TextureLib_Data {
public:
    static void() _TextureLib_Data();  // 0x0053FFA0
    static void ~_TextureLib_Data(int a1, int a2, int a3, int a4, float *a5);  // 0x00540070
    static void _GetItemNum(int *a1, struct gbTextureArray *a2, int a3, int a4);  // 0x005400E0
    static void _CheckItem(_DWORD *a1, int *a2, struct gbTextureArray *a3, int a4, unsigned int a5, float *a6);  // 0x00540210
    static void SetLibFolder(int *a1, unsigned int *a2, struct gbTextureArray *a3, unsigned int a4, unsigned int *a5, float a6);  // 0x00540440
    static void GetLibInfo(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, int a7, unsigned int *a8);  // 0x00540650
    static void GetLib(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, unsigned int a7);  // 0x005407A0
    static void GetTextureInfo(_DWORD *a1, int *a2, int *a3, struct gbTextureArray *a4, unsigned int *a5);  // 0x005408E0
    static void GetTextureInfo(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, unsigned int *a7);  // 0x00540A20
};

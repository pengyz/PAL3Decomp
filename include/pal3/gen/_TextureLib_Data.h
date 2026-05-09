#pragma once
// Auto-generated: _TextureLib_Data

#include "Parent_Data.h"

class _Texture_Info;

class _TextureLib_Data : public Parent_Data {
public:
    char * Seps; // +0x4
    char * tok; // +0x8
    char _libfolder[512]; // +0xC
    int _realNum; // +0x20C
    _Texture_Info * m_pData; // +0x210
    unsigned char _isLoadTLI; // +0x214
    // total size: 0x218 (536)

    _TextureLib_Data(); // 0x0053FFA0
    ~_TextureLib_Data(); // 0x00540070
    static void _GetItemNum(int *a1, struct gbTextureArray *a2, int a3, int a4); // 0x005400E0
    static void _CheckItem(_DWORD *a1, int *a2, struct gbTextureArray *a3, int a4, unsigned int a5, float *a6); // 0x00540210
    static void SetLibFolder(int *a1, unsigned int *a2, struct gbTextureArray *a3, unsigned int a4, unsigned int *a5, float a6); // 0x00540440
    static void GetLibInfo(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, int a7, unsigned int *a8); // 0x00540650
    static void GetLib(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, unsigned int a7); // 0x005407A0
    static void GetTextureInfo(_DWORD *a1, int *a2, int *a3, struct gbTextureArray *a4, unsigned int *a5); // 0x005408E0
    static void GetTextureInfo(int a1, int a2, int a3, int a4, int *a5, struct gbTextureArray *a6, unsigned int *a7); // 0x00540A20
};

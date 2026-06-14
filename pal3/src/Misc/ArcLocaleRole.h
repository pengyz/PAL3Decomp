#pragma once
// Auto-generated: ArcLocaleRole

#include "gbengine/gbengine_types.h"

class ArcLocaleRole {
public:
    BYTE active; // +0x0
    char _gap_001[3]; // +0x1
    gbVec3D pos; // +0x4
    char _gap_008[8]; // +0x8
    BYTE layer; // +0x10
    char _gap_011[3]; // +0x11
    float rotate; // +0x14
    UINT script; // +0x18
    // total size: 0x1C (28)

    int HandleKeyInput(); // 0x0047F930
    int Release(); // 0x004A6C70
    int IterateColors(); // 0x004AF410
    int * CalcPosition(int *p_DWORD); // 0x004AFB60
    static unsigned int ParseLocaleData(char *pszBuf, char *pszBuf2, int nVal); // 0x004AFD80
    int DispatchActive(int nVal); // 0x005303C0
    int Destroy(); // 0x00535030
    void GetScreenLeft(double thisa); // 0x005350C0
    float * TransformPoint(float *a2, float a3, float a4, float a5); // 0x00535FD0
};

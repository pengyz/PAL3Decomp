#pragma once
// Auto-generated: PathObj

#include "gbengine/gbengine_types.h"

class PathObj {
public:
    gbVec3D points[256]; // +0x0
    char _gap_400[2048]; // +0x400
    int numpoint; // +0xC00
    float totallength; // +0xC04
    float length[256]; // +0xC08
    gbVec3D * normal; // +0x1008
    int m_nCurPathLen; // +0x100C
    int _todo_1010; // +0x1010
    gbVec3D * m_pPathDir; // +0x1014
    int m_nPathLen; // +0x1018
    int _todo_101C; // +0x101C
    char _gap_1020[3048]; // +0x1020
    float segmentprojection; // +0x1C08
    float segmentlength; // +0x1C0C
    gbVec3D segmentnormal; // +0x1C10
    char _gap_1C14[8]; // +0x1C14
    gbVec3D chosen; // +0x1C1C
    char _tail_1C20[8]; // +0x1C20
    // total size: 0x1C28 (7208)

    int CalcLength(); // 0x00407DC0
    int * GetPosition(float pPos, float *pfVal, int *p_DWORD); // 0x0041F120
};

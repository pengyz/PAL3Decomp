#pragma once
// Auto-generated: tagEffLinker

#include "gbengine/gbengine_types.h"

class tagEffLinker {
public:
    UINT dwTrickID; // +0x0
    int nEffGroup1; // +0x4
    BYTE bSrcForceCenter1; // +0x8
    BYTE bDestForceCenter1; // +0x9
    BYTE bSrcRole1; // +0xA
    BYTE bDestRole1; // +0xB
    gbVec3D vecPos1; // +0xC
    char _gap_010[8]; // +0x10
    float fWaitTime1; // +0x18
    float fWorkTime1; // +0x1C
    int nEffGroup2; // +0x20
    BYTE bSrcForceCenter2; // +0x24
    BYTE bDestForceCenter2; // +0x25
    BYTE bSrcRole2; // +0x26
    BYTE bDestRole2; // +0x27
    gbVec3D vecPos2; // +0x28
    char _gap_02C[8]; // +0x2C
    float fWaitTime2; // +0x34
    float fWorkTime2; // +0x38
    // total size: 0x3C (60)

};

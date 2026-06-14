#pragma once
// Auto-generated: tagRoleTask

#include "ECBRoleTaskMode.h"
#include "gbengine/gbengine_types.h"
#include "tagCmdData.h"

class tagRoleTask {
public:
    char * fp[4]; // +0x0
    char _gap_004[12]; // +0x4
    gbVec3D vec1; // +0x10
    char _gap_014[8]; // +0x14
    tagCmdData cmd; // +0x1C
    char _gap_020[40]; // +0x20
    float fTemp; // +0x48
    float fTemp2; // +0x4C
    UINT dwID; // +0x50
    ECBRoleTaskMode eMode; // +0x54
    BYTE bValid; // +0x58
    BYTE bFinished; // +0x59
    BYTE bExecuted; // +0x5A
    char _tail_05B[5]; // +0x5B
    // total size: 0x60 (96)

};

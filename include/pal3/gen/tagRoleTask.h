#pragma once
// Auto-generated: tagRoleTask

#include "ECBRoleTaskMode.h"
#include "tagCmdData.h"

class tagRoleTask {
public:
    void * * fp; // +0x0
    gbVec3D vec1; // +0x10
    tagCmdData cmd; // +0x1C
    float fTemp; // +0x48
    float fTemp2; // +0x4C
    DWORD dwID; // +0x50
    ECBRoleTaskMode eMode; // +0x54
    BYTE bValid; // +0x58
    BYTE bFinished; // +0x59
    BYTE bExecuted; // +0x5A
    // total size: 0x60 (96)

};

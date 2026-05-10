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
    unsigned long dwID; // +0x50
    ECBRoleTaskMode eMode; // +0x54
    unsigned char bValid; // +0x58
    unsigned char bFinished; // +0x59
    unsigned char bExecuted; // +0x5A
    // total size: 0x60 (96)

};

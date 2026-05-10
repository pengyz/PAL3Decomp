#pragma once
// Auto-generated: tagStageSubTask

#include "ECBStageTaskState.h"
#include "tagParam.h"

class tagStageSubTask {
public:
    void * * fp; // +0x0
    ECBStageTaskState eStats; // +0x10
    DWORD dwID; // +0x14
    float fStartTime; // +0x18
    float fWaitTime; // +0x1C
    float fTime; // +0x20
    DWORD dwReturn; // +0x24
    BYTE bValid; // +0x28
    BYTE bExecuted; // +0x29
    BYTE bAction; // +0x2A
    BYTE bRequireToEnd; // +0x2B
    tagParam param; // +0x2C
    int nEffLinker; // +0x38
    BYTE bEff1Started; // +0x3C
    BYTE bEff2Started; // +0x3D
    BYTE bEffWorked; // +0x3E
    int nTemp1; // +0x40
    DWORD dwTemp1; // +0x40
    float fTemp1; // +0x40
    int nTemp2; // +0x44
    DWORD dwTemp2; // +0x44
    float fTemp2; // +0x44
    int nTemp3; // +0x48
    DWORD dwTemp3; // +0x48
    float fTemp3; // +0x48
    int nTemp4; // +0x4C
    DWORD dwTemp4; // +0x4C
    float fTemp4; // +0x4C
    // total size: 0x50 (80)

};

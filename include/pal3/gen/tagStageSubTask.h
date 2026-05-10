#pragma once
// Auto-generated: tagStageSubTask

#include "ECBStageTaskState.h"
#include "tagParam.h"

class tagStageSubTask {
public:
    void * * fp; // +0x0
    ECBStageTaskState eStats; // +0x10
    unsigned long dwID; // +0x14
    float fStartTime; // +0x18
    float fWaitTime; // +0x1C
    float fTime; // +0x20
    unsigned long dwReturn; // +0x24
    unsigned char bValid; // +0x28
    unsigned char bExecuted; // +0x29
    unsigned char bAction; // +0x2A
    unsigned char bRequireToEnd; // +0x2B
    tagParam param; // +0x2C
    int nEffLinker; // +0x38
    unsigned char bEff1Started; // +0x3C
    unsigned char bEff2Started; // +0x3D
    unsigned char bEffWorked; // +0x3E
    int nTemp1; // +0x40
    unsigned long dwTemp1; // +0x40
    float fTemp1; // +0x40
    int nTemp2; // +0x44
    unsigned long dwTemp2; // +0x44
    float fTemp2; // +0x44
    int nTemp3; // +0x48
    unsigned long dwTemp3; // +0x48
    float fTemp3; // +0x48
    int nTemp4; // +0x4C
    unsigned long dwTemp4; // +0x4C
    float fTemp4; // +0x4C
    // total size: 0x50 (80)

};

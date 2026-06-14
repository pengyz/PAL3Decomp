#pragma once
// Auto-generated: tagStageSubTask

#include "ECBStageTaskState.h"
#include "tagParam.h"

class tagStageSubTask {
public:
    char * fp[4]; // +0x0
    char _gap_004[12]; // +0x4
    ECBStageTaskState eStats; // +0x10
    UINT dwID; // +0x14
    float fStartTime; // +0x18
    float fWaitTime; // +0x1C
    float fTime; // +0x20
    UINT dwReturn; // +0x24
    BYTE bValid; // +0x28
    BYTE bExecuted; // +0x29
    BYTE bAction; // +0x2A
    BYTE bRequireToEnd; // +0x2B
    tagParam param; // +0x2C
    char _gap_030[8]; // +0x30
    int nEffLinker; // +0x38
    BYTE bEff1Started; // +0x3C
    BYTE bEff2Started; // +0x3D
    BYTE bEffWorked; // +0x3E
    char _gap_03F[1]; // +0x3F
    float fTemp1; // +0x40
    float fTemp2; // +0x44
    float fTemp3; // +0x48
    float fTemp4; // +0x4C
    // total size: 0x50 (80)

};

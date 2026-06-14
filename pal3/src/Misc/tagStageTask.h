#pragma once
// Auto-generated: tagStageTask

#include "ECBStageTask.h"
#include "ECBStageTaskState.h"
#include "tagCmdData.h"
#include "tagStageSubTask.h"

class tagStageTask {
public:
    ECBStageTask eTask; // +0x0
    ECBStageTaskState eStats; // +0x4
    int nSubTask; // +0x8
    int nReserved; // +0xC
    tagStageSubTask SubTask[32]; // +0x10
    char _gap_090[2432]; // +0x90
    UINT dwID; // +0xA10
    UINT dwReturn; // +0xA14
    tagCmdData cmd; // +0xA18
    char _gap_A1C[40]; // +0xA1C
    BYTE bValid; // +0xA44
    BYTE bAutoDel; // +0xA45
    char _tail_A46[2]; // +0xA46
    // total size: 0xA48 (2632)

};

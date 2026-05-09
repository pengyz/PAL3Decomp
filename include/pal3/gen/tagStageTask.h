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
    tagStageSubTask SubTask[32]; // +0x10
    unsigned long dwID; // +0xA10
    unsigned long dwReturn; // +0xA14
    tagCmdData cmd; // +0xA18
    unsigned char bValid; // +0xA44
    unsigned char bAutoDel; // +0xA45
    // total size: 0xA48 (2632)

};

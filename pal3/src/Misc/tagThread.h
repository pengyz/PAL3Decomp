#pragma once
// Auto-generated: tagThread

#include "tagCmdData.h"

class tagThread {
public:
    char * fp[4]; // +0x0
    char _gap_004[12]; // +0x4
    UINT dwID; // +0x10
    int nTaskIndex; // +0x14
    UINT dwTaskID; // +0x18
    UINT dwReturn; // +0x1C
    int nTemp; // +0x20
    BYTE bValid; // +0x24
    BYTE bExecuted; // +0x25
    char _gap_026[2]; // +0x26
    tagCmdData cmd; // +0x28
    char _tail_02C[44]; // +0x2C
    // total size: 0x58 (88)

};

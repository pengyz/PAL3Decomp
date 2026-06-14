#pragma once
// Auto-generated: tagUITask

#include "tagUIParam.h"

class tagUITask {
public:
    char * fp[4]; // +0x0
    char _gap_004[12]; // +0x4
    BYTE bValid; // +0x10
    BYTE bExecuted; // +0x11
    BYTE bFinished; // +0x12
    char _gap_013[1]; // +0x13
    UINT dwID; // +0x14
    float fStartTime; // +0x18
    int fExpectStartTime; // +0x1C
    float fExpectEndTime; // +0x20
    tagUIParam param; // +0x24
    char _tail_028[32]; // +0x28
    // total size: 0x48 (72)

};

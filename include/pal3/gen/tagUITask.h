#pragma once
// Auto-generated: tagUITask

#include "tagUIParam.h"

class tagUITask {
public:
    void * * fp; // +0x0
    unsigned char bValid; // +0x10
    unsigned char bExecuted; // +0x11
    unsigned char bFinished; // +0x12
    unsigned long dwID; // +0x14
    float fStartTime; // +0x18
    float fExpectStartTime; // +0x1C
    float fExpectEndTime; // +0x20
    tagUIParam param; // +0x24
    // total size: 0x48 (72)

};

#pragma once
// Auto-generated: tagUITask

#include "tagUIParam.h"

class tagUITask {
public:
    void * * fp; // +0x0
    BYTE bValid; // +0x10
    BYTE bExecuted; // +0x11
    BYTE bFinished; // +0x12
    DWORD dwID; // +0x14
    float fStartTime; // +0x18
    float fExpectStartTime; // +0x1C
    float fExpectEndTime; // +0x20
    tagUIParam param; // +0x24
    // total size: 0x48 (72)

};

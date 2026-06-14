#pragma once
// Auto-generated: tagCamTask

#include "tagCam.h"

class tagCamTask {
public:
    char * fp[4]; // +0x0
    char _gap_004[12]; // +0x4
    UINT dwID; // +0x10
    BYTE bValid; // +0x14
    BYTE bExecuted; // +0x15
    BYTE bFinished; // +0x16
    char _gap_017[1]; // +0x17
    float fStartTime; // +0x18
    float fExpectTime; // +0x1C
    tagCam StartPos; // +0x20
    char _gap_024[20]; // +0x24
    tagCam EndPos; // +0x38
    char _tail_03C[20]; // +0x3C
    // total size: 0x50 (80)

};

#pragma once
// Auto-generated: tagControlThread

class tagControlThread {
public:
    char * fp[4]; // +0x0
    char _gap_004[12]; // +0x4
    char * fpCaller[4]; // +0x10
    char _gap_014[12]; // +0x14
    UINT dwID; // +0x20
    UINT dwFlag; // +0x24
    UINT dwCmdKind; // +0x28
    UINT dwCmdID; // +0x2C
    UINT dwReturn; // +0x30
    int nTaskIndex; // +0x34
    UINT dwTaskID; // +0x38
    BYTE bValid; // +0x3C
    BYTE bExecuted; // +0x3D
    char _tail_03E[2]; // +0x3E
    // total size: 0x40 (64)

};

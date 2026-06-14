#pragma once
// Auto-generated: tagCmdData

class tagCmdData {
public:
    UINT dwCmdKind; // +0x0
    UINT dwItemID; // +0x4
    int nSrcRole; // +0x8
    int nDestRole; // +0xC
    BYTE bMultiSrcRole; // +0x10
    BYTE bMultiDestRole; // +0x11
    _BYTE bSrcRole[11]; // +0x12
    _BYTE bDestRole[11]; // +0x1D
    BYTE bValid; // +0x28
    char _tail_029[3]; // +0x29
    // total size: 0x2C (44)

};

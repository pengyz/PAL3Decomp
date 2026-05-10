#pragma once
// Auto-generated: tagCmdData

class tagCmdData {
public:
    DWORD dwCmdKind; // +0x0
    DWORD dwCmdID; // +0x4
    DWORD dwItemID; // +0x4
    int nSrcRole; // +0x8
    int nDestRole; // +0xC
    BYTE bMultiSrcRole; // +0x10
    BYTE bMultiDestRole; // +0x11
    BYTE bSrcRole[11]; // +0x12
    BYTE bDestRole[11]; // +0x1D
    BYTE bValid; // +0x28
    // total size: 0x2C (44)

};

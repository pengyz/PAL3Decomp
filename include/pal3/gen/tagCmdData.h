#pragma once
// Auto-generated: tagCmdData

class tagCmdData {
public:
    unsigned long dwCmdKind; // +0x0
    unsigned long dwCmdID; // +0x4
    unsigned long dwItemID; // +0x4
    int nSrcRole; // +0x8
    int nDestRole; // +0xC
    unsigned char bMultiSrcRole; // +0x10
    unsigned char bMultiDestRole; // +0x11
    unsigned char bSrcRole[11]; // +0x12
    unsigned char bDestRole[11]; // +0x1D
    unsigned char bValid; // +0x28
    // total size: 0x2C (44)

};

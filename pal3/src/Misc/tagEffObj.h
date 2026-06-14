#pragma once
// Auto-generated: tagEffObj

class CEffObj;

class tagEffObj {
public:
    UINT dwClassNameCRC; // +0x0
    UINT dwTypeNameCRC; // +0x4
    UINT dwRunGroupID; // +0x8
    BYTE bValid; // +0xC
    BYTE bIdle; // +0xD
    BYTE bClassObj; // +0xE
    char _gap_00F[1]; // +0xF
    CEffObj * pEffect; // +0x10
    // total size: 0x14 (20)

};

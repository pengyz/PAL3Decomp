#pragma once
// Auto-generated: CPKFile

class tagCPKTable;

class CPKFile {
public:
    unsigned char bValid; // +0x0
    unsigned long dwCRC; // +0x4
    unsigned long dwFatherCRC; // +0x8
    int nTableIndex; // +0xC
    void * lpMapAddress; // +0x10
    void * lpStartAddress; // +0x14
    unsigned long dwOffset; // +0x18
    unsigned char bCompressed; // +0x1C
    void * lpMem; // +0x20
    unsigned long dwFileSize; // +0x24
    unsigned long dwPointer; // +0x28
    tagCPKTable * pTableItem; // +0x2C
    // total size: 0x30 (48)

};

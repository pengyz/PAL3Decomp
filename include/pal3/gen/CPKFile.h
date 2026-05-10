#pragma once
// Auto-generated: CPKFile

class tagCPKTable;

class CPKFile {
public:
    BYTE bValid; // +0x0
    DWORD dwCRC; // +0x4
    DWORD dwFatherCRC; // +0x8
    int nTableIndex; // +0xC
    void * lpMapAddress; // +0x10
    void * lpStartAddress; // +0x14
    DWORD dwOffset; // +0x18
    BYTE bCompressed; // +0x1C
    void * lpMem; // +0x20
    DWORD dwFileSize; // +0x24
    DWORD dwPointer; // +0x28
    tagCPKTable * pTableItem; // +0x2C
    // total size: 0x30 (48)

};

#pragma once
// Auto-generated: BINKIO

class BINK;

class BINKIO {
public:
    void * * ReadHeader; // +0x0
    void * * ReadFrame; // +0x4
    void * * GetBufferSize; // +0x8
    void * * SetInfo; // +0xC
    void * * Idle; // +0x10
    void * * Close; // +0x14
    BINK * bink; // +0x18
    DWORD ReadError; // +0x1C
    DWORD DoingARead; // +0x20
    DWORD BytesRead; // +0x24
    DWORD Working; // +0x28
    DWORD TotalTime; // +0x2C
    DWORD ForegroundTime; // +0x30
    DWORD IdleTime; // +0x34
    DWORD ThreadTime; // +0x38
    DWORD BufSize; // +0x3C
    DWORD BufHighUsed; // +0x40
    DWORD CurBufSize; // +0x44
    DWORD CurBufUsed; // +0x48
    BYTE iodata[128]; // +0x4C
    // total size: 0xCC (204)

};

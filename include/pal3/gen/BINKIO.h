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
    unsigned long ReadError; // +0x1C
    unsigned long DoingARead; // +0x20
    unsigned long BytesRead; // +0x24
    unsigned long Working; // +0x28
    unsigned long TotalTime; // +0x2C
    unsigned long ForegroundTime; // +0x30
    unsigned long IdleTime; // +0x34
    unsigned long ThreadTime; // +0x38
    unsigned long BufSize; // +0x3C
    unsigned long BufHighUsed; // +0x40
    unsigned long CurBufSize; // +0x44
    unsigned long CurBufUsed; // +0x48
    unsigned char iodata[128]; // +0x4C
    // total size: 0xCC (204)

};

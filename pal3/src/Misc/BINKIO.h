#pragma once
// Auto-generated: BINKIO

class BINK;

class BINKIO {
public:
    char * ReadHeader; // +0x0
    char * ReadFrame; // +0x4
    char * GetBufferSize; // +0x8
    char * SetInfo; // +0xC
    char * Idle; // +0x10
    char * Close; // +0x14
    BINK * bink; // +0x18
    UINT ReadError; // +0x1C
    UINT DoingARead; // +0x20
    UINT BytesRead; // +0x24
    UINT Working; // +0x28
    UINT TotalTime; // +0x2C
    UINT ForegroundTime; // +0x30
    UINT IdleTime; // +0x34
    UINT ThreadTime; // +0x38
    UINT BufSize; // +0x3C
    UINT BufHighUsed; // +0x40
    UINT CurBufSize; // +0x44
    UINT CurBufUsed; // +0x48
    _BYTE iodata[128]; // +0x4C
    // total size: 0xCC (204)

};

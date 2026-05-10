#pragma once
// Auto-generated: BINKSND

class BINKSND {
public:
    void * * Ready; // +0x0
    void * * Lock; // +0x4
    void * * Unlock; // +0x8
    void * * Volume; // +0xC
    void * * Pan; // +0x10
    void * * Pause; // +0x14
    void * * SetOnOff; // +0x18
    void * * Close; // +0x1C
    DWORD BestSizeIn16; // +0x20
    DWORD SoundDroppedOut; // +0x24
    long OnOff; // +0x28
    DWORD Latency; // +0x2C
    DWORD VideoScale; // +0x30
    DWORD freq; // +0x34
    long bits; // +0x38
    long chans; // +0x3C
    BYTE snddata[128]; // +0x40
    // total size: 0xC0 (192)

};

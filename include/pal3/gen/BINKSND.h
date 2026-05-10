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
    unsigned long BestSizeIn16; // +0x20
    unsigned long SoundDroppedOut; // +0x24
    long OnOff; // +0x28
    unsigned long Latency; // +0x2C
    unsigned long VideoScale; // +0x30
    unsigned long freq; // +0x34
    long bits; // +0x38
    long chans; // +0x3C
    unsigned char snddata[128]; // +0x40
    // total size: 0xC0 (192)

};

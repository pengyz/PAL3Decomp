#pragma once
// Auto-generated: BINKSND

class BINKSND {
public:
    char * Ready; // +0x0
    char * Lock; // +0x4
    char * Unlock; // +0x8
    char * Volume; // +0xC
    char * Pan; // +0x10
    char * Pause; // +0x14
    char * SetOnOff; // +0x18
    char * Close; // +0x1C
    UINT BestSizeIn16; // +0x20
    UINT SoundDroppedOut; // +0x24
    int OnOff; // +0x28
    UINT Latency; // +0x2C
    UINT VideoScale; // +0x30
    UINT freq; // +0x34
    int bits; // +0x38
    int chans; // +0x3C
    _BYTE snddata[128]; // +0x40
    // total size: 0xC0 (192)

};

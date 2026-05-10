#pragma once
// Auto-generated: DIEFFECT

class DIENVELOPE;

class DIEFFECT {
public:
    unsigned long dwSize; // +0x0
    unsigned long dwFlags; // +0x4
    unsigned long dwDuration; // +0x8
    unsigned long dwSamplePeriod; // +0xC
    unsigned long dwGain; // +0x10
    unsigned long dwTriggerButton; // +0x14
    unsigned long dwTriggerRepeatInterval; // +0x18
    unsigned long cAxes; // +0x1C
    unsigned long * rgdwAxes; // +0x20
    long * rglDirection; // +0x24
    DIENVELOPE * lpEnvelope; // +0x28
    unsigned long cbTypeSpecificParams; // +0x2C
    void * lpvTypeSpecificParams; // +0x30
    unsigned long dwStartDelay; // +0x34
    // total size: 0x38 (56)

};

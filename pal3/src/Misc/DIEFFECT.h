#pragma once
// Auto-generated: DIEFFECT

class DIENVELOPE;

class DIEFFECT {
public:
    UINT dwSize; // +0x0
    UINT dwFlags; // +0x4
    UINT dwDuration; // +0x8
    UINT dwSamplePeriod; // +0xC
    UINT dwGain; // +0x10
    UINT dwTriggerButton; // +0x14
    UINT dwTriggerRepeatInterval; // +0x18
    UINT cAxes; // +0x1C
    UINT * rgdwAxes; // +0x20
    int * rglDirection; // +0x24
    DIENVELOPE * lpEnvelope; // +0x28
    UINT cbTypeSpecificParams; // +0x2C
    char * lpvTypeSpecificParams; // +0x30
    UINT dwStartDelay; // +0x34
    // total size: 0x38 (56)

};

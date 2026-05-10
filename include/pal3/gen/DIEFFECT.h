#pragma once
// Auto-generated: DIEFFECT

class DIENVELOPE;

class DIEFFECT {
public:
    DWORD dwSize; // +0x0
    DWORD dwFlags; // +0x4
    DWORD dwDuration; // +0x8
    DWORD dwSamplePeriod; // +0xC
    DWORD dwGain; // +0x10
    DWORD dwTriggerButton; // +0x14
    DWORD dwTriggerRepeatInterval; // +0x18
    DWORD cAxes; // +0x1C
    DWORD * rgdwAxes; // +0x20
    long * rglDirection; // +0x24
    DIENVELOPE * lpEnvelope; // +0x28
    DWORD cbTypeSpecificParams; // +0x2C
    void * lpvTypeSpecificParams; // +0x30
    DWORD dwStartDelay; // +0x34
    // total size: 0x38 (56)

};

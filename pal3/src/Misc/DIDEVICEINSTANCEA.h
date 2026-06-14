#pragma once
// Auto-generated: DIDEVICEINSTANCEA

class DIDEVICEINSTANCEA {
public:
    UINT dwSize; // +0x0
    _GUID guidInstance; // +0x4
    char _gap_008[12]; // +0x8
    _GUID guidProduct; // +0x14
    char _gap_018[12]; // +0x18
    UINT dwDevType; // +0x24
    char tszInstanceName[324]; // +0x28
    char tszProductName[324]; // +0x16C
    _GUID guidFFDriver; // +0x2B0
    char _gap_2B4[12]; // +0x2B4
    WORD wUsagePage; // +0x2C0
    WORD wUsage; // +0x2C2
    // total size: 0x2C4 (708)

};

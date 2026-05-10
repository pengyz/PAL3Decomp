#pragma once
// Auto-generated: _D3DADAPTER_IDENTIFIER9

#include "_LARGE_INTEGER.h"

class _D3DADAPTER_IDENTIFIER9 {
public:
    char Driver[512]; // +0x0
    char Description[512]; // +0x200
    char DeviceName[32]; // +0x400
    _LARGE_INTEGER DriverVersion; // +0x420
    unsigned long VendorId; // +0x428
    unsigned long DeviceId; // +0x42C
    unsigned long SubSysId; // +0x430
    unsigned long Revision; // +0x434
    _GUID DeviceIdentifier; // +0x438
    unsigned long WHQLLevel; // +0x448
    // total size: 0x44C (1100)

};

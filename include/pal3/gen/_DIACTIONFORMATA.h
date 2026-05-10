#pragma once
// Auto-generated: _DIACTIONFORMATA

class HINSTANCE__;
class _DIACTIONA;

class _DIACTIONFORMATA {
public:
    unsigned long dwSize; // +0x0
    unsigned long dwActionSize; // +0x4
    unsigned long dwDataSize; // +0x8
    unsigned long dwNumActions; // +0xC
    _DIACTIONA * rgoAction; // +0x10
    _GUID guidActionMap; // +0x14
    unsigned long dwGenre; // +0x24
    unsigned long dwBufferSize; // +0x28
    long lAxisMin; // +0x2C
    long lAxisMax; // +0x30
    HINSTANCE__ * hInstString; // +0x34
    _FILETIME ftTimeStamp; // +0x38
    unsigned long dwCRC; // +0x40
    char tszActionMap[324]; // +0x44
    // total size: 0x188 (392)

};

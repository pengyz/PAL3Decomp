#pragma once
// Auto-generated: _DIACTIONFORMATA

class HINSTANCE__;
class _DIACTIONA;

class _DIACTIONFORMATA {
public:
    DWORD dwSize; // +0x0
    DWORD dwActionSize; // +0x4
    DWORD dwDataSize; // +0x8
    DWORD dwNumActions; // +0xC
    _DIACTIONA * rgoAction; // +0x10
    _GUID guidActionMap; // +0x14
    DWORD dwGenre; // +0x24
    DWORD dwBufferSize; // +0x28
    long lAxisMin; // +0x2C
    long lAxisMax; // +0x30
    HINSTANCE__ * hInstString; // +0x34
    _FILETIME ftTimeStamp; // +0x38
    DWORD dwCRC; // +0x40
    char tszActionMap[324]; // +0x44
    // total size: 0x188 (392)

};

#pragma once
// Auto-generated: util

class CIniFile;
class CLoad3DS;

class util {
public:
    unsigned long Crc32Table[256]; // +0x0
    unsigned long m_dwIDHolder; // +0x400
    int m_nRandHolder; // +0x404
    int m_nRandCallCount; // +0x408
    CIniFile * m_pIniReader; // +0x40C
    CLoad3DS * m_pLoader3DS; // +0x410
    // total size: 0x414 (1044)

};

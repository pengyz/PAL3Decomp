#pragma once
// Auto-generated: CUtil

class _iobuf;

class CUtil {
public:
    unsigned char m_bCanWarp; // +0x0
    int m_nRandHolder; // +0x0
    int m_nRandCallCount; // +0x0
    _iobuf * m_fLog; // +0x0
    char * m_sLogFileName; // +0x0
    char m_INIFileName[260]; // +0x0
    char * m_pDefaultString; // +0x0
    char m_INIBuffer[256]; // +0x0
    // total size: 0x1 (1)

    ~CUtil(); // 0x005230F0
    static int Create(); // 0x00523100
    static void Destroy(); // 0x00523110
    static void Init(); // 0x00523120
    int CreateLog(); // 0x00523130
    stdiobuf * WriteLog(stdiobuf *Block, char a2); // 0x005231D0
    void GetFileSize(); // 0x005231F0
    int GetFileSize(); // 0x005232B0
    char RectIntersection(); // 0x00523560
};

#pragma once
// Auto-generated: PtrArray

class PtrArray {
public:
    void * * m_pData; // +0x0
    int m_nSize; // +0x4
    int m_nMaxSize; // +0x8
    int m_nGrowBy; // +0xC
    // total size: 0x10 (16)

    _DWORD * Clear(); // 0x00432660
    void SetAt(int a2, int a3); // 0x00432770
    int InsertAt(int a2, int a3); // 0x004327B0
    PtrArray(int a1, int a2, char a3); // 0x00434130
    ~PtrArray(); // 0x004341E0
    static void SetSize(); // 0x00434240
    static char * SetAtGrow(signed __int16 a1, int a2); // 0x004343B0
    static char * RemoveAt(const char *a1); // 0x004343F0
    void Remove(); // 0x00434490
    struct gbVFile * InsertAt(const char *a2); // 0x004344F0
};

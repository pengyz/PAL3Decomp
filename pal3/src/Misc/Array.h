#pragma once
// Auto-generated: Array

class Array {
public:
    char * m_pDataStart; // +0x0
    int m_nSize; // +0x4
    char * m_pData; // +0x8
    int m_nCapacity; // +0xC
    // total size: 0x10 (16)

    void Free(); // 0x00410960
    int InsertAt(char *pPos, int *pSrc); // 0x00410BD0
    int * CopyRange(int *p_DWORD, int *p_DWORD2); // 0x00410DF0
    void * Insert(void *pElem, void *pEnd); // 0x00411170
    int Size(); // 0x004111C0
    void * Erase(int nIndex, int nCount); // 0x004111E0
    static void * Copy(void *dst, void *src); // 0x00411240
    static unsigned int * PartialSort(unsigned int *pdwVal, unsigned int *pdwVal2, unsigned int dwVal, int nVal, int nVal2, int nVal3); // 0x004115C0
    static double HandleItemPage(int *pnVal, int nVal, int elem); // 0x0049CF80
    char * InsertBlocks(char *pszBuf, unsigned int dwVal, int *p_DWORD); // 0x004AF450
};

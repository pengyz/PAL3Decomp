#pragma once
// Auto-generated: PtrArray

#include "gbengine/gbVFileSystem.h"

class PtrArray {
public:
    char * m_pData; // +0x0
    int capacity; // +0x4
    int m_nSize; // +0x8
    int m_needscriptdel; // +0xC
    // total size: 0x10 (16)

    void * ReleasePtrArray(); // 0x004019B0
    int GetSize(); // 0x0040D620
    void * GetAt(void *pOut, unsigned int nIndex); // 0x0040D640
    void * Insert(void *pItem); // 0x0040D6B0
    BOOL Find(void *pKey, void *pResult); // 0x0040DBD0
    static BOOL CompareValues(int *p_DWORD, int *p_DWORD2); // 0x0040DCD0
    static unsigned int ParseStringPair(char *pszBuf, char *pszBuf2, void **a3); // 0x00411290
    int * Reset(); // 0x00431CB0
    void ConditionalCleanup(); // 0x00431E90
    static int IsArrayReady(char *String1); // 0x004325A0
    int * Clear(); // 0x00432660
    void SetAt(int nIndex, int newElement); // 0x00432770
    int RemoveAt(int nIndex, int nCount); // 0x004327B0
    int FindFirst(void *pData); // 0x004327F0
    static void ReadFromVFile(unsigned __int16 *pBuf, struct gbVFile *pFile); // 0x00433C50
    static int * CopyRange(int *p_DWORD, int nVal, int nVal2); // 0x00433DC0
    PtrArray(int nInitSize, int nGrowBy, char bOwned); // 0x00434130
    void _PtrArray(); // 0x004341E0
    void SetSize(); // 0x00434240
    static char * SetAtGrow(unsigned __int16 pData, int *nIndex); // 0x004343B0
    void RemoveAt(const char *nIndex); // 0x004343F0
    void Remove(); // 0x00434490
    void InsertAt(const char *nIndex); // 0x004344F0
    int DestroyAll(); // 0x00434670
    struct gbVFile * ReadFileSection(int nSection); // 0x004348E0
    PtrArray(); // 0x0044BD60
    PtrArray * ClearBoth(); // 0x0053D0B0
    void SetResolution(int nVal, int arg4); // 0x0053D1A0
};

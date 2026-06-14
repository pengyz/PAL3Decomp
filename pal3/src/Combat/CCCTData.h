#pragma once
// Auto-generated: CCCTData

#include "tagCCT.h"

class CCCTData {
public:
    tagCCT m_Pool[2000]; // +0x0
    char _gap_1F40[400000]; // +0x1F40
    _BYTE m_bPoolInUse[2000]; // +0x639C0
    int m_nCCTIndex[50][100]; // +0x64190
    // total size: 0x68FB0 (430000)

    void CalcDist(float fVal, float fVal2); // 0x0041C900
    int InitEntries(float fVal); // 0x0044D780
    int ProcessTask(int nVal); // 0x004533F0
    CCCTData * InitImages(); // 0x004A6730
    void DestroyImage(); // 0x004A67B0
    CCCTData(); // 0x004A6F10
    int CreateUI(); // 0x004A8770
    LRESULT UpdateDebugDialog(); // 0x004E7D70
    int UpdateCamera(int nVal); // 0x005044C0
    CCCTData(int *p_DWORD, int *p_DWORD2); // 0x005058F0
    void _CCCTData(); // 0x00505930
    bool Create(float *pfVal); // 0x00506020
    bool Destroy(); // 0x005060D0
    void Init(); // 0x005061A0
    char * Save(int nVal); // 0x00506260
    bool Load(float *pfVal); // 0x005062D0
    void InsertTaskToList(); // 0x005075E0
    void SwapTask(); // 0x00507B20
    bool ClearList(); // 0x00508190
    bool IsTaskValid(); // 0x005081A0
    void GetTaskNumInList(); // 0x005081B0
    void GetFreeSpaceInPool(); // 0x005081C0
};

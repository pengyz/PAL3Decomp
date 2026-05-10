#pragma once
// Auto-generated: CCCTData

#include "tagCCT.h"

class CCCTData {
public:
    tagCCT m_Pool[2000]; // +0x0
    BYTE m_bPoolInUse[2000]; // +0x639C0
    int m_nCCTIndex[50][100]; // +0x64190
    // total size: 0x68FB0 (430000)

    static void CalcDist(float a1, float a2); // 0x0041C900
    int UpdateCamera(int a2); // 0x005044C0
    CCCTData(_DWORD *a2, _DWORD *a3); // 0x005058F0
    ~CCCTData(); // 0x00505930
    bool Create(float *a2); // 0x00506020
    char Destroy(); // 0x005060D0
    void Init(); // 0x005061A0
    int Save(int a2); // 0x00506260
    int Load(int a2); // 0x005062D0
    void InsertTaskToList(); // 0x005075E0
    void SwapTask(); // 0x00507B20
    static int ClearList(); // 0x00508190
    static int IsTaskValid(); // 0x005081A0
    static void GetTaskNumInList(); // 0x005081B0
    static void GetFreeSpaceInPool(); // 0x005081C0
};

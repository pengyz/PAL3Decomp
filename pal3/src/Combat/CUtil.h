#pragma once
// Auto-generated: CUtil

#include "UIItem.h"

class CScreenMode;
class PalScript;
class PropUI;
class UIWnd;

class CUtil {
public:
    // vtable (6 methods, order matches binary layout)

    BYTE m_bCanWarp; // +0x0
    char _gap_001[3]; // +0x1
    short m_nRandHolder; // +0x4
    char _gap_006[2]; // +0x6
    int m_nRandCallCount; // +0x8
    FILE * m_fLog; // +0xC
    char * m_sLogFileName; // +0x10
    char m_szLogPath[260]; // +0x14
    char * m_pDefaultString; // +0x118
    char _gap_11C[68]; // +0x11C
    void * _todo_160; // +0x160
    char _gap_164[4]; // +0x164
    int _todo_168; // +0x168
    int _todo_16C; // +0x16C
    UIItem _embed_UIItem_368; // +0x170
    char _gap_174[972]; // +0x174
    int _todo_540; // +0x540
    int _todo_544; // +0x544
    char _gap_548[384]; // +0x548
    CScreenMode * m_pScreenMode; // +0x6C8
    char * m_pBattleSystem; // +0x6CC
    char * m_pListView; // +0x6D0
    PropUI * m_pPropUI; // +0x6D4
    int m_nRenderMode; // +0x6D8
    char _tail_6DC[16]; // +0x6DC
    // total size: 0x6EC (1772)

    virtual int RenderFrame(); // 0x00523670
    static void SetDisablePicDw(char *pszScene); // 0x005236E0
    virtual UIWnd * WriteLog(CUtil *Block, char format); // 0x005231D0
    void _CUtil(); // 0x005230F0
    bool Create(); // 0x00523100
    void Destroy(); // 0x00523110
    void Init(); // 0x00523120
    CUtil(); // 0x00523130
    void _CUtil_31f0(); // 0x005231F0
    int InitGameSystems(); // 0x005232B0
    bool RectIntersection(); // 0x00523560
    int CalulateParabola(); // 0x00523600
    int Update(float nDelta); // 0x00523820
    int DispatchCommand(int *pCmd); // 0x00523E80
};

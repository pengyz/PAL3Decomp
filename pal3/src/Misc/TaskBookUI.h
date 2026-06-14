#include "UIFrameWnd.h"
#pragma once
// Auto-generated: TaskBookUI

#include "MUIDialog.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIParticle.h"
#include "UIScrollBar.h"
#include "UIStatic.h"

class StateUI;

class TaskBookUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    BYTE m_IsCreateable; // +0x60
    BYTE m_IsActive; // +0x61
    char _gap_062[2]; // +0x62
    StateUI * pStateUI; // +0x64
    UIStatic m_OutFrameT; // +0x68
    char _gap_06C[156]; // +0x6C
    UIStatic m_OutFrameR; // +0x108
    char _gap_10C[156]; // +0x10C
    UIStatic m_OutFrameL; // +0x1A8
    char _gap_1AC[156]; // +0x1AC
    UIStatic m_OutFrameB; // +0x248
    char _gap_24C[156]; // +0x24C
    UIStatic stp_BarL; // +0x2E8
    char _gap_2EC[156]; // +0x2EC
    UIFlexBar stp_BarM; // +0x388
    char _gap_38C[80]; // +0x38C
    UIStatic stp_BarR; // +0x3DC
    char _gap_3E0[156]; // +0x3E0
    UIButton stp_State; // +0x47C
    char _gap_480[340]; // +0x480
    UIButton stp_Magic; // +0x5D4
    char _gap_5D8[340]; // +0x5D8
    UIButton stp_Equip; // +0x72C
    char _gap_730[340]; // +0x730
    UIButton stp_Prop; // +0x884
    char _gap_888[340]; // +0x888
    UIButton stp_BattleArray; // +0x9DC
    char _gap_9E0[340]; // +0x9E0
    UIButton stp_TaskBook; // +0xB34
    char _gap_B38[340]; // +0xB38
    UIButton stp_System; // +0xC8C
    char _gap_C90[340]; // +0xC90
    UIButton stp_Exit; // +0xDE4
    char _gap_DE8[340]; // +0xDE8
    UIStatic stp_Effect; // +0xF3C
    char _gap_F40[156]; // +0xF40
    tagRECT stp_Rect; // +0xFDC
    char _gap_FE0[12]; // +0xFE0
    MUIDialog m_DlgEx; // +0xFEC
    char _gap_FF0[1380]; // +0xFF0
    UIParticle m_btnPar[16][7]; // +0x1554
    char _gap_1714[65856]; // +0x1714
    UIParticle m_btnPar2[16][7]; // +0x11854
    char _gap_11A14[65856]; // +0x11A14
    tagRECT m_btnParRc[7]; // +0x21B54
    char _gap_21B70[84]; // +0x21B70
    _BYTE _isParBtn[7]; // +0x21BC4
    char _gap_21BCB[1]; // +0x21BCB
    int _curParEffect; // +0x21BCC
    UIStatic m_ListBK; // +0x21BD0
    char _gap_21BD4[156]; // +0x21BD4
    UIStatic m_ListTitle; // +0x21C70
    char _gap_21C74[156]; // +0x21C74
    UIButton m_ListBtn[9]; // +0x21D10
    char _gap_21D34[3060]; // +0x21D34
    UIStatic m_ListBtnBkL; // +0x22928
    char _gap_2292C[156]; // +0x2292C
    UIStatic m_ListBtnBkR; // +0x229C8
    char _gap_229CC[156]; // +0x229CC
    UIScrollBar m_Scroll; // +0x22A68
    char _gap_22A6C[364]; // +0x22A6C
    int m_IsScroll; // +0x22BD8
    UIStatic m_ScrollHB; // +0x22BDC
    char _gap_22BE0[156]; // +0x22BE0
    UIStatic m_TaskBk; // +0x22C7C
    char _gap_22C80[156]; // +0x22C80
    UIStatic m_TaskPicBk; // +0x22D1C
    char _gap_22D20[156]; // +0x22D20
    UIStatic m_TaskPic; // +0x22DBC
    char _gap_22DC0[156]; // +0x22DC0
    UIStatic m_TaskDesc; // +0x22E5C
    char _gap_22E60[156]; // +0x22E60
    UIStatic m_TaskTitle; // +0x22EFC
    char _gap_22F00[156]; // +0x22F00
    UIStatic m_TaskState; // +0x22F9C
    char _gap_22FA0[156]; // +0x22FA0
    int m_SelItem; // +0x2303C
    int m_FirstItem; // +0x23040
    int m_TotalItem; // +0x23044
    char _tail_23048[240]; // +0x23048
    // total size: 0x23138 (143672)

    void _TaskBookUI(); // 0x00454830
    void _TaskBookUI_4ba0(); // 0x00454BA0
    void * CreateEntry(int nVal, int nVal2, int nVal3, int nVal4); // 0x00454CA0
    int RefreshTaskList(); // 0x004551A0
    int * AdvancePage(); // 0x004554D0
    int * RefreshElements(); // 0x00455790
    char ScrollUp(char pData); // 0x00455A20
    char ScrollDown(char pData); // 0x00455B30
    void HandleInput(); // 0x00455C40
    int SaveData(); // 0x00455F20
    int _TaskBookUI_6220(); // 0x00456220
    void HandleNavigation(); // 0x004562C0
    int ValidateEntries(); // 0x004566C0
    void SetEntryCaption(int nVal, int nVal2); // 0x00477A90
};

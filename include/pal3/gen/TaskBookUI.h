#pragma once
// Auto-generated: TaskBookUI

#include "MUIDialog.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIParticle.h"
#include "UIScrollBar.h"
#include "UIStatic.h"

class StateUI;

class TaskBookUI : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    unsigned char m_IsCreateable; // +0x60
    unsigned char m_IsActive; // +0x61
    StateUI * pStateUI; // +0x64
    UIStatic m_OutFrameT; // +0x68
    UIStatic m_OutFrameR; // +0x108
    UIStatic m_OutFrameL; // +0x1A8
    UIStatic m_OutFrameB; // +0x248
    UIStatic stp_BarL; // +0x2E8
    UIFlexBar stp_BarM; // +0x388
    UIStatic stp_BarR; // +0x3DC
    UIButton stp_State; // +0x47C
    UIButton stp_Magic; // +0x5D4
    UIButton stp_Equip; // +0x72C
    UIButton stp_Prop; // +0x884
    UIButton stp_BattleArray; // +0x9DC
    UIButton stp_TaskBook; // +0xB34
    UIButton stp_System; // +0xC8C
    UIButton stp_Exit; // +0xDE4
    UIStatic stp_Effect; // +0xF3C
    tagRECT stp_Rect; // +0xFDC
    MUIDialog m_DlgEx; // +0xFEC
    UIParticle m_btnPar[16][7]; // +0x1554
    UIParticle m_btnPar2[16][7]; // +0x11854
    tagRECT m_btnParRc[7]; // +0x21B54
    unsigned char _isParBtn[7]; // +0x21BC4
    int _curParEffect; // +0x21BCC
    UIStatic m_ListBK; // +0x21BD0
    UIStatic m_ListTitle; // +0x21C70
    UIButton m_ListBtn[9]; // +0x21D10
    UIStatic m_ListBtnBkL; // +0x22928
    UIStatic m_ListBtnBkR; // +0x229C8
    UIScrollBar m_Scroll; // +0x22A68
    int m_IsScroll; // +0x22BD8
    UIStatic m_ScrollHB; // +0x22BDC
    UIStatic m_TaskBk; // +0x22C7C
    UIStatic m_TaskPicBk; // +0x22D1C
    UIStatic m_TaskPic; // +0x22DBC
    UIStatic m_TaskDesc; // +0x22E5C
    UIStatic m_TaskTitle; // +0x22EFC
    UIStatic m_TaskState; // +0x22F9C
    int m_SelItem; // +0x2303C
    int m_FirstItem; // +0x23040
    int m_TotalItem; // +0x23044
    UIStatic m_FrameUp; // +0x23048
    UIStatic m_FrameDw; // +0x230E8
    UIStatic m_FrameRight; // +0x23188
    // total size: 0x23228 (143912)

};

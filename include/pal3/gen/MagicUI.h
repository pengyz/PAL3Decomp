#pragma once
// Auto-generated: MagicUI

#include "DLG_MSG.h"
#include "MUIDialog.h"
#include "SkillData.h"
#include "UIAnimate.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIListBox.h"
#include "UIParticle.h"
#include "UIStatic.h"
#include "m_RoleState.h"
#include "tagPOINT.h"
#include "tagRECT.h"

class StateUI;

class MagicUI : public UIFrameWnd {
public:
    tagRECT rc; // +0x48
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[256]; // +0x68
    char remarkbuf[256]; // +0x168
    int s_x; // +0x268
    unsigned char m_IsMsg; // +0x26C
    unsigned char m_Is[5]; // +0x26D
    int m_CtrlRole; // +0x274
    unsigned char m_IsActive; // +0x278
    unsigned char m_IsCreateable; // +0x279
    int curPage; // +0x27C
    int m_SelNum; // +0x280
    int m_CurType; // +0x284
    int m_usemagicRole; // +0x288
    unsigned char m_isuseMagic; // +0x28C
    unsigned char m_LockUse; // +0x28D
    unsigned char m_IsUsed; // +0x28E
    unsigned char m_IsCanUse; // +0x28F
    unsigned char m_IsAllUse; // +0x290
    tagPOINT pt; // +0x294
    SkillData m_RoleSkill[7][5]; // +0x29C
    StateUI * pStateUI; // +0xA594
    UIStatic m_Frame; // +0xA598
    UIStatic m_TimeMoney; // +0xA638
    UIStatic m_OutFrameT; // +0xA6D8
    UIStatic m_OutFrameR; // +0xA778
    UIStatic m_OutFrameL; // +0xA818
    UIStatic m_OutFrameB; // +0xA8B8
    UIStatic stp_BarL; // +0xA958
    UIFlexBar stp_BarM; // +0xA9F8
    UIStatic stp_BarR; // +0xAA4C
    UIButton stp_State; // +0xAAEC
    UIButton stp_Magic; // +0xAC44
    UIButton stp_Equip; // +0xAD9C
    UIButton stp_Prop; // +0xAEF4
    UIButton stp_BattleArray; // +0xB04C
    UIButton stp_TaskBook; // +0xB1A4
    UIButton stp_System; // +0xB2FC
    UIButton stp_Exit; // +0xB454
    UIStatic stp_Effect; // +0xB5AC
    tagRECT stp_Rect; // +0xB64C
    tagRECT titleRc; // +0xB65C
    UIStatic m_title[4]; // +0xB66C
    UIStatic m_GameTime; // +0xB8EC
    UIStatic m_GameMoney; // +0xB98C
    MUIDialog m_DlgEx; // +0xBA2C
    UIParticle m_btnPar[16][7]; // +0xBF94
    UIParticle m_btnPar2[16][7]; // +0x1C294
    tagRECT m_btnParRc[7]; // +0x2C594
    unsigned char _isParBtn[7]; // +0x2C604
    int _curParEffect; // +0x2C60C
    int m_CurSelRole; // +0x2C610
    int m_CurNeedRole; // +0x2C614
    MUIDialog m_Dlg; // +0x2C618
    MUIDialog m_Msg; // +0x2CB80
    DLG_MSG m_DlgMsg; // +0x2D0E8
    UIAnimate m_Animate[5]; // +0x2D0EC
    tagRECT m_AnimateRc[5]; // +0x2D1F0
    UIStatic m_ListFrame; // +0x2D240
    UIStatic m_ListGrid[8]; // +0x2D2E0
    UIStatic m_RemarkBk; // +0x2D7E0
    UIStatic m_Remark; // +0x2D880
    UIStatic m_RemarkVal; // +0x2D920
    UIStatic m_UnCom; // +0x2D9C0
    m_RoleState m_Role[5]; // +0x2DA60
    UIButton m_Ctrlbtn[7]; // +0x32E34
    UIListBox ml_SpeList; // +0x3379C
    UIListBox ml_FengList; // +0x33CA4
    UIListBox ml_LeiList; // +0x341AC
    UIListBox ml_ShuiList; // +0x346B4
    UIListBox ml_HuoList; // +0x34BBC
    UIListBox ml_TuList; // +0x350C4
    UIListBox ml_SuangList; // +0x355CC
    UIStatic m_TopFrame; // +0x35AD4
    UIStatic m_TopFrameXS; // +0x35B74
    UIParticle m_parRainbow[8][5]; // +0x35C14
    UIParticle m_parRise[8][5]; // +0x3B894
    tagRECT m_parRc[5]; // +0x41514
    unsigned char m_ComSkill[8][5]; // +0x0
    // total size: 0x41564 (267620)

    int Create(); // 0x004A4AC0
    void Init(); // 0x004A4B70
};

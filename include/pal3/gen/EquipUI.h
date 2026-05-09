#pragma once
// Auto-generated: EquipUI

#include "BtnGroup.h"
#include "MUIDialog.h"
#include "PlayerAtt.h"
#include "UI3DCtrl.h"
#include "UIAnimate.h"
#include "UIAnimateCtrl.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIListBox.h"
#include "UIStatic.h"
#include "UIStaticRM.h"
#include "UITabBtn.h"
#include "st_Manager.h"
#include "tagRECT.h"

class DealUI;
class PlayerItem;

class EquipUI : public UIFrameWnd {
public:
    int bkWndX; // +0x48
    int bkWndY; // +0x4C
    char buf[256]; // +0x50
    int m_SelNum; // +0x150
    int * m_ListNum; // +0x154
    int m_x; // +0x158
    int m_y; // +0x15C
    int m_Sum; // +0x160
    int i; // +0x164
    int j; // +0x168
    int k; // +0x16C
    unsigned char _isCreatable; // +0x170
    float _flashSpeed; // +0x174
    st_Manager m_EquipData; // +0x178
    PlayerItem * p_DealData; // +0x45D8
    PlayerAtt m_TempData[5]; // +0x45DC
    tagRECT rc; // +0x63A0
    UIStatic m_Frame; // +0x63B0
    UIFlexBar m_FrameBar; // +0x6450
    UIStatic m_Flag; // +0x64A4
    UIStatic m_OutFrameT; // +0x6544
    UIStatic m_OutFrameR; // +0x65E4
    UIStatic m_OutFrameL; // +0x6684
    UIStatic m_OutFrameB; // +0x6724
    UIAnimateCtrl m_ani; // +0x67C4
    UIStatic m_Role[5]; // +0x6868
    tagRECT m_RoleRc[5]; // +0x6B88
    int RoleX; // +0x6BD8
    int RoleY; // +0x6BDC
    int HeadW; // +0x6BE0
    int HeadH; // +0x6BE4
    unsigned char m_Is[5]; // +0x6BE8
    UIStatic m_Arrow[8][6][5]; // +0x6BF0
    UIStatic m_ArrowNum[8][2][5]; // +0x101F0
    tagRECT m_ArrowRc[8][6][5]; // +0x133F0
    unsigned char m_IsArrow[8][6][5]; // +0x142F0
    int m_OldSelect; // +0x143E0
    unsigned char m_IsMove[8][6][5]; // +0x143E4
    tagRECT m_AnimateRc[8][6][5]; // +0x144D4
    UIAnimate m_ArrowMove[8][6][5]; // +0x153D4
    UIStaticRM m_Icon[6][5]; // +0x18494
    UIStatic m_Select[6][5]; // +0x19A9C
    unsigned char m_IsControlEquip; // +0x1AD5C
    unsigned char m_IsEquip[6][5]; // +0x1AD5D
    unsigned char m_IsMsg; // +0x1AD7B
    int * m_EquipingNum; // +0x1AD7C
    int m_Equiping[6][5]; // +0x1AD80
    int * m_UnEquipingNum; // +0x1ADF8
    int * m_MaxNum; // +0x1ADFC
    unsigned char m_Adorn[2][5]; // +0x1AE00
    UI3DCtrl m_3DObj; // +0x1AE0C
    MUIDialog m_Msg; // +0x1AF40
    UIStatic m_TalkFrame; // +0x1B4A8
    UIStatic m_Ready; // +0x1B548
    tagRECT m_ReadyRc; // +0x1B5E8
    UIButton mb_EquipYes; // +0x1B5F8
    UIButton mb_EquipNo; // +0x1B750
    UIStatic m_EquipTalk; // +0x1B8A8
    tagRECT m_EquipRc; // +0x1B948
    UIStatic m_ListFrame; // +0x1B958
    UIStatic m_ListGrid[14]; // +0x1B9F8
    UIStatic m_ScrollHB; // +0x1C2B8
    UIStatic m_EquipFlag; // +0x1C358
    UIStatic m_ListEquipTitle; // +0x1C3F8
    UIListBox ml_ListEquip; // +0x1C498
    tagRECT ml_ListEquipRc; // +0x1C9A0
    BtnGroup m_btnGroup; // +0x1C9B0
    float m_ctrlTime; // +0x1CC94
    unsigned char m_bCanUpdate1; // +0x1CC98
    unsigned char m_bCanUpdate2; // +0x1CC99
    UIStatic m_EquipRemarkBk; // +0x1CC9C
    UIStatic m_EquipRemark; // +0x1CD3C
    tagRECT m_EquipRemarkRc; // +0x1CDDC
    UIStatic m_EquipAtt; // +0x1CDEC
    tagRECT m_EquipAttRc; // +0x1CE8C
    UIStatic m_MoneyRemark; // +0x1CE9C
    tagRECT m_MoneyRc; // +0x1CF3C
    UIStatic m_SumEquip; // +0x1CF4C
    tagRECT m_SumRc; // +0x1CFEC
    UIButton mb_OK; // +0x1CFFC
    tagRECT mb_OKRc; // +0x1D154
    unsigned char m_IsDicker; // +0x1D164
    UIButton mb_Cancel; // +0x1D168
    tagRECT mb_CancelRc; // +0x1D2C0
    UIButton mb_Exit; // +0x1D2D0
    tagRECT mb_ExitRc; // +0x1D428
    UITabBtn m_TabBtn; // +0x1D438
    tagRECT mb_DKRc; // +0x1D450
    tagRECT haveRc; // +0x1D460
    unsigned char m_isCancelTalk; // +0x1D470
    unsigned char m_IsRefuse; // +0x1D471
    char m_strIn[256][2]; // +0x1D472
    unsigned char m_IsTalk; // +0x1D672
    int m_TalkCount; // +0x1D674
    int m_talker; // +0x1D678
    int m_TalkFlag; // +0x1D67C
    unsigned char m_bDK; // +0x1D680
    int m_DkNum; // +0x1D684
    int mb_DkFlag; // +0x1D688
    unsigned long * m_DealID; // +0x1D68C
    int DealNum; // +0x1D690
    int curID; // +0x1D694
    unsigned char m_IsUse; // +0x1D698
    unsigned char m_IsDeal; // +0x1D699
    DealUI * pDealUI; // +0x1D69C
    unsigned char m_isSetData; // +0x1D6A0
    // total size: 0x1D6A4 (120484)

    int Create(); // 0x004A1E40
    void Init(); // 0x004A4220
    void InitSlots(); // 0x004A48B0
};

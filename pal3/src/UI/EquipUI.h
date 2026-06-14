#include "UIFrameWnd.h"
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
#include "UIListBox.h"
#include "UIStatic.h"
#include "UIStaticRM.h"
#include "UITabBtn.h"
#include "st_Manager.h"

class PlayerItem;

class EquipUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
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
    BYTE _isCreatable; // +0x170
    char _gap_171[3]; // +0x171
    float _flashSpeed; // +0x174
    st_Manager m_EquipData; // +0x178
    char _gap_17C[17500]; // +0x17C
    PlayerItem * p_DealData; // +0x45D8
    PlayerAtt m_TempData[5]; // +0x45DC
    char _gap_45F0[7600]; // +0x45F0
    tagRECT rc; // +0x63A0
    char _gap_63A4[12]; // +0x63A4
    UIStatic m_Frame; // +0x63B0
    char _gap_63B4[156]; // +0x63B4
    UIFlexBar m_FrameBar; // +0x6450
    char _gap_6454[80]; // +0x6454
    UIStatic m_Flag; // +0x64A4
    char _gap_64A8[156]; // +0x64A8
    UIStatic m_OutFrameT; // +0x6544
    char _gap_6548[156]; // +0x6548
    UIStatic m_OutFrameR; // +0x65E4
    char _gap_65E8[156]; // +0x65E8
    UIStatic m_OutFrameL; // +0x6684
    char _gap_6688[156]; // +0x6688
    UIStatic m_OutFrameB; // +0x6724
    char _gap_6728[156]; // +0x6728
    UIAnimateCtrl m_ani; // +0x67C4
    char _gap_67C8[160]; // +0x67C8
    UIStatic m_Role[5]; // +0x6868
    char _gap_687C[780]; // +0x687C
    tagRECT m_RoleRc[5]; // +0x6B88
    char _gap_6B9C[60]; // +0x6B9C
    int RoleX; // +0x6BD8
    int RoleY; // +0x6BDC
    int HeadW; // +0x6BE0
    int HeadH; // +0x6BE4
    _BYTE m_Is[5]; // +0x6BE8
    char _gap_6BED[3]; // +0x6BED
    UIStatic m_Arrow[8][6][5]; // +0x6BF0
    char _gap_6FB0[37440]; // +0x6FB0
    UIStatic m_ArrowNum[8][2][5]; // +0x101F0
    char _gap_10330[12480]; // +0x10330
    tagRECT m_ArrowRc[8][6][5]; // +0x133F0
    char _gap_137B0[2880]; // +0x137B0
    _BYTE m_IsArrow[8][6][5]; // +0x142F0
    int m_OldSelect; // +0x143E0
    _BYTE m_IsMove[8][6][5]; // +0x143E4
    tagRECT m_AnimateRc[8][6][5]; // +0x144D4
    char _gap_14894[2880]; // +0x14894
    UIAnimate m_ArrowMove[8][6][5]; // +0x153D4
    char _gap_15794[11520]; // +0x15794
    UIStaticRM m_Icon[6][5]; // +0x18494
    char _gap_1850C[5520]; // +0x1850C
    UIStatic m_Select[6][5]; // +0x19A9C
    char _gap_19B14[4680]; // +0x19B14
    BYTE m_IsControlEquip; // +0x1AD5C
    _BYTE m_IsEquip[6][5]; // +0x1AD5D
    BYTE m_IsMsg; // +0x1AD7B
    int * m_EquipingNum; // +0x1AD7C
    int m_Equiping[6][5]; // +0x1AD80
    int * m_UnEquipingNum; // +0x1ADF8
    int * m_MaxNum; // +0x1ADFC
    _BYTE m_Adorn[2][5]; // +0x1AE00
    char _gap_1AE0A[2]; // +0x1AE0A
    UI3DCtrl m_3DObj; // +0x1AE0C
    char _gap_1AE10[304]; // +0x1AE10
    MUIDialog m_Msg; // +0x1AF40
    char _gap_1AF44[1380]; // +0x1AF44
    UIStatic m_TalkFrame; // +0x1B4A8
    char _gap_1B4AC[156]; // +0x1B4AC
    UIStatic m_Ready; // +0x1B548
    char _gap_1B54C[156]; // +0x1B54C
    tagRECT m_ReadyRc; // +0x1B5E8
    char _gap_1B5EC[12]; // +0x1B5EC
    UIButton mb_EquipYes; // +0x1B5F8
    char _gap_1B5FC[340]; // +0x1B5FC
    UIButton mb_EquipNo; // +0x1B750
    char _gap_1B754[340]; // +0x1B754
    UIStatic m_EquipTalk; // +0x1B8A8
    char _gap_1B8AC[156]; // +0x1B8AC
    tagRECT m_EquipRc; // +0x1B948
    char _gap_1B94C[12]; // +0x1B94C
    UIStatic m_ListFrame; // +0x1B958
    char _gap_1B95C[156]; // +0x1B95C
    UIStatic m_ListGrid[14]; // +0x1B9F8
    char _gap_1BA30[2184]; // +0x1BA30
    UIStatic m_ScrollHB; // +0x1C2B8
    char _gap_1C2BC[156]; // +0x1C2BC
    UIStatic m_EquipFlag; // +0x1C358
    char _gap_1C35C[156]; // +0x1C35C
    UIStatic m_ListEquipTitle; // +0x1C3F8
    char _gap_1C3FC[156]; // +0x1C3FC
    UIListBox ml_ListEquip; // +0x1C498
    char _gap_1C49C[1284]; // +0x1C49C
    tagRECT ml_ListEquipRc; // +0x1C9A0
    char _gap_1C9A4[12]; // +0x1C9A4
    BtnGroup m_btnGroup; // +0x1C9B0
    char _gap_1C9B4[736]; // +0x1C9B4
    float m_ctrlTime; // +0x1CC94
    BYTE m_bCanUpdate1; // +0x1CC98
    BYTE m_bCanUpdate2; // +0x1CC99
    char _gap_1CC9A[2]; // +0x1CC9A
    UIStatic m_EquipRemarkBk; // +0x1CC9C
    char _gap_1CCA0[156]; // +0x1CCA0
    UIStatic m_EquipRemark; // +0x1CD3C
    char _gap_1CD40[156]; // +0x1CD40
    tagRECT m_EquipRemarkRc; // +0x1CDDC
    char _gap_1CDE0[12]; // +0x1CDE0
    UIStatic m_EquipAtt; // +0x1CDEC
    char _gap_1CDF0[156]; // +0x1CDF0
    tagRECT m_EquipAttRc; // +0x1CE8C
    char _gap_1CE90[12]; // +0x1CE90
    UIStatic m_MoneyRemark; // +0x1CE9C
    char _gap_1CEA0[156]; // +0x1CEA0
    tagRECT m_MoneyRc; // +0x1CF3C
    char _gap_1CF40[12]; // +0x1CF40
    UIStatic m_SumEquip; // +0x1CF4C
    char _gap_1CF50[156]; // +0x1CF50
    tagRECT m_SumRc; // +0x1CFEC
    char _gap_1CFF0[12]; // +0x1CFF0
    UIButton mb_OK; // +0x1CFFC
    char _gap_1D000[340]; // +0x1D000
    tagRECT mb_OKRc; // +0x1D154
    char _gap_1D158[12]; // +0x1D158
    BYTE m_IsDicker; // +0x1D164
    char _gap_1D165[3]; // +0x1D165
    UIButton mb_Cancel; // +0x1D168
    char _gap_1D16C[340]; // +0x1D16C
    tagRECT mb_CancelRc; // +0x1D2C0
    char _gap_1D2C4[12]; // +0x1D2C4
    UIButton mb_Exit; // +0x1D2D0
    char _gap_1D2D4[340]; // +0x1D2D4
    tagRECT mb_ExitRc; // +0x1D428
    char _gap_1D42C[12]; // +0x1D42C
    UITabBtn m_TabBtn; // +0x1D438
    char _gap_1D43C[20]; // +0x1D43C
    tagRECT mb_DKRc; // +0x1D450
    char _gap_1D454[12]; // +0x1D454
    tagRECT haveRc; // +0x1D460
    char _gap_1D464[12]; // +0x1D464
    BYTE m_isCancelTalk; // +0x1D470
    char _tail_1D471[195]; // +0x1D471
    // total size: 0x1D534 (120116)

    virtual ~EquipUI() {}

    virtual void RenderEffects(); // 0x0049FE00
    virtual BOOL Update(int nVal, int nVal2); // 0x004A00B0
    virtual void HandleEquipEvent(int nVal, char *pszBuf, int nVal2); // 0x004A0370
    int ShowPage(); // 0x00484D20
    int SelectTab0(unsigned __int8 nTab); // 0x00484E70
    int SetSubTab(unsigned __int8 nTab); // 0x0048A2F0
    void UpdateSlot(int nSlotIdx, int nItemID, int nCount); // 0x00494040
    int SelectBigMapTab0(char nTab); // 0x004945C0
    void HandleInput(int nInputID, int nParam); // 0x00494D70
    int ctor(); // 0x00498820
    void ctor_9030(); // 0x00499030
    int SetSubTab2(unsigned __int8 nTab); // 0x0049E840
    int SetGroupVisible(unsigned __int8 bVisible); // 0x0049F9B0
    int InitParticleEffects(int nVal); // 0x0049FA10
    BOOL UpdateDisplay(int nPage, int nSlot); // 0x0049FBE0
    int FindNextSlot(int *pCounter); // 0x0049FF30
    int FindPrevSlot(int *pCounter); // 0x0049FF60
    char HandleInput(); // 0x0049FF90
    int InitUI(); // 0x004A1E40
    void Init(); // 0x004A4220
    int GetSelected(); // 0x004A4890
    void InitSlots(); // 0x004A48B0
    int Create(); // 0x004A4C20
    int InitEquipUI(int nVal); // 0x004AB6B0
    static void ControlDealBTWnd(uchar); // 0x005137EF
};

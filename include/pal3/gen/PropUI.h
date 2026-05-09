#pragma once
// Auto-generated: PropUI

#include "BtnGroup.h"
#include "MUIDialog.h"
#include "UI3DCtrl.h"
#include "UIAnimateCtrl.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIFrameWnd.h"
#include "UIListBox.h"
#include "UIStatic.h"
#include "UITabBtn.h"
#include "st_Manager.h"
#include "tagRECT.h"

class DealUI;
class PlayerItem;

class PropUI : public UIFrameWnd {
public:
    int bkWndX; // +0x48
    int bkWndY; // +0x4C
    int m_ListWidth; // +0x50
    int m_ListHeight; // +0x54
    st_Manager m_PropData; // +0x58
    PlayerItem * p_DealData; // +0x44B8
    char buf[256]; // +0x44BC
    char remarkbuf[256]; // +0x45BC
    int m_SelNum; // +0x46BC
    int * m_ListSelNum; // +0x46C0
    int * m_MaxNum; // +0x46C4
    int m_x; // +0x46C8
    int m_y; // +0x46CC
    int m_Sum; // +0x46D0
    int i; // +0x46D4
    int j; // +0x46D8
    unsigned char _isCreatable; // +0x46DC
    UIStatic m_Frame; // +0x46E0
    UIFlexBar m_FrameBar; // +0x4780
    UIStatic m_Flag; // +0x47D4
    UIStatic m_OutFrameT; // +0x4874
    UIStatic m_OutFrameR; // +0x4914
    UIStatic m_OutFrameL; // +0x49B4
    UIStatic m_OutFrameB; // +0x4A54
    tagRECT mb_ExitRc; // +0x4AF4
    UIButton mb_Exit; // +0x4B04
    UIAnimateCtrl m_ani; // +0x4C5C
    UIStatic m_Role[5]; // +0x4D00
    tagRECT m_RoleRc[5]; // +0x5020
    int RoleX; // +0x5070
    int RoleY; // +0x5074
    int HeadW; // +0x5078
    int HeadH; // +0x507C
    unsigned char m_Is[5]; // +0x5080
    MUIDialog m_Msg; // +0x5088
    UI3DCtrl m_3DObj; // +0x55F0
    UIStatic m_Dlg; // +0x5724
    tagRECT m_DlgRc; // +0x57C4
    UIStatic m_TalkFrame; // +0x57D4
    UIStatic m_Ready; // +0x5874
    tagRECT m_ReadyRc; // +0x5914
    UIStatic m_ListFrame; // +0x5924
    UIStatic m_ListGrid[14]; // +0x59C4
    UIStatic m_ScrollHB; // +0x6284
    UIStatic m_EquipFlag; // +0x6324
    UIStatic m_ListPropTitle; // +0x63C4
    tagRECT m_ListPropTitleRc; // +0x6464
    UIListBox ml_ListProp; // +0x6474
    tagRECT ml_ListPropRc; // +0x697C
    BtnGroup m_btnGroup; // +0x698C
    float m_ctrlTime; // +0x6C70
    unsigned char m_bCanUpdate1; // +0x6C74
    unsigned char m_bCanUpdate2; // +0x6C75
    UIStatic m_PropRemarkBk; // +0x6C78
    UIStatic m_PropRemark; // +0x6D18
    UIStatic m_PropAtt; // +0x6DB8
    UIStatic m_MoneyRemark; // +0x6E58
    tagRECT m_MoneyRc; // +0x6EF8
    UIStatic m_SumProp; // +0x6F08
    tagRECT m_SumRc; // +0x6FA8
    UIButton mb_OK; // +0x6FB8
    tagRECT mb_OKRc; // +0x7110
    unsigned char m_IsDeal; // +0x7120
    UIButton mb_Cancel; // +0x7124
    tagRECT mb_CancelRc; // +0x727C
    unsigned long * m_DealID; // +0x728C
    int DealNum; // +0x7290
    int curID; // +0x7294
    unsigned char m_isBuy; // +0x7298
    unsigned char b_IsExterior; // +0x7299
    int exterior_num; // +0x729C
    float discount_price; // +0x72A0
    int m_extmode; // +0x72A4
    DealUI * pDealUI; // +0x72A8
    UITabBtn m_TabBtn; // +0x72AC
    unsigned char m_opt; // +0x72C4
    // total size: 0x72C8 (29384)

    int Create(); // 0x00452580
    void Init(); // 0x00452670
};

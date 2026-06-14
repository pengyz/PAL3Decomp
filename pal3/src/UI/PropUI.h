#include "UIFrameWnd.h"
#pragma once
// Auto-generated: PropUI

#include "BtnGroup.h"
#include "MUIDialog.h"
#include "UI3DCtrl.h"
#include "UIAnimateCtrl.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIListBox.h"
#include "UIStatic.h"
#include "st_Manager.h"

class PlayerItem;

class PropUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    int bkWndX; // +0x48
    int bkWndY; // +0x4C
    int m_ListWidth; // +0x50
    int m_ListHeight; // +0x54
    st_Manager m_PropData; // +0x58
    char _gap_05C[17500]; // +0x5C
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
    BYTE _isCreatable; // +0x46DC
    char _gap_46DD[3]; // +0x46DD
    UIStatic m_Frame; // +0x46E0
    char _gap_46E4[156]; // +0x46E4
    UIFlexBar m_FrameBar; // +0x4780
    char _gap_4784[80]; // +0x4784
    UIStatic m_Flag; // +0x47D4
    char _gap_47D8[156]; // +0x47D8
    UIStatic m_OutFrameT; // +0x4874
    char _gap_4878[156]; // +0x4878
    UIStatic m_OutFrameR; // +0x4914
    char _gap_4918[156]; // +0x4918
    UIStatic m_OutFrameL; // +0x49B4
    char _gap_49B8[156]; // +0x49B8
    UIStatic m_OutFrameB; // +0x4A54
    char _gap_4A58[156]; // +0x4A58
    tagRECT mb_ExitRc; // +0x4AF4
    char _gap_4AF8[12]; // +0x4AF8
    UIButton mb_Exit; // +0x4B04
    char _gap_4B08[340]; // +0x4B08
    UIAnimateCtrl m_ani; // +0x4C5C
    char _gap_4C60[160]; // +0x4C60
    UIStatic m_Role[5]; // +0x4D00
    char _gap_4D14[780]; // +0x4D14
    tagRECT m_RoleRc[5]; // +0x5020
    char _gap_5034[60]; // +0x5034
    int RoleX; // +0x5070
    int RoleY; // +0x5074
    int HeadW; // +0x5078
    int HeadH; // +0x507C
    _BYTE m_Is[5]; // +0x5080
    char _gap_5085[3]; // +0x5085
    MUIDialog m_Msg; // +0x5088
    char _gap_508C[1380]; // +0x508C
    UI3DCtrl m_3DObj; // +0x55F0
    char _gap_55F4[304]; // +0x55F4
    UIStatic m_Dlg; // +0x5724
    char _gap_5728[156]; // +0x5728
    tagRECT m_DlgRc; // +0x57C4
    char _gap_57C8[12]; // +0x57C8
    UIStatic m_TalkFrame; // +0x57D4
    char _gap_57D8[156]; // +0x57D8
    UIStatic m_Ready; // +0x5874
    char _gap_5878[156]; // +0x5878
    tagRECT m_ReadyRc; // +0x5914
    char _gap_5918[12]; // +0x5918
    UIStatic m_ListFrame; // +0x5924
    char _gap_5928[156]; // +0x5928
    UIStatic m_ListGrid[14]; // +0x59C4
    char _gap_59FC[2184]; // +0x59FC
    UIStatic m_ScrollHB; // +0x6284
    char _gap_6288[156]; // +0x6288
    UIStatic m_EquipFlag; // +0x6324
    char _gap_6328[156]; // +0x6328
    UIStatic m_ListPropTitle; // +0x63C4
    char _gap_63C8[156]; // +0x63C8
    tagRECT m_ListPropTitleRc; // +0x6464
    char _gap_6468[12]; // +0x6468
    UIListBox ml_ListProp; // +0x6474
    char _gap_6478[1284]; // +0x6478
    tagRECT ml_ListPropRc; // +0x697C
    char _gap_6980[12]; // +0x6980
    BtnGroup m_btnGroup; // +0x698C
    char _gap_6990[736]; // +0x6990
    float m_ctrlTime; // +0x6C70
    BYTE m_bCanUpdate1; // +0x6C74
    BYTE m_bCanUpdate2; // +0x6C75
    char _gap_6C76[2]; // +0x6C76
    UIStatic m_PropRemarkBk; // +0x6C78
    char _gap_6C7C[156]; // +0x6C7C
    UIStatic m_PropRemark; // +0x6D18
    char _gap_6D1C[156]; // +0x6D1C
    UIStatic m_PropAtt; // +0x6DB8
    char _gap_6DBC[156]; // +0x6DBC
    UIStatic m_MoneyRemark; // +0x6E58
    char _gap_6E5C[156]; // +0x6E5C
    tagRECT m_MoneyRc; // +0x6EF8
    char _gap_6EFC[12]; // +0x6EFC
    UIStatic m_SumProp; // +0x6F08
    char _gap_6F0C[156]; // +0x6F0C
    tagRECT m_SumRc; // +0x6FA8
    char _gap_6FAC[12]; // +0x6FAC
    UIButton mb_OK; // +0x6FB8
    char _gap_6FBC[340]; // +0x6FBC
    tagRECT mb_OKRc; // +0x7110
    char _tail_7114[108]; // +0x7114
    // total size: 0x7180 (29056)

    virtual ~PropUI() {}

    virtual int HandleInput(int nVal, int nVal2); // 0x0046F620
    virtual int InitListUI(int arg0, int nVal, unsigned int dwVal); // 0x0046F650
    static int GetFaceNum(); // 0x00452580
    void Init(); // 0x00452670
    int ShowCategory0(unsigned __int8 pData); // 0x0045B200
    int ShowCategory1(unsigned __int8 pData); // 0x0045B320
    int ShowCategory2(unsigned __int8 pData); // 0x0045B440
    int ShowCategory3(unsigned __int8 pData); // 0x0045B560
    int ShowCategory4(unsigned __int8 pData); // 0x0045B680
    int InitUI(); // 0x0046D140
    void ctor(); // 0x0046D4E0
    int UpdateItemList(const void *arg0); // 0x0046DD10
    int InitPlayerList(int nVal); // 0x0046DF40
    int SetSlotLock(int nVal); // 0x0046EC30
    bool CheckMode(unsigned int dwVal); // 0x0046EC50
    int SetSceneStates(unsigned __int8 pData); // 0x0046EC70
    int DisplayItemInfo(); // 0x0046ECC0
    int UpdateCaptions(); // 0x0046F160
    void UpdateItemDetail(int nItemIdx); // 0x0046F300
    int SetPendingMessage(char msg, int wparam, int lparam); // 0x00521A50
};

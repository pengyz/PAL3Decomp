#include "UIFrameWnd.h"
#pragma once
// Auto-generated: MagicUI

#include "DLG_MSG.h"
#include "MUIDialog.h"
#include "SkillData.h"
#include "UIAnimate.h"
#include "UIButton.h"
#include "UIFlexBar.h"
#include "UIListBox.h"
#include "UIParticle.h"
#include "UIStatic.h"
#include "m_RoleState.h"

class StateUI;

class MagicUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    _BYTE m_ComSkill[8][5]; // +0x48
    char _gap_070[168]; // +0x70
    char remarkbuf[256]; // +0x118
    int s_x; // +0x218
    BYTE m_IsMsg; // +0x21C
    _BYTE m_Is[5]; // +0x21D
    char _gap_222[2]; // +0x222
    int m_CtrlRole; // +0x224
    BYTE m_IsActive; // +0x228
    BYTE m_IsCreateable; // +0x229
    char _gap_22A[2]; // +0x22A
    int curPage; // +0x22C
    int m_SelNum; // +0x230
    int m_CurType; // +0x234
    int m_usemagicRole; // +0x238
    BYTE m_isuseMagic; // +0x23C
    BYTE m_LockUse; // +0x23D
    BYTE m_IsUsed; // +0x23E
    BYTE m_IsCanUse; // +0x23F
    BYTE m_IsAllUse; // +0x240
    char _gap_241[3]; // +0x241
    tagPOINT pt; // +0x244
    char _gap_248[4]; // +0x248
    SkillData m_RoleSkill[7][5]; // +0x24C
    char _gap_2D8[41580]; // +0x2D8
    StateUI * pStateUI; // +0xA544
    UIStatic m_Frame; // +0xA548
    char _gap_A54C[148]; // +0xA54C
    UIStatic m_TimeMoney; // +0xA5E0
    char _gap_A5E4[148]; // +0xA5E4
    UIStatic m_OutFrameT; // +0xA678
    char _gap_A67C[148]; // +0xA67C
    UIStatic m_OutFrameR; // +0xA710
    char _gap_A714[148]; // +0xA714
    UIStatic m_OutFrameL; // +0xA7A8
    char _gap_A7AC[148]; // +0xA7AC
    UIStatic m_OutFrameB; // +0xA840
    char _gap_A844[148]; // +0xA844
    UIStatic stp_BarL; // +0xA8D8
    char _gap_A8DC[148]; // +0xA8DC
    UIFlexBar stp_BarM; // +0xA970
    char _gap_A974[80]; // +0xA974
    UIStatic stp_BarR; // +0xA9C4
    char _gap_A9C8[148]; // +0xA9C8
    UIButton stp_State; // +0xAA5C
    char _gap_AA60[340]; // +0xAA60
    UIButton stp_Magic; // +0xABB4
    char _gap_ABB8[340]; // +0xABB8
    UIButton stp_Equip; // +0xAD0C
    char _gap_AD10[340]; // +0xAD10
    UIButton stp_Prop; // +0xAE64
    char _gap_AE68[340]; // +0xAE68
    UIButton stp_BattleArray; // +0xAFBC
    char _gap_AFC0[340]; // +0xAFC0
    UIButton stp_TaskBook; // +0xB114
    char _gap_B118[340]; // +0xB118
    UIButton stp_System; // +0xB26C
    char _gap_B270[340]; // +0xB270
    UIButton stp_Exit; // +0xB3C4
    char _gap_B3C8[340]; // +0xB3C8
    UIStatic stp_Effect; // +0xB51C
    char _gap_B520[148]; // +0xB520
    tagRECT stp_Rect; // +0xB5B4
    char _gap_B5B8[12]; // +0xB5B8
    tagRECT titleRc; // +0xB5C4
    char _gap_B5C8[12]; // +0xB5C8
    UIStatic m_title[4]; // +0xB5D4
    char _gap_B5E4[592]; // +0xB5E4
    UIStatic m_GameTime; // +0xB834
    char _gap_B838[148]; // +0xB838
    UIStatic m_GameMoney; // +0xB8CC
    char _gap_B8D0[148]; // +0xB8D0
    MUIDialog m_DlgEx; // +0xB964
    char _gap_B968[1380]; // +0xB968
    UIParticle m_btnPar[16][7]; // +0xBECC
    char _gap_C08C[65856]; // +0xC08C
    UIParticle m_btnPar2[16][7]; // +0x1C1CC
    char _gap_1C38C[65856]; // +0x1C38C
    tagRECT m_btnParRc[7]; // +0x2C4CC
    char _gap_2C4E8[84]; // +0x2C4E8
    _BYTE _isParBtn[7]; // +0x2C53C
    char _gap_2C543[1]; // +0x2C543
    int _curParEffect; // +0x2C544
    int m_CurSelRole; // +0x2C548
    int m_CurNeedRole; // +0x2C54C
    MUIDialog m_Dlg; // +0x2C550
    char _gap_2C554[1380]; // +0x2C554
    MUIDialog m_Msg; // +0x2CAB8
    char _gap_2CABC[1380]; // +0x2CABC
    DLG_MSG m_DlgMsg; // +0x2D020
    UIAnimate m_Animate[5]; // +0x2D024
    char _gap_2D038[240]; // +0x2D038
    tagRECT m_AnimateRc[5]; // +0x2D128
    char _gap_2D13C[60]; // +0x2D13C
    UIStatic m_ListFrame; // +0x2D178
    char _gap_2D17C[148]; // +0x2D17C
    UIStatic m_ListGrid[8]; // +0x2D210
    char _gap_2D230[1184]; // +0x2D230
    UIStatic m_RemarkBk; // +0x2D6D0
    char _gap_2D6D4[148]; // +0x2D6D4
    UIStatic m_Remark; // +0x2D768
    char _gap_2D76C[148]; // +0x2D76C
    UIStatic m_RemarkVal; // +0x2D800
    char _gap_2D804[148]; // +0x2D804
    UIStatic m_UnCom; // +0x2D898
    char _gap_2D89C[148]; // +0x2D89C
    m_RoleState m_Role[5]; // +0x2D930
    char _gap_2D944[21440]; // +0x2D944
    UIButton m_Ctrlbtn[7]; // +0x32D04
    char _gap_32D20[2380]; // +0x32D20
    UIListBox ml_SpeList; // +0x3366C
    char _gap_33670[1284]; // +0x33670
    UIListBox ml_FengList; // +0x33B74
    char _gap_33B78[1284]; // +0x33B78
    UIListBox ml_LeiList; // +0x3407C
    char _gap_34080[1284]; // +0x34080
    UIListBox ml_ShuiList; // +0x34584
    char _gap_34588[1284]; // +0x34588
    UIListBox ml_HuoList; // +0x34A8C
    char _gap_34A90[1284]; // +0x34A90
    UIListBox ml_TuList; // +0x34F94
    char _gap_34F98[1284]; // +0x34F98
    UIListBox ml_SuangList; // +0x3549C
    char _gap_354A0[1284]; // +0x354A0
    UIStatic m_TopFrame; // +0x359A4
    char _gap_359A8[148]; // +0x359A8
    UIStatic m_TopFrameXS; // +0x35A3C
    char _gap_35A40[148]; // +0x35A40
    UIParticle m_parRainbow[8][5]; // +0x35AD4
    char _gap_35B74[23520]; // +0x35B74
    UIParticle m_parRise[8][5]; // +0x3B754
    char _gap_3B7F4[23520]; // +0x3B7F4
    tagRECT m_parRc[5]; // +0x413D4
    char _tail_413E8[60]; // +0x413E8
    // total size: 0x41424 (267300)

    int SelectTab3(unsigned __int8 nTab); // 0x00484ED0
    int SelectTab4(unsigned __int8 nTab); // 0x00484EF0
    int RefreshAndLayout(); // 0x0048A010
    int SelectSubTab3(unsigned __int8 nTab); // 0x0048A350
    int SelectSubTab4(unsigned __int8 nTab); // 0x0048A370
    int InitUILayout(); // 0x0048A390
    int UpdateViewListItems(); // 0x0048B8F0
    int SelectBigMapTab3(char nTab); // 0x00494620
    int SelectBigMapTab4(char nTab); // 0x00494640
    void ProcessInput(); // 0x00494660
    int SelectXJTMTab3(unsigned __int8 nTab); // 0x0049E8A0
    int SelectXJTMTab4(unsigned __int8 nTab); // 0x0049E8C0
    int SetSelectedData(); // 0x004A4AC0
    void Init(); // 0x004A4B70
    static void InitComItem(); // 0x00551C66
    static int NextRole(int *); // 0x0055CCE4
};

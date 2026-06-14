#include "UIFrameWnd.h"
#pragma once
// Auto-generated: SystemUI

#include "MUIDialog.h"
#include "NOTE_STATE.h"
#include "Note_Item.h"
#include "UIButton.h"
#include "UIDragBar.h"
#include "UIFlexBar.h"
#include "UIParticle.h"
#include "UIPushButton.h"
#include "UIScrollBar.h"
#include "UIStatic.h"

class StateUI;
class UIWnd;

class SystemUI : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    tagRECT rc; // +0x48
    char _gap_04C[12]; // +0x4C
    int bkWndX; // +0x58
    int bkWndY; // +0x5C
    int i; // +0x60
    int j; // +0x64
    char buf[68]; // +0x68
    int _field_0AC; // +0xAC
    int _field_0B0; // +0xB0
    void * _field_0B4; // +0xB4
    char _gap_0B8[176]; // +0xB8
    BYTE m_IsMsg; // +0x168
    char _gap_169[3]; // +0x169
    StateUI * pStateUI; // +0x16C
    UIStatic m_Frame; // +0x170
    char _gap_174[156]; // +0x174
    UIStatic m_TimeMoney; // +0x210
    char _gap_214[156]; // +0x214
    UIStatic m_OutFrameT; // +0x2B0
    char _gap_2B4[156]; // +0x2B4
    UIStatic m_OutFrameR; // +0x350
    char _gap_354[156]; // +0x354
    UIStatic m_OutFrameL; // +0x3F0
    char _gap_3F4[156]; // +0x3F4
    UIStatic m_OutFrameB; // +0x490
    char _gap_494[156]; // +0x494
    UIStatic stp_BarL; // +0x530
    char _gap_534[156]; // +0x534
    UIFlexBar stp_BarM; // +0x5D0
    char _gap_5D4[80]; // +0x5D4
    UIStatic stp_BarR; // +0x624
    char _gap_628[156]; // +0x628
    UIButton stp_State; // +0x6C4
    char _gap_6C8[340]; // +0x6C8
    UIButton stp_Magic; // +0x81C
    char _gap_820[340]; // +0x820
    UIButton stp_Equip; // +0x974
    char _gap_978[340]; // +0x978
    UIButton stp_Prop; // +0xACC
    char _gap_AD0[340]; // +0xAD0
    UIButton stp_BattleArray; // +0xC24
    char _gap_C28[340]; // +0xC28
    UIButton stp_TaskBook; // +0xD7C
    char _gap_D80[340]; // +0xD80
    UIButton stp_System; // +0xED4
    char _gap_ED8[340]; // +0xED8
    UIButton stp_Exit; // +0x102C
    char _gap_1030[340]; // +0x1030
    UIStatic stp_Effect; // +0x1184
    char _gap_1188[156]; // +0x1188
    tagRECT stp_Rect; // +0x1224
    char _gap_1228[12]; // +0x1228
    UIStatic m_GameTime; // +0x1234
    char _gap_1238[156]; // +0x1238
    UIStatic m_GameMoney; // +0x12D4
    char _gap_12D8[156]; // +0x12D8
    UIParticle m_par[16][7]; // +0x1374
    char _gap_1534[65856]; // +0x1534
    UIParticle m_par2[16][7]; // +0x11674
    char _gap_11834[65856]; // +0x11834
    tagRECT m_parRc[7]; // +0x21974
    char _gap_21990[84]; // +0x21990
    _BYTE _isParBtn[7]; // +0x219E4
    char _gap_219EB[1]; // +0x219EB
    int _curParEffect; // +0x219EC
    UIStatic m_TopBar; // +0x219F0
    char _gap_219F4[156]; // +0x219F4
    UIStatic m_BottomBar; // +0x21A90
    char _gap_21A94[156]; // +0x21A94
    UIButton m_ExitGame; // +0x21B30
    char _gap_21B34[340]; // +0x21B34
    UIButton m_SaveBtn; // +0x21C88
    char _gap_21C8C[340]; // +0x21C8C
    UIButton m_LoadBtn; // +0x21DE0
    char _gap_21DE4[340]; // +0x21DE4
    UIButton m_DeleteBtn; // +0x21F38
    char _gap_21F3C[340]; // +0x21F3C
    UIPushButton m_pbPage[10]; // +0x22090
    char _gap_220B8[2480]; // +0x220B8
    _BYTE m_isItemShow[99]; // +0x22A68
    char _gap_22ACB[1]; // +0x22ACB
    Note_Item m_NoteItem[99]; // +0x22ACC
    char _gap_22C58[368676]; // +0x22C58
    UIScrollBar m_Scroll; // +0x7CC7C
    char _gap_7CC80[364]; // +0x7CC80
    int m_CurScrollPos; // +0x7CDEC
    UIStatic m_BackBar; // +0x7CDF0
    char _gap_7CDF4[156]; // +0x7CDF4
    UIStatic m_BackBar2; // +0x7CE90
    char _gap_7CE94[156]; // +0x7CE94
    UIDragBar m_MusicBar; // +0x7CF30
    char _gap_7CF34[268]; // +0x7CF34
    UIDragBar m_MusicEffectBar; // +0x7D040
    char _gap_7D044[268]; // +0x7D044
    UIStatic m_MusicText; // +0x7D150
    char _gap_7D154[156]; // +0x7D154
    UIStatic m_MusicEffectText; // +0x7D1F0
    char _gap_7D1F4[156]; // +0x7D1F4
    int m_ItemH; // +0x7D290
    int m_ItemW; // +0x7D294
    int m_firstItem; // +0x7D298
    int m_selItem; // +0x7D29C
    int m_getNote; // +0x7D2A0
    NOTE_STATE m_noteState; // +0x7D2A4
    int m_loading; // +0x7D2A8
    float m_passtime; // +0x7D2AC
    BYTE m_isExit; // +0x7D2B0
    char _gap_7D2B1[3]; // +0x7D2B1
    MUIDialog m_MsgBox; // +0x7D2B4
    char _tail_7D2B8[3940]; // +0x7D2B8
    // total size: 0x7E21C (516636)

    virtual ~SystemUI() {}

    virtual void ProcessFrame(); // 0x004AD140
    virtual BOOL UpdateSwordDisplay(int nVal, int nVal2); // 0x004AD540
    virtual int InitScreenUI(int nVal, UIWnd *pWnd, int nVal2, char *pszBuf, int nVal3); // 0x004ADC30
    void Reset(); // 0x0041F6F0
    void Close(); // 0x0041F800
    int Render(int nVal); // 0x004200A0
    int RenderWithStack(void *pStack); // 0x00420110
    double UIUpdate(double result, double pData); // 0x00420150
    int GetNoteItemData(int *item); // 0x00421A40
    void _SystemUI(); // 0x004A7690
    int LayoutWidgets(); // 0x004A7C40
    int ShowPage(); // 0x004A8150
    char CreateNoteEntry(int nVal, int nVal2, int nVal3, char pData, int nVal4, int nVal5, unsigned __int8 a8); // 0x004A8260
    void ReplaceTextures(); // 0x004AC8B0
    int InitSlotEffects(int nVal); // 0x004ACC10
    int UpdateNoteScroll(); // 0x004ACDE0
    int UpdateNoteScrollAlt(); // 0x004ACF90
    int UpdateParticles(); // 0x0051F130
};

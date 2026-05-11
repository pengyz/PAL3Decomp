#pragma once
// Auto-generated: MUIDialog

#include "DLG_MSG.h"
#include "DLG_TYPE.h"
#include "UIButton.h"
#include "UIDialog.h"
#include "UIStatic.h"
#include "UIStaticFlex.h"
#include "_TimeMgr.h"

class MUIDialogMgr;
class UIWnd;

class MUIDialog : public UIDialog, public MUIDialogMgr {
public:
    UIWnd * ptr_Dlg; // +0x48
    UINT m_DlgId; // +0x4C
    tagRECT m_rect; // +0x50
    tagRECT m_textRc; // +0x60
    UIStaticFlex m_bk; // +0x70
    UIStatic m_static; // +0x130
    UIStatic m_text; // +0x1D0
    int m_btnW; // +0x270
    int m_btnH; // +0x274
    tagRECT m_btRc; // +0x278
    UIButton mb_Yes; // +0x288
    UIButton mb_No; // +0x3E0
    int Lacune; // +0x538
    DLG_TYPE m_type; // +0x53C
    DLG_MSG m_getMsg; // +0x540
    int dft_W; // +0x544
    int dft_H; // +0x548
    BYTE m_IsModel; // +0x54C
    BYTE m_isDoModel; // +0x54D
    int m_xOffset; // +0x550
    int m_yOffset; // +0x554
    _TimeMgr _m_timeMgr; // +0x558
    BYTE _m_canEndDlg; // +0x564
    BYTE _haveSound; // +0x565
    // total size: 0x568 (1384)

};

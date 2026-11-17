class UIWnd;
#ifdef CreateDialog
#undef CreateDialog
#endif

#ifdef CreateDialog
#undef CreateDialog
#endif


class tagRECT;

class CCBUI;

#pragma once
// Auto-generated: UIRoleSelectDialog
#include "pal3/ida_types.h"

#include "Misc/UIAnimateCtrl.h"
#include "UI/UIDialog.h"
#include "UI/UIListBox.h"
#include "Misc/UIStaticFlex.h"
#include "Misc/UIStaticFlip.h"
#include "Misc/UITextArea.h"

class CCBUI;

class UIRoleSelectDialog : public UIDialog {
public:
    int m_state; // +0x48
    UIStaticFlex m_bk; // +0x4C
    UIAnimateCtrl m_ani; // +0x10C
    UIStaticFlip m_face; // +0x1B0
    char _gap_24C[8]; // +0x24C
    UITextArea m_static; // +0x254
    int m_texth; // +0x314
    UIListBox m_list; // +0x318
    char _gap_360[1216]; // +0x360
    int m_maxlen; // +0x820
    float m_last; // +0x824
    int m_sel; // +0x828
    int m_mode; // +0x82C
    char _tail_830[196]; // +0x830
    // total size: 0x8F4 (2292)

    virtual void ShowClipped(int nVal); // slot0 0x00445e70
    virtual void Render(); // slot1 0x00529cf0
    virtual BOOL Update(CCBUI **deltatime); // slot2 0x00529e40
    virtual void HideAll(); // slot3 0x0043de40
    virtual int Create(int id, tagRECT *, UIWnd * parent); // slot4 0x00445b90
    virtual ~UIRoleSelectDialog();
    virtual int OnMessage(int a2, unsigned int nVal, int nVal2); // slot6 0x0052aab0

    int (CreateDialog)(int id, void *pRect, int parent, char *tex); // 0x00451980
    UIRoleSelectDialog(); // 0x005295f0
    int SubtractFromStats(); // 0x0052aa50
    void DestroyStatics(); // 0x0052bbd0
    void CreateDialog(int, void *pRect, int, char *tex); // [G1b] 0x00451980

    void DestroyFrames(); // 0x0052bc90
    char IsRoleSelectable(int nVal); // 0x0052d200
};

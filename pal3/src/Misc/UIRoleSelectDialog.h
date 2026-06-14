#include "UIDialog.h"
#ifdef CreateDialog
#undef CreateDialog
#endif

#pragma once
// Auto-generated: UIRoleSelectDialog

#include "UIAnimateCtrl.h"
#include "UIListBox.h"
#include "UIStaticFlex.h"
#include "UIStaticFlip.h"
#include "UITextArea.h"

class UIRoleSelectDialog : public UIDialog {
public:
    char _gap_000[72]; // +0x0
    int m_state; // +0x48
    UIStaticFlex m_bk; // +0x4C
    char _gap_050[188]; // +0x50
    UIAnimateCtrl m_ani; // +0x10C
    char _gap_110[160]; // +0x110
    UIStaticFlip m_face; // +0x1B0
    char _gap_1B4[160]; // +0x1B4
    UITextArea m_static; // +0x254
    char _gap_258[100]; // +0x258
    int m_texth; // +0x2BC
    UIListBox m_list; // +0x2C0
    char _gap_2C4[1284]; // +0x2C4
    int m_maxlen; // +0x7C8
    float m_last; // +0x7CC
    int m_sel; // +0x7D0
    int m_mode; // +0x7D4
    char _tail_7D8[108]; // +0x7D8
    // total size: 0x844 (2116)

    virtual ~UIRoleSelectDialog() {}

    virtual void Render(); // 0x00529CF0
    virtual double HandleInput(double st6_0, double result, int arg0, int arg0a); // 0x00529E40
    virtual int ProcessDialog(); // 0x0052AAB0
    int (CreateDialog)(int id, void *pRect, int parent, char *tex); // 0x00451980
    int ctor_95F0(); // 0x005295F0
    void ctor(); // 0x00529790
    int SubtractFromStats(); // 0x0052AA50
    void DestroyStatics(); // 0x0052BBD0
    void DestroyFrames(); // 0x0052BC90
    char IsRoleSelectable(int nVal); // 0x0052D200
};

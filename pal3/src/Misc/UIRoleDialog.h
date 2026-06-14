#include "PalScriptWaitObj.h"
#include "UIDialog.h"
#pragma once
// Auto-generated: UIRoleDialog

#include "UIAnimateCtrl.h"
#include "UIStaticFlex.h"
#include "UIStaticFlip.h"
#include "UITextArea.h"

class UIRoleDialog : public UIDialog, public PalScriptWaitObj {
public:
    char _gap_000[80]; // +0x0
    UIStaticFlex m_bk; // +0x50
    char _gap_054[188]; // +0x54
    UIAnimateCtrl m_ani; // +0x110
    char _gap_114[160]; // +0x114
    UIStaticFlip m_face; // +0x1B4
    char _gap_1B8[152]; // +0x1B8
    UITextArea m_static; // +0x250
    char _gap_254[100]; // +0x254
    char timeclose[24]; // +0x2B8
    // total size: 0x2D0 (720)

    virtual ~UIRoleDialog() {}

    virtual void * RemoveChild(void *pChild, char bDelete); // 0x004A1A80
    virtual BOOL ProcessFrame(int nVal, int nVal2); // 0x004A1AA0
    virtual void HideAll(); // 0x004A14C0
    virtual int OnCommand(int nVal, int nVal2, int nVal3); // 0x004A1D10
    void _UIRoleDialog(); // 0x004A1410
    void _UIWnd(); // 0x004BEF50
    virtual void Create(int nVal); // 0x004BF1C0
    virtual int Destroy(int nVal); // 0x004BF1D0
    virtual void Render(int nVal); // 0x004BF260
};

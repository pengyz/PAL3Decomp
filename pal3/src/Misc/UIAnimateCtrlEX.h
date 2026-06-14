#include "UIAnimateCtrl.h"
#pragma once
// Auto-generated: UIAnimateCtrlEX

#include "CCBResultWindow.h"
#include "UIStatic.h"
#include "UITextArea.h"
#include "UIWnd.h"

class UIAnimateCtrlEX : public UIAnimateCtrl {
public:
    char _gap_000[412]; // +0x0
    UIStatic m_Frame; // +0x19C
    char _gap_1A0[148]; // +0x1A0
    CCBResultWindow m_ResultWnd; // +0x234
    char _gap_238[180]; // +0x238
    UITextArea m_TextArea; // +0x2EC
    char _gap_2F0[188]; // +0x2F0
    UIWnd m_ChildWnd; // +0x3AC
    char _gap_3B0[64]; // +0x3B0
    BYTE m_bAnimFlag; // +0x3F0
    char _tail_3F1[3]; // +0x3F1
    // total size: 0x3F4 (1012)

    virtual void Render(); // 0x00452AA0
    virtual BOOL ComputeStatBonus(int nVal, int nVal2); // 0x00452D30
    virtual int OnNotify(int msg, int wparam, int lparam); // 0x00452DA0
    int StepAnimation(); // 0x00441D50
    int NextFrame(); // 0x00441DC0
    UIAnimateCtrlEX(); // 0x00452790
    ~UIAnimateCtrlEX(); // 0x00452850
    int SetTextBottom(int nVal); // 0x00530990
    int SwapBuffer(int nNewBuf); // 0x00530BE0
    int InitMatrix(); // 0x00535A70
    int NormalizeVector(int nVal, int nVal2, int nVal3, int nVal4); // 0x00535E70
};

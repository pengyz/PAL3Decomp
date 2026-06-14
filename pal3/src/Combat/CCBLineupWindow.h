#include "UIFrameWnd.h"
#pragma once
// Auto-generated: CCBLineupWindow

class CCBControlWindow;
class CCBItemWindow;
class CCBMagicWindow;
class CCBProtectWindow;
class CCBUI;
class UIStatic;
class UIWnd;

class CCBLineupWindow : public UIFrameWnd {
public:
    char _gap_000[72]; // +0x0
    int m_nInitRoleFaceLineup[5]; // +0x48
    UIStatic * m_pBack; // +0x5C
    UIStatic * m_pFace[5]; // +0x60
    char _gap_064[16]; // +0x64
    int m_nSelected; // +0x74
    CCBUI * m_pUI; // +0x78
    // total size: 0x7C (124)

    virtual ~CCBLineupWindow() {}

    CCBLineupWindow(CCBControlWindow **a2); // 0x0051CFB0
    void _CCBLineupWindow(CCBItemWindow **a2); // 0x0051D070
    void Reset(CCBMagicWindow **a2); // 0x0051D120
    char Create(struct tagRECT *a2, int a3); // 0x0051D1D0
    void Destroy(); // 0x0051D290
    char OnMessage(int *msg); // 0x0051D340
    char Update(int *deltatime); // 0x0051D3F0
    char Render(int *p_DWORD); // 0x0051D4A0
    int IsPtOnFace(); // 0x0051D580
    int IsPtOnFace_d590(); // 0x0051D590
    void IsPtOnInitPos(); // 0x0051D5A0
    void IsPtOnInitPos_d5b0(); // 0x0051D5B0
    char IsFaceOnInitPos(); // 0x0051D5F0
    static char SetFaceLineup(int nVal, int nFaceIndex, int nPosIndex, int nVal2, int nVal3, int nVal4, int nVal5, int nVal6, int *p_DWORD); // 0x0051D610
    CCBProtectWindow * RefreshFacePos(); // 0x0051D6D0
};

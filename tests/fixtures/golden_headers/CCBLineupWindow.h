class tagRECT;

class CCBUI;

class UIWnd;

class gbVFileSystem;

#pragma once
// Auto-generated: CCBLineupWindow
#include "pal3/ida_types.h"

#include "Misc/UIFrameWnd.h"

class CCBControlWindow;
class CCBItemWindow;
class CCBMagicWindow;
class CCBProtectWindow;
class CCBUI;
class UIStatic;
class UIWnd;

class CCBLineupWindow : public UIFrameWnd {
public:
    int m_nInitRoleFaceLineup[5]; // +0x48
    UIStatic * m_pBack; // +0x5C
    UIStatic * m_pFace[5]; // +0x60
    int m_nSelected; // +0x74
    CCBUI * m_pUI; // +0x78
    // total size: 0x7C (124)

    virtual ~CCBLineupWindow() {}

    virtual void Render(); // slot1 0x0043ddf0
    virtual BOOL Update(CCBUI **deltatime); // slot2 0x0051b570
    virtual void HideAll(); // slot3 0x0051b4b0
    virtual int Create(int id, tagRECT *, UIWnd * parent); // slot4 0x00445b90
    virtual int OnMessage(int a2, unsigned int nVal, int nVal2); // slot6 0x0051c9b0

    CCBLineupWindow(CCBControlWindow **a2); // 0x0051cfb0
    void UpdateItems(CCBItemWindow **a2); // 0x0051d070
    void Reset(CCBMagicWindow **a2); // 0x0051d120
    void DestroyUI(); // 0x0051d290
    char OnMessage_d340(int *msg); // 0x0051d340
    char Update_d3f0(int *deltatime); // 0x0051d3f0
    int IsPtOnFace(); // 0x0051d580
    int Method(); // 0x0051d590
    void IsPtOnInitPos(); // 0x0051d5a0
    void Initialize(); // 0x0051d5b0
    char IsFaceOnInitPos(); // 0x0051d5f0
    static char SetFaceLineup(int nVal, int nFaceIndex, int nPosIndex, int nVal2, int nVal3, int nVal4, int nVal5, int nVal6, int *p_DWORD); // 0x0051d610
    CCBProtectWindow * RefreshFacePos(); // 0x0051d6d0
};

#include "UIWnd.h"
#pragma once
// Auto-generated: UIListBox

#include "UILBColumn.h"
#include "UIScrollBar.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"

class CCBUI;
class UIWnd;
class _PlugInfo;

class UIListBox : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    gbColorQuad m_selcolor; // +0x44
    int m_showGrayBk; // +0x48
    BYTE m_hasKeyCtrl; // +0x4C
    char _gap_04D[3]; // +0x4D
    UIScrollBar m_scrollbar; // +0x50
    char _gap_054[348]; // +0x54
    int m_numcol; // +0x1B0
    UILBColumn m_column[8]; // +0x1B4
    char _gap_1D4[640]; // +0x1D4
    int m_itemheight; // +0x454
    int m_fontsize; // +0x458
    int m_firstshow; // +0x45C
    int m_onsel; // +0x460
    int m_locksel; // +0x464
    tagRECT m_scrollRc; // +0x468
    char _gap_46C[12]; // +0x46C
    gbTexture * m_pbkpic; // +0x478
    _PlugInfo * m_pbkpicInfo; // +0x47C
    gbTexture * m_selpic; // +0x480
    _PlugInfo * m_selpicInfo; // +0x484
    int m_seloffset; // +0x488
    int m_seloffsetL; // +0x48C
    int m_seloffsetR; // +0x490
    int m_scrollW; // +0x494
    gbColorQuad m_seltexcolor; // +0x498
    tagPOINT m_itemoffset; // +0x49C
    char _gap_4A0[4]; // +0x4A0
    int m_movesel; // +0x4A4
    char m_rowenable[16]; // +0x4A8
    // total size: 0x4B8 (1208)

    virtual ~UIListBox() {}

    virtual int Render_e8a0(); // 0x0043E8A0
    virtual BOOL Update(int nVal, int nVal2); // 0x0043EBE0
    virtual void Destroy_e520(); // 0x0043E520
    virtual int OnMessage(int height, int nVal, int nVal2); // 0x0043E480
    virtual void CalScrollBarRange(int id, int *p_DWORD, int parent, LPCSTR lpString, int nVal, char pData); // 0x0043E1C0
    virtual int ResizeToContent(int bResize); // 0x00451B40
    virtual int IsVisible(); // 0x00451C10
    virtual int RenderMagic(); // 0x004526F0
    virtual BOOL ShouldProcessInput(int nVal, int nVal2); // 0x004526C0
    virtual int RenderWithSceneMap(); // 0x00527D80
    virtual int ProcessInput(int nVal, int nVal2); // 0x00527DC0
    virtual int OnMessageEx(int nVal, int nVal2, int nVal3); // 0x00527EA0
    void RefreshSelection(); // 0x00431CD0
    int ReleaseVtable(); // 0x00432680
    UIListBox(); // 0x0043DCD0
    void _UIListBox(); // 0x0043DD10
    void SetSelTexture(int id, int pRect, int nVal, int nVal2, int nVal3, int nVal4); // 0x0043DD60
    void Destroy(); // 0x0043DE90
    void AddColumn(); // 0x0043DEA0
    void AddRow(); // 0x0043DEB0
    void SetSubItem(); // 0x0043DEC0
    UIListBox * GetSubItemInfo(); // 0x0043DED0
    void Render(); // 0x0043DEF0
    void CalHeightCount(); // 0x0043DF10
    void GetItemPos(); // 0x0043DF20
    void GetItemAt(); // 0x0043DF70
    UIListBox * UpdateKeyCtrl(); // 0x0043DFC0
    void DeleteRow(); // 0x0043E120
    void GetSel(int nVal, int nVal2); // 0x0043E330
    int GetLockSel(int nVal, int *p_DWORD, int nVal2, int nVal3, char pData); // 0x0043E3B0
    void SetSel(int sel); // 0x0043E440
    int SetFirstShow(int nVal, int nOffset); // 0x0043E560
    int SetItemOffset(char *Source, int y); // 0x0043E5C0
    gbVFileSystem * SetMouseMoveSel(int movesel, int nVal, char *Source, int nVal2); // 0x0043E7D0
    void SetDefaultSel(); // 0x0043EBA0
    int ProcessSelection(); // 0x0043F080
    int ClearAll(); // 0x0043F360
    int AdjustScroll(int nVal); // 0x0043F410
    int InitScrollbar(); // 0x0043F520
    int GetLockedSel(); // 0x0043F590
    int GetItem(); // 0x0043F5B0
    void SetLockSel(); // 0x0043F640
    int GetItemData(); // 0x0043F650
    int SetItemOffset(int nVal, int nVal2); // 0x0043F670
    int SetItemData(int nData); // 0x0043F690
    unsigned int SetChildParam(unsigned int dwVal, int nVal); // 0x0043F6A0
    int SetFirstShow(unsigned int dwVal); // 0x0043F6D0
    int GetCurSel(); // 0x0043FE90
    int UIListBox_Init(); // 0x00451850
    static void DestroyContent(UIWnd *pWnd); // 0x00451900
    int ReinitScrollbar(); // 0x00451AD0
    int CalcVisibleRange(char *Source, int nVal); // 0x00451AF0
    void ctor_2600(); // 0x00452600
    virtual int OnMessage(int nVal, char *pszBuf, int nVal2); // 0x0046B4B0
    int InitWithPalScript(int nVal, int nVal2); // 0x00470A60
    int GetSkillSlotLevel(int nVal, int nVal2); // 0x0049CF20
    int _todo_4A9870(); // 0x004A9870
    int ResetAllListBoxes(); // 0x004AA1B0
    int ShowSlotUI(); // 0x004AA230
    // [IDA_VTABLE] InsertUIListBox; // 0x004AA320
    void ProcessListInput(int a2); // 0x004AA680
    void Reset(); // 0x004B4690
    CCBUI * InitAndRender(); // 0x00519AF0
    int ctor(); // 0x00527950
    void ctor_79F0(); // 0x005279F0
    int * ResetRect(); // 0x00532A40
    void RefreshList(); // 0x0053D100
};

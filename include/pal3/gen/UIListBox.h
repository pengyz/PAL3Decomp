#pragma once
// Auto-generated: UIListBox

#include "UILBColumn.h"
#include "UIScrollBar.h"
#include "UIWnd.h"

class _PlugInfo;

class UIListBox : public UIWnd {
public:
    gbColorQuad m_selcolor; // +0x44
    int m_showGrayBk; // +0x48
    unsigned char m_hasKeyCtrl; // +0x4C
    UIScrollBar m_scrollbar; // +0x50
    int m_numcol; // +0x1C0
    UILBColumn m_column[8]; // +0x1C4
    int m_itemheight; // +0x4A4
    int m_fontsize; // +0x4A8
    int m_firstshow; // +0x4AC
    int m_onsel; // +0x4B0
    int m_locksel; // +0x4B4
    tagRECT m_scrollRc; // +0x4B8
    gbTexture * m_pbkpic; // +0x4C8
    _PlugInfo * m_pbkpicInfo; // +0x4CC
    gbTexture * m_selpic; // +0x4D0
    _PlugInfo * m_selpicInfo; // +0x4D4
    int m_seloffset; // +0x4D8
    int m_seloffsetL; // +0x4DC
    int m_seloffsetR; // +0x4E0
    int m_scrollW; // +0x4E4
    gbColorQuad m_seltexcolor; // +0x4E8
    tagPOINT m_itemoffset; // +0x4EC
    int m_movesel; // +0x4F4
    struct allocator<int> > {}; // nested type stub
    allocator<int> > m_rowenable; // +0x4F8
    // total size: 0x508 (1288)

    UIListBox(); // 0x0043DCD0
    ~UIListBox(); // 0x0043DCF0
    int SetSelTexture(int id, int pRect, int a4, int a5, int a6, int a7); // 0x0043DD60
    int SetScroll(); // 0x0043DDF0
    int SetScrollPos(); // 0x0043DE40
    static int Destroy(); // 0x0043DE90
    static int AddColumn(); // 0x0043DEA0
    static void AddRow(); // 0x0043DEB0
    static void SetSubItem(); // 0x0043DEC0
    void * GetSubItemInfo(); // 0x0043DED0
    int Render(); // 0x0043DEF0
    void CalHeightCount(); // 0x0043DF10
    void GetItemPos(); // 0x0043DF20
    char * UpdateKeyCtrl(); // 0x0043DFC0
    std::ios_base * DeleteAllItems(std::ios_base *Block, char a2); // 0x0043E100
    void DeleteRow(); // 0x0043E120
    int CalScrollBarRange(int id, _DWORD *a3, int parent, LPCSTR lpString, int a6, char a7); // 0x0043E1C0
    void GetSel(int a2, int a3); // 0x0043E330
    int GetLockSel(int a2, _DWORD *a3, int a4, int a5, char a6); // 0x0043E3B0
    int SetSel(int a2); // 0x0043E440
    int SetItemHeight(int a2, int a3, int a4); // 0x0043E480
    int GetItemCount(); // 0x0043E520
    int SetFirstShow(char *Source, int a3); // 0x0043E560
    int SetItemOffset(char *Source, int a3); // 0x0043E5C0
    struct gbVFileSystem * SetMouseMoveSel(int a2, int a3, char *Source, int a5); // 0x0043E7D0
    int EnableRow(); // 0x0043E8A0
    int SetDefaultSel(); // 0x0043EBA0
};

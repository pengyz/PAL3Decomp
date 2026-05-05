#ifndef PAL3A_UILISTBOX_H
#define PAL3A_UILISTBOX_H

#include "pal3a_types.h"

class UILBColumn {
public:
    char _data[64];

    void Destroy();
    ~UILBColumn();
    UILBColumn();
};

class UILBItem {
public:
    char _data[64];

    ~UILBItem();
    UILBItem();
};

class UIListBox {
public:
    char _data[1288];

    void SetItemOffset(int x, int y);
    void Destroy();
    void SetMouseMoveSel(int movesel);
    void SetSelTexture(char * selfile, uchar opt);
    void CalScrollBarRange();
    tagPOINT GetItemPos(tagPOINT * __$ReturnUdt);
    void UpdateKeyCtrl();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void SetScroll(char * srcfile, tagRECT * rect, int btnW, int btnH, uchar opt);
    ~UIListBox();
    void SetFirstShow(int first);
    int CalHeightCount();
    void Render();
    void DeleteAllItems();
    int GetLockSel();
    void SetItemHeight(int height);
    void AddColumn(char * head, int width, uchar rightalign, int rightoffset);
    UIListBox();
    int AddRow(char * str, int isicon);
    void SetSubItem(int col, int item, char * str, int bicon);
    int Update(float deltatime, int haveinput);
    void EnableRow(int row, int enable);
    char * GetSubItemInfo(int col, int item);
    int GetSel();
    void SetScrollPos(int pos);
    void SetDefaultSel(int start);
    int GetItemCount();
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * bkfile, int scroll, uchar opt, uchar bCalFrameRate);
    void DeleteRow(int row);
    void SetSel(int sel);
};

#endif // PAL3A_UILISTBOX_H

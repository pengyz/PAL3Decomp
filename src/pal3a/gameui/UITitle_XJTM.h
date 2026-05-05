#ifndef PAL3A_UITITLE_XJTM_H
#define PAL3A_UITITLE_XJTM_H

#include "pal3a_types.h"

class UITitle_XJTM {
public:
    char _data[5204];

    void Render();
    void Create(UIWnd * pWnd);
    int Update(float deltatime, int haveinput);
    void UpdateElementShow();
    ~UITitle_XJTM();
    UITitle_XJTM();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
};

class _Item_List_Info {
public:
    char _data[5888];

    ~_Item_List_Info();
    int Update(float deltatime, int haveinput);
    void ReSetItem(_Item * pItem);
    void UpdatePanelShow();
    void Create(uint id, tagRECT * rc, UIWnd * pWnd);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    _Item_List_Info();
    void Render();
};

#endif // PAL3A_UITITLE_XJTM_H

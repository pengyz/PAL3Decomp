#ifndef PAL3A_UIWND_H
#define PAL3A_UIWND_H

#include "pal3a_types.h"

class UITextureArray {
public:
    char _data[68];

    int Add(char * filepath, int mode);
    void FreeAll();
    ~UITextureArray();
    int SetTexAt(int index, char * filepath, int mode);
    gbTexture * GetAt(int index);
    UITextureArray();
    unsigned char GetPixelChannel(int index, int x, int y, int channel);
};

class UIWnd {
public:
    char _data[68];

    void Render();
    ~UIWnd();
    tagRECT GetWindowRect();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Destroy();
    void SetWndColor(ulong dwColor);
    void SetWndColor(gbColorQuad color);
    void ShowWindow(int show);
    void MoveWindowOffset(int offsetx, int offsety);
    void AddChild(UIWnd * pchild);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, uchar bCalFrameRate);
    void SetFontColor(gbColorQuad * color);
    void BringWindowToTop();
    void SetRect(tagRECT * rc);
    void CenterWindow(UIWnd * pwnd);
    void ClientToScreen(tagPOINT * pt);
    void ClientToScreen(tagRECT * rect);
    void ScreenToClient(tagPOINT * pt);
    void ScreenToClient(tagRECT * rect);
    int Update(float deltatime, int haveinput);
    void MoveWindow(int x, int y);
    void SetFrameRate();
    UIWnd();
    void EnableWindow(int enable);
};

#endif // PAL3A_UIWND_H

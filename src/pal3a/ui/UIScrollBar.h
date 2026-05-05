#ifndef PAL3A_UISCROLLBAR_H
#define PAL3A_UISCROLLBAR_H

#include "pal3a_types.h"

class UIScrollBar {
public:
    char _data[368];

    void SetBKRect(int top, int left, int right, int bottom);
    void SetBKRect(tagRECT * rect);
    int Update(float deltatime, int haveinput);
    ~UIScrollBar();
    void ShowBkBar(int show);
    void SetSliderTBOffset(int offset);
    void Destroy();
    void SetSliderOffset(int offset);
    void CalBtnRect();
    void SetSliderSize(int w, int h);
    float CalSliderPt();
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * picname, int bvscroll, uchar opt, uchar bCalFrameRate);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void ON_UPBTN();
    void SetBk(char * bkPic, uchar opt);
    int GetPtArea(tagPOINT * pt);
    void SetBKTileSize(int w, int h);
    void SetBtnRect(tagRECT * up, tagRECT * down);
    void ON_DWBTN();
    void Render();
    UIScrollBar();
    void SetPos(int p);
    void SetRange(int min, int max);
};

#endif // PAL3A_UISCROLLBAR_H

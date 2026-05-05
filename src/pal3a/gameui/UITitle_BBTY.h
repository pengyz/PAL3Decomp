#ifndef PAL3A_UITITLE_BBTY_H
#define PAL3A_UITITLE_BBTY_H

#include "pal3a_types.h"

class UITitle_BBTY {
public:
    char _data[5388];

    void ShowGameControl(uchar show);
    void AdjustApprNote();
    ~UITitle_BBTY();
    void ShowGameShow(uchar show);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void CheckItem();
    void Create(UIWnd * pWnd);
    int Update(float deltatime, int haveinput);
    UITitle_BBTY();
    void Render();
};

#endif // PAL3A_UITITLE_BBTY_H

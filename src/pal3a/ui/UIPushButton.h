#ifndef PAL3A_UIPUSHBUTTON_H
#define PAL3A_UIPUSHBUTTON_H

#include "pal3a_types.h"

class UIPushButton {
public:
    char _data[252];

    void SetDownPic(char * pic, uchar opt);
    void SetPopPic(char * pic, uchar opt);
    void Destroy();
    void SetBk(char * bkpic, uchar opt);
    void SetOnPic(char * pic, uchar opt);
    void SetCaption(char * txt);
    void SetFontColor(gbColorQuad * color);
    void SetDisablePic(char * picname, uchar opt);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * picname, uchar opt, uchar bCalFrameRate);
    ~UIPushButton();
    int Update(float deltatime, int haveinput);
    void Render();
    void SetFontType(gbFontType type);
    UIPushButton();
};

#endif // PAL3A_UIPUSHBUTTON_H

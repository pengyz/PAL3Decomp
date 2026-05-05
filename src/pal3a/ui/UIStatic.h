#ifndef PAL3A_UISTATIC_H
#define PAL3A_UISTATIC_H

#include "pal3a_types.h"

class UIStatic {
public:
    char _data[160];

    void SetBK2(char * bkpic);
    void SetDisablePic(char * bkpic, uchar opt);
    void SetPic(char * picfilename, uchar opt);
    int Update(float deltatime, int haveinput);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, uchar bCalFrameRate);
    void SetRichText(char * text, int bcenter);
    void SetTexOffset(int x, int y);
    void Render();
    ~UIStatic();
    void SetFont(gbFontType fonttype);
    void SetFont(int bBigFont);
    void SetBk(char * bkpic, uchar opt);
    void DeleteBK();
    void DeleteBK2();
    void Destroy();
    void SetText(char * text, int bcenter);
    void SetTextWidth(int w);
    UIStatic();
};

#endif // PAL3A_UISTATIC_H

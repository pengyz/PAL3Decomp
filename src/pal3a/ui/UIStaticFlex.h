#ifndef PAL3A_UISTATICFLEX_H
#define PAL3A_UISTATICFLEX_H

#include "pal3a_types.h"

class UIStaticFlex {
public:
    char _data[192];

    void SetText(char * str);
    void SetOpenStyle(int style);
    void SetFont(gbFontType fonttype);
    void Destroy();
    void ShowWindow(int show);
    void Render();
    void DrawRect(tagRECT * rc, int tileindex);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * picname, uchar bCalFrameRate);
    ~UIStaticFlex();
    int Update(float deltatime, int haveinput);
    UIStaticFlex();
};

#endif // PAL3A_UISTATICFLEX_H

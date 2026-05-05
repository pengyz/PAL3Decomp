#ifndef PAL3A_UIFLEXBAR_H
#define PAL3A_UIFLEXBAR_H

#include "pal3a_types.h"

class UIFlexBar {
public:
    char _data[84];

    void Render();
    ~UIFlexBar();
    UIFlexBar();
    void SetTileSize(int width, int height);
    void Destroy();
    void Create(uint id, tagRECT * rect, char * picname, int style, UIWnd * pfather);
    void DrawRect(tagRECT * rc, int tileindex);
};

#endif // PAL3A_UIFLEXBAR_H

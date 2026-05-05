#ifndef PAL3A_UITAB_H
#define PAL3A_UITAB_H

#include "pal3a_types.h"

class UITabCtrl {
public:
    char _data[148];

    void Destroy();
    ~UITabCtrl();
    void SetItemWidth(int width);
    void Render();
    int GetSel();
    int Update(float deltatime, int haveinput);
    void SetSel(int sel);
    UITabCtrl();
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * picname, int numpage);
};

#endif // PAL3A_UITAB_H

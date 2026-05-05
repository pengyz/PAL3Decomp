#ifndef PAL3A_UITABBTN_H
#define PAL3A_UITABBTN_H

#include "pal3a_types.h"

class UITabBtn {
public:
    char _data[24];

    void AddBtn(UIButton * btn, ulong btnID, UIWnd * pWnd);
    int UpdateKeyCtrl(int updw, int leftright);
    void SetBtnNULL(int index);
    void Init();
    UITabBtn();
    ~UITabBtn();
};

#endif // PAL3A_UITABBTN_H

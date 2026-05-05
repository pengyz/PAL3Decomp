#ifndef PAL3A_UITITLE_QCYM_H
#define PAL3A_UITITLE_QCYM_H

#include "pal3a_types.h"

class UITitle_QCYM {
public:
    char _data[18060];

    void SetQCYMItem(QCYM_TYPE type, int flag);
    void TestEle();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void CheckEleOn();
    ~UITitle_QCYM();
    void Render();
    void HideUI(uchar show);
    UITitle_QCYM();
    int Update(float deltatime, int haveinput);
    void Create(UIWnd * pWnd);
};

#endif // PAL3A_UITITLE_QCYM_H

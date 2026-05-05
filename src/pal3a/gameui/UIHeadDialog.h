#ifndef PAL3A_UIHEADDIALOG_H
#define PAL3A_UIHEADDIALOG_H

#include "pal3a_types.h"

class UIHeadDialog {
public:
    char _data[352];

    ~UIHeadDialog();
    void Destroy();
    int IsWaiting();
    void SetRole(Role * role);
    void SetText(char * text);
    int Update(float deltatime, int haveinput);
    void Create(uint id, int width, int height, UIWnd * pfather, char * bkfile);
    UIHeadDialog();
    void Render();
};

#endif // PAL3A_UIHEADDIALOG_H

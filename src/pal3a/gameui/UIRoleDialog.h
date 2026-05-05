#ifndef PAL3A_UIROLEDIALOG_H
#define PAL3A_UIROLEDIALOG_H

#include "pal3a_types.h"

class UIRoleDialog {
public:
    char _data[720];

    int Update(float deltatime, int haveinput);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * bkfile);
    void SetRect(tagRECT * rc);
    void DlgText(char * text, int mode);
    void Render();
    void SetFace(char * path, int leftright);
    void ShowWindow(int show);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Destroy();
    void SetFont(int bBigFont);
    int IsWaiting();
    int GetTimeSel();
    void GetIconRect(tagRECT * rc, uchar right);
    UIRoleDialog();
    ~UIRoleDialog();
};

#endif // PAL3A_UIROLEDIALOG_H

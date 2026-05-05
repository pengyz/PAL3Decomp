#ifndef PAL3A_MUIDIALOG_H
#define PAL3A_MUIDIALOG_H

#include "pal3a_types.h"

class MUIDialog {
public:
    char _data[1384];

    void SetDlgSize(int w, int h);
    DLG_MSG GetModelMsg();
    ~MUIDialog();
    void Render();
    void Destroy();
    MUIDialog();
    void EndDlg();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, DLG_TYPE type, uchar opt);
    void DoModel(uchar havesnd);
    void SetText(int color_r, int color_g, int color_b, int color_alpha);
    int Update(float deltatime, int haveinput);
};

#endif // PAL3A_MUIDIALOG_H

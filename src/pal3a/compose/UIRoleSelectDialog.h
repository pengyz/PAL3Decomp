#ifndef PAL3A_UIROLESELECTDIALOG_H
#define PAL3A_UIROLESELECTDIALOG_H

#include "pal3a_types.h"

class UIRoleSelectDialog {
public:
    char _data[2008];

    void DlgText(char * text);
    void AddString(char * str, int enable);
    void SetFace(char * path, int leftright);
    void Render();
    int Update(float deltatime, int haveinput);
    ~UIRoleSelectDialog();
    void Create(uint id, tagRECT * rect, UIWnd * pfather);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void GetIconRect(tagRECT * rc, uchar right);
    void Destroy();
    UIRoleSelectDialog();
    void Clear();
    void SetFont(int bBigFont);
};

#endif // PAL3A_UIROLESELECTDIALOG_H

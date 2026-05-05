#ifndef PAL3A_UIROLESELECT_H
#define PAL3A_UIROLESELECT_H

#include "pal3a_types.h"

class UIRoleSelect {
public:
    char _data[1568];

    void Render();
    void Clear();
    int Update(float deltatime, int haveinput);
    void Create(uint id, tagRECT * rect, UIWnd * pfather, char * bkfile);
    void AddString(char * str, int enable);
    int IsWaiting();
    void SetSel(int i);
    ~UIRoleSelect();
    UIRoleSelect();
    void ShowWindow(int show);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
};

#endif // PAL3A_UIROLESELECT_H

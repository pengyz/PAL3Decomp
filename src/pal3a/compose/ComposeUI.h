#ifndef PAL3A_COMPOSEUI_H
#define PAL3A_COMPOSEUI_H

#include "pal3a_types.h"

class ComposeUI {
public:
    char _data[4008];

    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void UpdateKeyCtrl();
    void SetTestData();
    ~ComposeUI();
    void Render();
    void ReadComposeData();
    int Update(float deltatime, int haveinput);
    ComposeUI();
    void SwitchUIRender(int flag);
    void RenderIntercept();
    void InterceptScene();
    void Create(int roleid);
};

#endif // PAL3A_COMPOSEUI_H

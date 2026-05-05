#ifndef PAL3A_COMP_DONATEUI_H
#define PAL3A_COMP_DONATEUI_H

#include "pal3a_types.h"

class Comp_DonateUI {
public:
    char _data[45992];

    void Render();
    void Clean();
    ~Comp_DonateUI();
    void UpdateKeyCtrl();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void SetTestData();
    void ChangeRole(int RoleId);
    void Create();
    Comp_DonateUI();
    int Update(float deltatime, int haveinput);
    void ReadComposeData();
    void TransString(int id, char * in, char * out);
    void BuildInfo();
    void BuildStaticBK(int id);
    void BuildState(int id);
};

class LineupComp {
public:
    char _data[2012];

    void Create();
    int Update(float deltatime, int haveinput);
    void Render();
    ~LineupComp();
    LineupComp();
};

#endif // PAL3A_COMP_DONATEUI_H

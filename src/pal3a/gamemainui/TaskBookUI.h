#ifndef PAL3A_TASKBOOKUI_H
#define PAL3A_TASKBOOKUI_H

#include "pal3a_types.h"

class TaskBookUI {
public:
    char _data[143912];

    void SetTaskVal();
    void Render();
    int Update(float deltatime, int haveinput);
    void WriteBackToReg();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    ~TaskBookUI();
    void Create(UIWnd * pWnd);
    void MgrStpCtrl();
    void SetBtnParEffect(int flag);
    void RefreshBtnCaption();
    void RefreshDesc();
    void SetTestData();
    void CreateStpCtl();
    TaskBookUI();
    void UpdateListBtn();
};

#endif // PAL3A_TASKBOOKUI_H

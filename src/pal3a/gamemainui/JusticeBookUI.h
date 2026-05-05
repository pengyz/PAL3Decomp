#ifndef PAL3A_JUSTICEBOOKUI_H
#define PAL3A_JUSTICEBOOKUI_H

#include "pal3a_types.h"

class JusticeBookUI {
public:
    char _data[11644];

    void PageDOWN();
    void Reset();
    int Update(float deltatime, int haveinput);
    void Set3DOBJParam(RoleAtt * pRole);
    void CloseBook();
    void CreateUIElement();
    void OpenBook();
    void ShowElement(uchar show);
    void DispElementBBB(float deltatime);
    ~JusticeBookUI();
    void DestroyMonsters();
    void SetBookMark(JB_TYPE type, JB_STATE state);
    void SetBookMark(JB_TYPE type);
    void DispatchInfo();
    void PageUP();
    void Create();
    void AdjustAllBookMark();
    void SetTestReoccupy();
    void UpdateKeyCtrl();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void ShowBookmarkGroup(uchar unopen);
    JusticeBookUI();
    void Render();
    void AdjustBookMark(JB_TYPE type, int mode);
    void SetPageInfo(JB_TYPE type);
    void AdjustBookMarkFrom(JB_TYPE type, int mode);
    void CtrlBookMarkFrom(JB_TYPE type, uchar show, int mode);
    void CtrlBookMark(JB_TYPE type, uchar show);
    void GetAllMonsters();
};

#endif // PAL3A_JUSTICEBOOKUI_H

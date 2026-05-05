#ifndef PAL3A_CG_UI_H
#define PAL3A_CG_UI_H

#include "pal3a_types.h"

class CG_UI {
public:
    char _data[39504];

    void UpdateComboBuffer(float deltatime);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Destroy();
    void ResumeBossHP(float deltatime);
    bool IsMouseOnControl();
    ~CG_UI();
    void UpdateResultUI(float deltatime);
    void SetSelectType(int nSelect);
    void RefreshMoney();
    void Init(int nLevel);
    void Render();
    void ShowResult(uchar bWin);
    bool IsMouseOnControlInEdit();
    void ChangeRoleHP(int nValue);
    void ConfigResultInfo();
    void SetSelectPropType(int nSelect);
    void ChangeBossHP(int nValue);
    void MakeBuyData();
    int Update(float deltatime, int haveinput);
    void UpdateTime(float deltatime);
    int GetBossHP();
    void ExitBuyUI();
    CG_UI(CG_Entry * pFather);
    void RenderComboBuffer();
    void UseProp(int seltype);
    void ShowWindow(int show);
    void ShowEditMode(uchar bShow);
    void ShowRunMode(uchar bShow);
    bool Create();
    int GetRoleHP();
};

#endif // PAL3A_CG_UI_H

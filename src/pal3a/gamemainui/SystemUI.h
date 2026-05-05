#ifndef PAL3A_SYSTEMUI_H
#define PAL3A_SYSTEMUI_H

#include "pal3a_types.h"

class SystemUI {
public:
    char _data[516852];

    void SeekNote();
    int UpdateNoteCtrl();
    void AdjustItem(int item, tagRECT rect);
    void AdjustNoteItem(NOTE_STATE state);
    void CreateStpCtl();
    void CreateNoteItem();
    void LoadAllNote();
    void CheckSelItem();
    void MgrStpCtrl();
    void Create(UIWnd * pWnd);
    int Update(float deltatime, int haveinput);
    void CheckItemShow();
    bool Move(int steps, uchar bmoveslide);
    void Render();
    int LoadNote(int item);
    ~SystemUI();
    void SetItemInfo();
    void SaveNote(int item);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    bool MoveDw(uchar bmoveslide);
    SystemUI();
    void UpdateKeyCtrl();
    void SetParEffect(int flag);
    void Reset(NOTE_STATE state);
    bool MoveUp(uchar bmoveslide);
    void UpdatePage();
    void UpdateSLD();
};

#endif // PAL3A_SYSTEMUI_H

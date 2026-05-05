#ifndef PAL3A_UITITLE_JDHY_H
#define PAL3A_UITITLE_JDHY_H

#include "pal3a_types.h"

class UITitle_JDHY {
public:
    char _data[377860];

    void UpdateKeyCtrl();
    void LoadArcNote(int item);
    ~UITitle_JDHY();
    void Reset();
    bool MoveUp(uchar bmoveslide);
    void UpdatePage();
    void LoadAllArcNote();
    void Initialize();
    bool MoveDw(uchar bmoveslide);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    bool Move(int steps, uchar bmoveslide);
    void CheckItemShow();
    int LoadNote(int item);
    int IfHasBrief(int index);
    void Render();
    void UpdateLD();
    UITitle_JDHY();
    void SeekNote();
    void AdjustNoteItem();
    void UpdateNoteCtrl();
    void AdjustItem(int item, tagRECT rect);
    void CheckSelItem();
    void LoadAllNote();
    void CreateNoteItem();
    int Update(float deltatime, int haveinput);
    void Create(UIWnd * pWnd);
};

#endif // PAL3A_UITITLE_JDHY_H

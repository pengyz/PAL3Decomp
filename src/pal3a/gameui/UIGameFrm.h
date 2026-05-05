#ifndef PAL3A_UIGAMEFRM_H
#define PAL3A_UIGAMEFRM_H

#include "pal3a_types.h"

class UIGameFrm {
public:
    char _data[31364];

    ~UIGameFrm();
    UIFrameWnd * GetFrmPtr(PAL3_FRAME frame);
    void SetSelectEmote(SELECT_EMOTE em0, SELECT_EMOTE em1);
    void Render();
    UIGameFrm();
    void HideSelectEmote();
    void Destroy();
    void ShowSelectEmote();
    PAL3_FRAME GetLastFrm();
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void Create();
    UIFrameWnd * CreateFrm(PAL3_FRAME frm, int nRoleID);
    void SwitchFrame(PAL3_FRAME nextframe, int nRoleID);
    int IsWaiting();
    UIEmote & GetEmoteWnd();
    int Update(float deltatime, int haveinput);
};

bool IfRenderScene(GAME_STATE state);

#endif // PAL3A_UIGAMEFRM_H

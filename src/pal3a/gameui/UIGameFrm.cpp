#include "UIGameFrm.h"

UIGameFrm::~UIGameFrm()
{
    /* stub */
}

UIFrameWnd * UIGameFrm::GetFrmPtr(PAL3_FRAME frame)
{
    /* stub */
    return NULL;
}

void UIGameFrm::SetSelectEmote(SELECT_EMOTE em0, SELECT_EMOTE em1)
{
    /* stub */
}

void UIGameFrm::Render()
{
    /* stub */
}

UIGameFrm::UIGameFrm()
{
    /* stub */
}

void UIGameFrm::HideSelectEmote()
{
    /* stub */
}

void UIGameFrm::Destroy()
{
    /* stub */
}

void UIGameFrm::ShowSelectEmote()
{
    /* stub */
}

PAL3_FRAME UIGameFrm::GetLastFrm()
{
    /* stub */
    return (PAL3_FRAME)0;
}

int UIGameFrm::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

void UIGameFrm::Create()
{
    /* stub */
}

UIFrameWnd * UIGameFrm::CreateFrm(PAL3_FRAME frm, int nRoleID)
{
    /* stub */
    return NULL;
}

void UIGameFrm::SwitchFrame(PAL3_FRAME nextframe, int nRoleID)
{
    /* stub */
}

int UIGameFrm::IsWaiting()
{
    /* stub */
    return 0;
}

UIEmote & UIGameFrm::GetEmoteWnd()
{
    /* stub */
    static char _buf[256] = {0}; return *(UIEmote*)_buf;
}

int UIGameFrm::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

bool IfRenderScene(GAME_STATE state)
{
    /* stub */
    return FALSE;
}


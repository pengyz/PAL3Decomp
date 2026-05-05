#include "MagicUI.h"

MagicUI::MagicUI()
{
    /* stub */
}

MagicUI::~MagicUI()
{
    /* stub */
}

void MagicUI::CtlList(uchar flag)
{
    /* stub */
}

void MagicUI::CreateAttFrame(int Role, tagRECT * rect)
{
    /* stub */
}

void MagicUI::SetRoleSkill()
{
    /* stub */
}

bool MagicUI::CanUseThis(PlayerSkill * pSkill, int role)
{
    /* stub */
    return FALSE;
}

bool MagicUI::CheckUsable(int l_index, int l_type, uchar bdisinfo)
{
    /* stub */
    return FALSE;
}

bool MagicUI::CheckCom(int l_index, int l_type)
{
    /* stub */
    return FALSE;
}

void MagicUI::CtrlAttFrameDisplay(int Role)
{
    /* stub */
}

void MagicUI::GetRoleState(int role, gbColorQuad color)
{
    /* stub */
}

void MagicUI::Render()
{
    /* stub */
}

void MagicUI::UpdateMagicLV(PlayerSkill * pMagic, int Role)
{
    /* stub */
}

void MagicUI::DisSkillInfo(PlayerSkill m_skill)
{
    /* stub */
}

void MagicUI::UpdateMagicVal(int Role, int l_type, int magic)
{
    /* stub */
}

bool MagicUI::UsingMagicRole(int usingrole, int acceptrole, int selnum)
{
    /* stub */
    return FALSE;
}

int MagicUI::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

void MagicUI::GetRoleSkill()
{
    /* stub */
}

void MagicUI::SetBtnParEffect(int flag)
{
    /* stub */
}

void MagicUI::ReSetState()
{
    /* stub */
}

void MagicUI::SetZX(uchar is)
{
    /* stub */
}

int MagicUI::CheckRealRole()
{
    /* stub */
    return 0;
}

void MagicUI::SetLK(uchar is)
{
    /* stub */
}

int MagicUI::UpdateKeyCtrl()
{
    /* stub */
    return 0;
}

void MagicUI::SetXJ(uchar is)
{
    /* stub */
}

void MagicUI::ChangeGrid(uchar isLarge)
{
    /* stub */
}

void MagicUI::SetMagicUI()
{
    /* stub */
}

void MagicUI::CheckComQuantum()
{
    /* stub */
}

void MagicUI::SetJT(uchar is)
{
    /* stub */
}

void MagicUI::AdjustHeadPos(int Role, tagRECT * rect)
{
    /* stub */
}

void MagicUI::MgrStpCtrl()
{
    /* stub */
}

int MagicUI::PrevRole(int * role)
{
    /* stub */
    return 0;
}

bool MagicUI::CheckUsable_Simple(int l_index, int l_type)
{
    /* stub */
    return FALSE;
}

void MagicUI::ComboFinal(int role, int selnum)
{
    /* stub */
}

void MagicUI::Create(UIWnd * pWnd)
{
    /* stub */
}

void MagicUI::CreateHead(int Role, tagRECT * rect)
{
    /* stub */
}

int MagicUI::NextRole(int * role)
{
    /* stub */
    return 0;
}

int MagicUI::CheckNeedTo(int l_index, int l_type)
{
    /* stub */
    return 0;
}

void MagicUI::SetCQ(uchar is)
{
    /* stub */
}

void MagicUI::InitComItem()
{
    /* stub */
}

void MagicUI::CreateStpCtl()
{
    /* stub */
}

void MagicUI::ControlPage(int Page)
{
    /* stub */
}

int MagicUI::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

void MagicUI::IsShow(int Role, uchar flag)
{
    /* stub */
}

void MagicUI::SetComParEffect()
{
    /* stub */
}

void MagicUI::SetParEffect(int Role)
{
    /* stub */
}

void MagicUI::RealCom()
{
    /* stub */
}

void MagicUI::GetListVal(int Role, Magic_ListType listType)
{
    /* stub */
}

bool MagicUI::CalProbability(float quantum)
{
    /* stub */
    return FALSE;
}

void MagicUI::SetRoleVal()
{
    /* stub */
}

int MagicUI::Warp(int n, float warp)
{
    /* stub */
    return 0;
}


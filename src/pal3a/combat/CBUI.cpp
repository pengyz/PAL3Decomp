#include "CBUI.h"

CCBAIWindow::~CCBAIWindow()
{
    /* stub */
}

int CCBAIWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

CCBAIWindow::CCBAIWindow()
{
    /* stub */
}

bool CCBAIWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

void CCBAIWindow::ShowWindow(int show)
{
    /* stub */
}

void CCBAIWindow::Reset()
{
    /* stub */
}

void CCBAIWindow::Destroy()
{
    /* stub */
}

int CCBAIWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

bool CCBControlWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

int CCBControlWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

void CCBControlWindow::HandleInput()
{
    /* stub */
}

void CCBControlWindow::HandleEnable(int dir, int n)
{
    /* stub */
}

bool CCBControlWindow::CreateButton(UIButton * * ppButton, uint id, tagRECT * rc, char * picname)
{
    /* stub */
    return FALSE;
}

void CCBControlWindow::CreateButtons()
{
    /* stub */
}

void CCBControlWindow::DefaultKey()
{
    /* stub */
}

CCBControlWindow::~CCBControlWindow()
{
    /* stub */
}

void CCBControlWindow::MoveButtons()
{
    /* stub */
}

void CCBControlWindow::KeyPressed()
{
    /* stub */
}

void CCBControlWindow::Destroy()
{
    /* stub */
}

int CCBControlWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

bool CCBControlWindow::CanHandleMiddle()
{
    /* stub */
    return FALSE;
}

CCBControlWindow::CCBControlWindow()
{
    /* stub */
}

void CCBControlWindow::CheckKeyInput(int dir)
{
    /* stub */
}

void CCBControlWindow::Reset()
{
    /* stub */
}

int CCBFiveNimbusWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

void CCBFiveNimbusWindow::ConsumeAllNimbus()
{
    /* stub */
}

CCBFiveNimbusWindow::CCBFiveNimbusWindow()
{
    /* stub */
}

void CCBFiveNimbusWindow::CheckNimbusState()
{
    /* stub */
}

CCBFiveNimbusWindow::~CCBFiveNimbusWindow()
{
    /* stub */
}

void CCBFiveNimbusWindow::SetNimbusCtrlState(ECBFiveNimbus eNim, int iState)
{
    /* stub */
}

void CCBFiveNimbusWindow::DisableCtrl()
{
    /* stub */
}

void CCBFiveNimbusWindow::SetNimbusStep(int nNimbusStep)
{
    /* stub */
}

void CCBFiveNimbusWindow::SetNimbus(ECBFiveNimbus nimbus, int nimbusnum)
{
    /* stub */
}

void CCBFiveNimbusWindow::UpdateFNOpenWindow(float deltatime)
{
    /* stub */
}

int CCBFiveNimbusWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

void CCBFiveNimbusWindow::ConsumeNimbus(ECBFiveNimbus nimbus)
{
    /* stub */
}

void CCBFiveNimbusWindow::Destroy()
{
    /* stub */
}

void CCBFiveNimbusWindow::Reset()
{
    /* stub */
}

void CCBFiveNimbusWindow::ShowWindow(int show)
{
    /* stub */
}

int CCBFiveNimbusWindow::GetChangeRound()
{
    /* stub */
    return 0;
}

bool CCBFiveNimbusWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

bool CCBFiveNimbusWindow::Init()
{
    /* stub */
    return FALSE;
}

int CCBItemWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

void CCBItemWindow::Reset()
{
    /* stub */
}

CCBItemWindow::~CCBItemWindow()
{
    /* stub */
}

bool CCBItemWindow::CreateButton(UIPushButton * * ppButton, uint id, tagRECT * rc, char * picname)
{
    /* stub */
    return FALSE;
}

CCBItemWindow::CCBItemWindow()
{
    /* stub */
}

bool CCBItemWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

int CCBItemWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

void CCBItemWindow::SetActivePage(int n)
{
    /* stub */
}

void CCBItemWindow::HandleInput()
{
    /* stub */
}

void CCBItemWindow::Destroy()
{
    /* stub */
}

void CCBItemWindow::CreateButtons()
{
    /* stub */
}

int CCBLineupWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

CCBLineupWindow::~CCBLineupWindow()
{
    /* stub */
}

void CCBLineupWindow::SetSelected(int nSelected)
{
    /* stub */
}

void CCBLineupWindow::Destroy()
{
    /* stub */
}

void CCBLineupWindow::Reset()
{
    /* stub */
}

int CCBLineupWindow::IsPtOnInitPos(tagPOINT pt)
{
    /* stub */
    return 0;
}

bool CCBLineupWindow::IsPtOnInitPos(int nPosIndex, tagPOINT pt)
{
    /* stub */
    return FALSE;
}

void CCBLineupWindow::ShowWindow(int show)
{
    /* stub */
}

bool CCBLineupWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

void CCBLineupWindow::RefreshFacePos()
{
    /* stub */
}

int CCBLineupWindow::SetFaceLineup(int nFaceIndex, int nPosIndex)
{
    /* stub */
    return 0;
}

int CCBLineupWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

CCBLineupWindow::CCBLineupWindow()
{
    /* stub */
}

int CCBLineupWindow::IsFaceOnInitPos(int nFaceIndex)
{
    /* stub */
    return 0;
}

bool CCBLineupWindow::IsFaceOnInitPos(int nPosIndex, int nFaceIndex, int * nArea)
{
    /* stub */
    return FALSE;
}

void CCBLineupWindow::Render()
{
    /* stub */
}

int CCBLineupWindow::IsPtOnFace(tagPOINT pt)
{
    /* stub */
    return 0;
}

bool CCBLineupWindow::IsPtOnFace(int nFaceIndex, tagPOINT pt)
{
    /* stub */
    return FALSE;
}

void CCBMagicWindow::Destroy()
{
    /* stub */
}

CCBMagicWindow::~CCBMagicWindow()
{
    /* stub */
}

bool CCBMagicWindow::CreateButton(UIPushButton * * ppButton, uint id, tagRECT * rc, char * picname)
{
    /* stub */
    return FALSE;
}

void CCBMagicWindow::CreateButtons()
{
    /* stub */
}

void CCBMagicWindow::ForbidPage(ECBBattleFieldAttr eBFA)
{
    /* stub */
}

int CCBMagicWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

bool CCBMagicWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

int CCBMagicWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

CCBMagicWindow::CCBMagicWindow()
{
    /* stub */
}

void CCBMagicWindow::HandleInput()
{
    /* stub */
}

void CCBMagicWindow::SetActivePage(int n)
{
    /* stub */
}

int CCBMagicWindow::GetActivePage()
{
    /* stub */
    return 0;
}

void CCBMagicWindow::Reset()
{
    /* stub */
}

CCBParabolaWindow::CCBParabolaWindow()
{
    /* stub */
}

int CCBParabolaWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

void CCBParabolaWindow::Destroy()
{
    /* stub */
}

CCBParabolaWindow::~CCBParabolaWindow()
{
    /* stub */
}

void CCBParabolaWindow::Reset()
{
    /* stub */
}

int CCBParabolaWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

bool CCBParabolaWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

void CCBProtectWindow::Reset()
{
    /* stub */
}

void CCBProtectWindow::Destroy()
{
    /* stub */
}

int CCBProtectWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

void CCBProtectWindow::ShowWindow(int show)
{
    /* stub */
}

CCBProtectWindow::~CCBProtectWindow()
{
    /* stub */
}

CCBProtectWindow::CCBProtectWindow()
{
    /* stub */
}

bool CCBProtectWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

int CCBProtectWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

int CCBResultWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

CCBResultWindow::~CCBResultWindow()
{
    /* stub */
}

void CCBResultWindow::Render()
{
    /* stub */
}

int CCBResultWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

CCBResultWindow::CCBResultWindow()
{
    /* stub */
}

void CCBResultWindow::Destroy()
{
    /* stub */
}

void CCBResultWindow::Reset()
{
    /* stub */
}

void CCBResultWindow::ShowWindow(int show)
{
    /* stub */
}

bool CCBResultWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

void CCBSkillWindow::Reset()
{
    /* stub */
}

CCBSkillWindow::~CCBSkillWindow()
{
    /* stub */
}

int CCBSkillWindow::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

bool CCBSkillWindow::Create(tagRECT * rc, UIWnd * pFather)
{
    /* stub */
    return FALSE;
}

int CCBSkillWindow::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

CCBSkillWindow::CCBSkillWindow()
{
    /* stub */
}

void CCBSkillWindow::Destroy()
{
    /* stub */
}

tagRECT CCBUI::GetNimbusArea(tagRECT * __$ReturnUdt)
{
    /* stub */
    tagRECT _ret = {0}; return _ret;
}

bool CCBUI::CreateItemWindow()
{
    /* stub */
    return FALSE;
}

bool CCBUI::CreateMagicWindow()
{
    /* stub */
    return FALSE;
}

bool CCBUI::CreateAttackSequen()
{
    /* stub */
    return FALSE;
}

CCBUI::CCBUI(CCBSystem * pCBSystem)
{
    /* stub */
}

bool CCBUI::CreateBattleFieldAttr()
{
    /* stub */
    return FALSE;
}

void CCBUI::ClearFinishedTask()
{
    /* stub */
}

void CCBUI::Render()
{
    /* stub */
}

bool CCBUI::CreateStageControl()
{
    /* stub */
    return FALSE;
}

void CCBUI::ChangeSpecStateLum()
{
    /* stub */
}

gbColorQuad CCBUI::GetNimbusColor(gbColorQuad * __$ReturnUdt)
{
    /* stub */
    gbColorQuad _ret = {0}; return _ret;
}

unsigned long CCBUI::LineMove(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBUI::ShowRoleStatePanel(uchar bVisible)
{
    /* stub */
}

bool CCBUI::Init()
{
    /* stub */
    return FALSE;
}

CCBUI::~CCBUI()
{
    /* stub */
}

bool CCBUI::CreateLineupWindow()
{
    /* stub */
    return FALSE;
}

bool CCBUI::CreateObj()
{
    /* stub */
    return FALSE;
}

void CCBUI::AddResultWindowAni()
{
    /* stub */
}

bool CCBUI::CheckNimbusMove(tagPOINT pt, tagRECT area)
{
    /* stub */
    return FALSE;
}

void CCBUI::ShowControlWindow(uchar bShow)
{
    /* stub */
}

void CCBUI::ShowLineupWindow(uchar bVisible)
{
    /* stub */
}

void CCBUI::ShowBattleFieldAttr(ECBBattleFieldAttr attr, ECBForce force)
{
    /* stub */
}

void CCBUI::Destroy()
{
    /* stub */
}

int CCBUI::OnMessage(uint msg, ulong wparam, ulong lparam)
{
    /* stub */
    return 0;
}

unsigned long CCBUI::GravityDown(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBUI::AddTask(void * fp, ulong dwTaskID, float fExpectStartTime, float fExpectEndTime, tagUIParam * pParam)
{
    /* stub */
    return FALSE;
}

void CCBUI::SetNimbusToNimbusControl()
{
    /* stub */
}

bool CCBUI::CreateProtectWindow()
{
    /* stub */
    return FALSE;
}

void CCBUI::WriteNimbusToPlayerMgr()
{
    /* stub */
}

void CCBUI::ShowProtectWindow(uchar bVisible)
{
    /* stub */
}

void CCBUI::DoTask()
{
    /* stub */
}

bool CCBUI::CreateResultWindow()
{
    /* stub */
    return FALSE;
}

void CCBUI::ShowDialogWindow(uchar bVisible)
{
    /* stub */
}

bool CCBUI::Create()
{
    /* stub */
    return FALSE;
}

void CCBUI::ConfigImbibeNimbus(int index, ECBFiveNimbus nimbustype, tagPOINT pos, float accelerate)
{
    /* stub */
}

bool CCBUI::CreateControlWindow()
{
    /* stub */
    return FALSE;
}

bool CCBUI::CreateResultItem()
{
    /* stub */
    return FALSE;
}

void CCBUI::HideAll()
{
    /* stub */
}

bool CCBUI::CreateButton(UIButton * * ppButton, uint id, tagRECT * rc, char * picname)
{
    /* stub */
    return FALSE;
}

bool CCBUI::IsResultWindowClosed()
{
    /* stub */
    return FALSE;
}

bool CCBUI::DelTask(int nIndex)
{
    /* stub */
    return FALSE;
}

void CCBUI::ShowAIWindow(int nRoleIndex, uchar bVisible)
{
    /* stub */
}

bool CCBUI::CreateParaWindow()
{
    /* stub */
    return FALSE;
}

bool CCBUI::CreateRoleStatePanel()
{
    /* stub */
    return FALSE;
}

void CCBUI::ShowResultWindow(uchar bVisible)
{
    /* stub */
}

unsigned long CCBUI::ChangeNumTxt(ulong __formal)
{
    /* stub */
    return 0;
}

int CCBUI::Update(float deltatime, int haveinput)
{
    /* stub */
    return 0;
}

bool CCBUI::IsImbibeNimbusNotFinish()
{
    /* stub */
    return FALSE;
}

void CCBUI::DeleteUIObj(UIWnd * pUIWnd)
{
    /* stub */
}

void CCBUI::AddRightControlButtonAni()
{
    /* stub */
}

void CCBUI::Reset()
{
    /* stub */
}

bool CCBUI::CreateSkillWindow()
{
    /* stub */
    return FALSE;
}

bool CCBUI::CreateFiveNimbus()
{
    /* stub */
    return FALSE;
}

void CCBUI::CreateImbibeNimbus(int iNum)
{
    /* stub */
}

bool CCBUI::CreateAIWindow()
{
    /* stub */
    return FALSE;
}

bool CCBUI::CreateCombatPanel()
{
    /* stub */
    return FALSE;
}

bool CreateObj(UIButtonEX * * ppObj)
{
    /* stub */
    return FALSE;
}

bool CreateObj(UIProgressBar * * ppObj)
{
    /* stub */
    return FALSE;
}

bool CreateObj(UIButton * * ppObj)
{
    /* stub */
    return FALSE;
}

bool CreateObj(UIPushButton * * ppObj)
{
    /* stub */
    return FALSE;
}

bool CreateObj(UIStatic * * ppObj)
{
    /* stub */
    return FALSE;
}


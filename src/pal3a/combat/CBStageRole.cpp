#include "CBStageRole.h"

unsigned long CCBStageRole::ProcFlyRun(ulong dwMsg)
{
    /* stub */
    return 0;
}

int CCBStageRole::CheckAction(ACTION_KIND ActKind)
{
    /* stub */
    return 0;
}

bool CCBStageRole::DelAllTask()
{
    /* stub */
    return FALSE;
}

void CCBStageRole::OnChangeAction()
{
    /* stub */
}

unsigned long CCBStageRole::ProcFastRun(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStageRole::EndTask(void * fp, ulong dwTaskID)
{
    /* stub */
    return FALSE;
}

bool CCBStageRole::ForceAddTask(void * fp, gbVec3D * pV1, tagCmdData * pCmd, ECBRoleTaskMode eMode)
{
    /* stub */
    return FALSE;
}

void CCBStageRole::LoadWeaponModel()
{
    /* stub */
}

bool CCBStageRole::IsAtInitPos()
{
    /* stub */
    return FALSE;
}

void CCBStageRole::SetParam(tagParam * pParam, ulong dw1, ulong dw2, ulong dw3)
{
    /* stub */
}

float CCBStageRole::GetRotAngle(gbVec3D * pvecTarget)
{
    /* stub */
    return 0.0f;
}

bool CCBStageRole::Grab(ulong dwStageTaskID, uchar bNormal)
{
    /* stub */
    return FALSE;
}

void CCBStageRole::SetMaxBlend()
{
    /* stub */
}

unsigned long CCBStageRole::ProcWin(ulong dwMsg)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcEnemyFlee(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcUseAttackItem(ulong dwMsg)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcPursueRole(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStageRole::SetAlive(uchar bAlive)
{
    /* stub */
}

float CCBStageRole::GetRoleHeight()
{
    /* stub */
    return 0.0f;
}

unsigned long CCBStageRole::ProcDodge(ulong dwMsg)
{
    /* stub */
    return 0;
}

void CCBStageRole::Reset()
{
    /* stub */
}

unsigned long CCBStageRole::ProcTurn(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStageRole::FaceToRole(int nRoleIndex)
{
    /* stub */
}

unsigned long CCBStageRole::ProcMagic(ulong dwMsg)
{
    /* stub */
    return 0;
}

void CCBStageRole::ForceEndTaskByPFN(void * fp)
{
    /* stub */
}

void CCBStageRole::DangerForceRelease()
{
    /* stub */
}

unsigned long CCBStageRole::ProcFlee(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcWeaponSkill(ulong dwMsg)
{
    /* stub */
    return 0;
}

int CCBStageRole::GetCurrentTaskIndex()
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcCatchED(ulong dwMsg)
{
    /* stub */
    return 0;
}

bool CCBStageRole::IsUnderMouse()
{
    /* stub */
    return FALSE;
}

void CCBStageRole::SetAction(ulong dwActKey, int nActIndex, uchar bReset)
{
    /* stub */
}

void CCBStageRole::SetAction(int nActIndex, uchar bReset)
{
    /* stub */
}

void CCBStageRole::ClearAniMsg()
{
    /* stub */
}

void CCBStageRole::SetVisible(uchar bVisit)
{
    /* stub */
}

bool CCBStageRole::SetRoleActState(ERoleActState eras)
{
    /* stub */
    return FALSE;
}

void CCBStageRole::Reload(char * name)
{
    /* stub */
}

unsigned long CCBStageRole::ProcFlingAct(ulong dwMsg)
{
    /* stub */
    return 0;
}

void CCBStageRole::HandleThrowWeapon()
{
    /* stub */
}

unsigned long CCBStageRole::ProcBlock(ulong dwMsg)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcStartDefence(ulong dwMsg)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcProtect(ulong dwMsg)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcMagicWait(ulong dwMsg)
{
    /* stub */
    return 0;
}

void CCBStageRole::GetPointerPos(gbVec3D * vec)
{
    /* stub */
}

bool CCBStageRole::Destroy()
{
    /* stub */
    return FALSE;
}

unsigned long CCBStageRole::ProcTurnToRole(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcWeaponFly(ulong dwMsg)
{
    /* stub */
    return 0;
}

void CCBStageRole::PushBackAllTask()
{
    /* stub */
}

unsigned CCBStageRole::GetCurrentTask()
{
    /* stub */
    return 0;
}

void CCBStageRole::ClearBadPushTask()
{
    /* stub */
}

void CCBStageRole::ForceRelease()
{
    /* stub */
}

void CCBStageRole::RenderWeaponModel(gbMatrixStack * pView)
{
    /* stub */
}

void CCBStageRole::Release(ulong dwStageTaskID)
{
    /* stub */
}

float CCBStageRole::GetRoleRadius()
{
    /* stub */
    return 0.0f;
}

void CCBStageRole::Render(gbMatrixStack * pView)
{
    /* stub */
}

bool CCBStageRole::TryRelease(ulong dwStageTaskID)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStageRole::ProcTurnToPos(ulong __formal)
{
    /* stub */
    return 0;
}

gbOBBox * CCBStageRole::GetOBBox()
{
    /* stub */
    return NULL;
}

unsigned long CCBStageRole::ProcRotate(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStageRole::Init(int nIndex, ulong dwID, gbActor * pActor)
{
    /* stub */
    return FALSE;
}

bool CCBStageRole::IsAtProtectPos(int nRoleIndex, int nAttacker)
{
    /* stub */
    return FALSE;
}

bool CCBStageRole::AddTask(void * fp, ulong dwStageTaskID, gbVec3D * pV1, tagCmdData * pCmd, ECBRoleTaskMode eMode)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStageRole::ProcTransportRun(ulong dwMsg)
{
    /* stub */
    return 0;
}

ACTION_KIND CCBStageRole::GetProperCurAction()
{
    /* stub */
    return (ACTION_KIND)0;
}

void CCBStageRole::ForceDelTaskByPFN(void * fp)
{
    /* stub */
}

unsigned long CCBStageRole::ProcUpgradeAct(ulong dw)
{
    /* stub */
    return 0;
}

bool CCBStageRole::DelTask(int nIndex)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStageRole::ProcJumpTo(ulong dwMsg)
{
    /* stub */
    return 0;
}

bool CCBStageRole::IsIdle()
{
    /* stub */
    return FALSE;
}

unsigned long CCBStageRole::ProcFleeWait(ulong dwMsg)
{
    /* stub */
    return 0;
}

char * CCBStageRole::GetActionName(ulong dwActKey, int nActIndex)
{
    /* stub */
    return NULL;
}

unsigned long CCBStageRole::ProcAttack(ulong dwMsg)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcFlyRotRun(ulong dwMsg)
{
    /* stub */
    return 0;
}

CCBStageRole::~CCBStageRole()
{
    /* stub */
}

bool CCBStageRole::IsDoTask(void * fpTask)
{
    /* stub */
    return FALSE;
}

void CCBStageRole::SetBlend(uchar bBlend, float fParam)
{
    /* stub */
}

void CCBStageRole::Update()
{
    /* stub */
}

void CCBStageRole::OnPlayAction()
{
    /* stub */
}

unsigned long CCBStageRole::ProcRun(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStageRole::Create(int nIndex)
{
    /* stub */
    return FALSE;
}

void CCBStageRole::SetForceFinishThrowingWeapon(uchar bForce)
{
    /* stub */
}

void CCBStageRole::GetWeaponTagByACT(int nRoleIndex, ACTION_KIND ACT, uchar * left, uchar * right)
{
    /* stub */
}

unsigned long CCBStageRole::ProcWait(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStageRole::LoadAction(ulong dwActKey, int nActIndex)
{
    /* stub */
}

void CCBStageRole::LoadAction(int nActIndex)
{
    /* stub */
}

bool CCBStageRole::IsGrabedBy(ulong dwStageTaskID)
{
    /* stub */
    return FALSE;
}

void CCBStageRole::ReplaceActor(Actor * pActor)
{
    /* stub */
}

bool CCBStageRole::IsCollideRay(gbRay ray)
{
    /* stub */
    return FALSE;
}

float CCBStageRole::GetBlend()
{
    /* stub */
    return 0.0f;
}

bool CCBStageRole::IsTaskFinished(void * fpTask, ulong dwTaskID)
{
    /* stub */
    return FALSE;
}

void CCBStageRole::SetPause(uchar bPause)
{
    /* stub */
}

void CCBStageRole::UnLoadWeaponModel()
{
    /* stub */
}

void CCBStageRole::LoadRoleAction()
{
    /* stub */
}

void CCBStageRole::DoTask(ulong dwMsg)
{
    /* stub */
}

void CCBStageRole::ClearFinishedTask()
{
    /* stub */
}

unsigned long CCBStageRole::ProcVarianceaAct(ulong dwMsg)
{
    /* stub */
    return 0;
}

void CCBStageRole::ShowSpecState(int nX, int nY, uchar bShow)
{
    /* stub */
}

unsigned long CCBStageRole::ProcSkill(ulong dwMsg)
{
    /* stub */
    return 0;
}

void CCBStageRole::SetBladeTime(float fBladeTime)
{
    /* stub */
}

unsigned long CCBStageRole::ProcFastRunToRoleFront(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStageRole::ProcUseRecoverItem(ulong dwMsg)
{
    /* stub */
    return 0;
}

void CCBStageRole::Proceed(ulong dwMsg)
{
    /* stub */
}

CCBStageRole::CCBStageRole(CCBStage * pStage)
{
    /* stub */
}

unsigned long CCBStageRole::ProcRunToRoleInitPos(ulong __formal)
{
    /* stub */
    return 0;
}


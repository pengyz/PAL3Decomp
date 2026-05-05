#include "CBStage.h"

unsigned long CCBStage::ProcSkillAct(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcMagic(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcWinAction(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcFlee(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcGreatMagic(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::Reset()
{
    /* stub */
}

unsigned long CCBStage::GetTaskID(int nIndex)
{
    /* stub */
    return 0;
}

bool CCBStage::IsTaskValid(int n)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcShowLevelup(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowForbidName(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcNormalAttackAct(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowDamage(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::CancelBFA()
{
    /* stub */
}

unsigned long CCBStage::ProcCoAttack(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcEnemyFlee(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::InitObj()
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcShowFleeResult(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcScreenFadeOut(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::SetBFAAttr(ECBBattleFieldAttr attr, int nRoleIndex)
{
    /* stub */
}

bool CCBStage::IsTaskExist(ulong dwTaskID)
{
    /* stub */
    return FALSE;
}

bool CCBStage::EndTask(int nIndex)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcShowEnemyFiveLineup(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowMagicLevelup(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcUseItemAct(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcFiveLienupFadeIn(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowCombatResult(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::UpdateDamageNumPosY()
{
    /* stub */
}

void CCBStage::SelectRelativeRole(int nRoleIndex, ulong dwParam, ulong dwCmdID)
{
    /* stub */
}

unsigned long CCBStage::ProcSkillEnd(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcPXRunOut(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcSelectRole(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::IsSubTaskFinished(int n, int nSub)
{
    /* stub */
    return FALSE;
}

bool CCBStage::IsSubTaskValid(int n, int nSub)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcCoAttackEnd(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::HandleKeyEnemy(int * Selected, tagStageTask * pTask, tagStageSubTask * pSubTask)
{
    /* stub */
    return FALSE;
}

void CCBStage::HandleKeyCtrl(int * n, int type, int op, int srcRole, ulong dwCmdKind)
{
    /* stub */
}

unsigned long CCBStage::ProcSetBFA(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::EditorUpdate()
{
    /* stub */
}

void CCBStage::GetTaskState(int nIndex, ECBStageTaskState * State)
{
    /* stub */
}

void CCBStage::GetTaskState(int nIndex, uchar * bFinished, ulong * dwReturn)
{
    /* stub */
}

bool CCBStage::HasNormalAttackRole(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcAllRoleToInitPos(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcProtect(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcRoleUndoHermit(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcEffect(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcMagicBlock(ulong __formal)
{
    /* stub */
    return 0;
}

int CCBStage::GetRoleTaskNum(int nRoleIndex)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcFadeOutRole(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::Destroy()
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcPXRunIn(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcFlingAct(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::InitBFACounter()
{
    /* stub */
}

unsigned long CCBStage::ProcGrabStageRole(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcStartDefence(ulong __formal)
{
    /* stub */
    return 0;
}

gbVec3D CCBStage::CalulateParabola(gbVec3D * __$ReturnUdt, gbVec3D A, gbVec3D B, float H)
{
    /* stub */
    gbVec3D _ret = {0}; return _ret;
}

unsigned long CCBStage::ProcShowMiss(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcWeaponSkill(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowCombatDialog(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowCost(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcUnLockVariance(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::DelTask(int nIndex)
{
    /* stub */
    return FALSE;
}

bool CCBStage::IsIdle()
{
    /* stub */
    return FALSE;
}

int CCBStage::HandleImbibeNimbus(tagCmdData cmd)
{
    /* stub */
    return 0;
}

tagStageTask * CCBStage::GetTask(int nIndex)
{
    /* stub */
    return NULL;
}

unsigned long CCBStage::ProcPreLoadEffGroup(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcFiveLienupFadeOut(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::CheckBFARound(int nRoleIndex)
{
    /* stub */
}

int CCBStage::SelectDefaultRole(ulong dwParam, tagCmdData * pCmd)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowLosePanel(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowNewFightSkill(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowName(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowItemName(ulong __formal)
{
    /* stub */
    return 0;
}

CCBStage::~CCBStage()
{
    /* stub */
}

bool CCBStage::HasEnemyNormalAttackRole(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcMagicEnd(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcCoAttackAct(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcSling(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcFadeInRole(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::Init()
{
    /* stub */
    return FALSE;
}

int CCBStage::AddTask(ECBStageTask eTask, tagCmdData * pCmd, uchar bAutoDel)
{
    /* stub */
    return 0;
}

void CCBStage::GetProperAttackPos(gbVec3D * vec, tagCmdData * pCmd)
{
    /* stub */
}

unsigned long CCBStage::ProcScreenFadeIn(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcNormalAttackDodge(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::IsAllSubTaskFinished(int n)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcAllRoleToCoAttackPos(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::IsTaskValidButNotFinish(ECBStageTask eTask)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcWeaponSkillAct(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcNormalAttack(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::StartTask(int nIndex)
{
    /* stub */
    return FALSE;
}

void CCBStage::Render()
{
    /* stub */
}

unsigned long CCBStage::ProcProtectAct(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcFling(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::HandleVariance(int taskIndex)
{
    /* stub */
}

unsigned long CCBStage::ProcSkillBlock(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowSneakAttackState(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcVarianceAct(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::DestroyObj()
{
    /* stub */
    return FALSE;
}

char * CCBStage::GetRoleName(ulong nameCrc)
{
    /* stub */
    return NULL;
}

unsigned long CCBStage::ProcPXVarianceDead(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::CreateObj()
{
    /* stub */
    return FALSE;
}

CCBStage::CCBStage(CCBSystem * pCBSystem)
{
    /* stub */
}

unsigned long CCBStage::ProcNormalAttackEnd(ulong __formal)
{
    /* stub */
    return 0;
}

int CCBStage::GetRoleIndex(ulong nameCrc)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcSkill(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::Procced()
{
    /* stub */
}

void CCBStage::DoTask()
{
    /* stub */
}

unsigned long CCBStage::ProcReleaseStageRole(ulong __formal)
{
    /* stub */
    return 0;
}

int CCBStage::AddSubTask(int nIndex, void * fp, tagParam * pParam, float fWaitTime, float fTime)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowWinPanel(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcNormalAttackEffect(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowUpgradeAct(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcMagicAct(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcRoleHermit(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::HandleKeyFriend(int * Selected, tagStageTask * pTask, tagStageSubTask * pSubTask)
{
    /* stub */
    return FALSE;
}

bool CCBStage::IsTaskFinished(int nIndex)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcMusicFadeOut(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcNormalAttackBlock(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcLockVariance(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::StartSubTask(int n, int nSub)
{
    /* stub */
    return FALSE;
}

bool CCBStage::Create()
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcWait(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcChangeInitPos(ulong __formal)
{
    /* stub */
    return 0;
}

bool CCBStage::ForceDelTask(int nIndex)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcUseItem(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcProtectEnd(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::ClearRoleAllTask(int nRoleIndex)
{
    /* stub */
}

void CCBStage::Update()
{
    /* stub */
}

bool CCBStage::IsDoTask(ECBStageTask eTask, int nRoleIndex)
{
    /* stub */
    return FALSE;
}

unsigned long CCBStage::ProcWeaponSkillEnd(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::EndRoleAllTask(int nRoleIndex)
{
    /* stub */
}

unsigned long CCBStage::ProcReLoadModel(ulong __formal)
{
    /* stub */
    return 0;
}

void CCBStage::SelectRole(int nRoleIndex)
{
    /* stub */
}

unsigned long CCBStage::ProcShowFiveLineup(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcGotoInitPos(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcFleeWait(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcShowGetItem(ulong __formal)
{
    /* stub */
    return 0;
}

unsigned long CCBStage::ProcMusicFadeIn(ulong __formal)
{
    /* stub */
    return 0;
}


#include "CBRoleState.h"

bool CCBRoleState::IsJingtianProtect(int nDestRole, int nAttacker)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::SpecAffect(int nSrcRole, int nDestRole, int nAffectIndex)
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::GetBestRoleReviveSkill(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsRolePoisoned(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::GetPoisonMagicForEnemy(int nRoleIndex)
{
    /* stub */
    return 0;
}

bool CCBRoleState::ItemSpecAffect(tagCmdData * pCmd, int nRoleIndex)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetForceAverageHP(ECBForce force, uchar bIncludeDead)
{
    /* stub */
    return 0;
}

void CCBRoleState::CheckCombatDialog(int nRoleIndex)
{
    /* stub */
}

void CCBRoleState::CheckGroundEffect(int nRoleIndex)
{
    /* stub */
}

int CCBRoleState::GetMoney()
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsRecoverCombo(ulong dwComboID)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::SetSpecState(int nRoleIndex, ECBRoleSpecState state, uchar bSet, uchar bSound)
{
    /* stub */
}

int CCBRoleState::GetForceAverageFullHP(ECBForce force, uchar bIncludeDead)
{
    /* stub */
    return 0;
}

int CCBRoleState::CalHasNormalAttackToDie(int nSrc, ECBForce force)
{
    /* stub */
    return 0;
}

bool CCBRoleState::SpecWeaponAffect(int nSrcRole, int nDestRole)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::IsAttackItem(ulong dwItemID)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetItemRecoverPower(int nRoleIndex, ulong dwItemID)
{
    /* stub */
    return 0;
}

int CCBRoleState::CalFullGP(int nRoleIndex, int nLevel)
{
    /* stub */
    return 0;
}

void CCBRoleState::GetProperForceRoleIndex(ECBForce force, int * nStart, int * nEnd)
{
    /* stub */
}

bool CCBRoleState::IsGem(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::GetBestBFAMagic(int nRoleIndex)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsRoleInBadSpecState(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::GetRoleMagicKind(int nRoleIndex, ulong dwMagicID, ECBMagicKind * eKind, int * nMagicIndex)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::IsAttackMagic(ulong dwMagicID)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetCoAttackDamage(ulong dwSrc, ulong dwDest, ulong dwParam)
{
    /* stub */
    return 0;
}

void CCBRoleState::ReviveAllFriendAtEnd()
{
    /* stub */
}

bool CCBRoleState::IsHarmfulSkill(ulong dwSkillID)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::MagicDamage(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::CancelVariance(int nRoleIndex)
{
    /* stub */
}

int CCBRoleState::GetRoleLuck(int nRoleIndex)
{
    /* stub */
    return 0;
}

void CCBRoleState::InitRoleEquipAttrib()
{
    /* stub */
}

void CCBRoleState::GetNormalAttackRange(tagCmdData * pCmd)
{
    /* stub */
}

bool CCBRoleState::CanRoleMove(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::CanRoleBeNormalAttack(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::FiveMagicToMagicKind(ECBFiveMagic fm, ECBMagicKind * mk)
{
    /* stub */
}

void CCBRoleState::FixState()
{
    /* stub */
}

bool CCBRoleState::IsBoss(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetAliveRoleNumInForce(ECBForce force)
{
    /* stub */
    return 0;
}

bool CCBRoleState::Destroy()
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::IsForbidWithBFA(ulong dwMagicID, int nRoleIndex)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetLowestHPCentRole(ECBForce force)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsHarmfulItem(ulong dwItemID)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::CanBeImbibeNimbus(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::IsRecoverMPItem(ulong dwItemID)
{
    /* stub */
    return FALSE;
}

ECBForce CCBRoleState::GetInvForce(ECBForce force)
{
    /* stub */
    return (ECBForce)0;
}

int CCBRoleState::GetWeakRoleNum(ECBForce force)
{
    /* stub */
    return 0;
}

void CCBRoleState::UpdateUI()
{
    /* stub */
}

ECBFiveMagic CCBRoleState::GetGreaterFiveMagic(ECBFiveMagic fm)
{
    /* stub */
    return (ECBFiveMagic)0;
}

bool CCBRoleState::CanCastTrick(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::GetBestRoleReviveItem(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

void CCBRoleState::HandleSpecStateBout(int nRoleIndex)
{
    /* stub */
}

void CCBRoleState::FightSkillCost(int nRoleIndex, ulong dwCmdID, int nDamage)
{
    /* stub */
}

bool CCBRoleState::IsGoodSpecStateItem(ulong dwItemID)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::DecGemUseTime(tagCmdData * pCmd)
{
    /* stub */
}

bool CCBRoleState::CanCoAttack(int nRoleIndex, ulong dwSkillID, ulong * dwCoAttackID)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::RandSetState()
{
    /* stub */
}

int CCBRoleState::ChangeRoleSpeed(int nRoleIndex, int nValue)
{
    /* stub */
    return 0;
}

void CCBRoleState::SetVisible(int nPanelIndex, uchar bVisible)
{
    /* stub */
}

int CCBRoleState::ChangeRoleValue(tagCmdData * pCmd, int nRoleIndex)
{
    /* stub */
    return 0;
}

void CCBRoleState::LoadRoleData()
{
    /* stub */
}

bool CCBRoleState::AttackSpecAffect(int nSrcRole, int nDestRole)
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::GetGoodMagicForEnemy(int nRoleIndex)
{
    /* stub */
    return 0;
}

tagRoleState * CCBRoleState::GetRole(int nIndex)
{
    /* stub */
    return NULL;
}

void CCBRoleState::Reset()
{
    /* stub */
}

unsigned long CCBRoleState::GetBestRoleAttackItem(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

void CCBRoleState::GetFiveMagicOfMagic(ulong dwMagicID, ECBFiveMagic * fm1, ECBFiveMagic * fm2)
{
    /* stub */
}

unsigned long CCBRoleState::GetBestBFAAttackMagic(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsNobodyAtLineupMiddle()
{
    /* stub */
    return FALSE;
}

void CCBRoleState::WriteBackRoleData()
{
    /* stub */
}

bool CCBRoleState::IsMagic(ulong dwMagicID)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::CanAttackBackRole(int nSrcRole, int nDestRole)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::WeaponSkillAffect(tagCmdData * pCmd, int nDestRole)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetGP(int nRoleIndex, uchar bGetFullValue)
{
    /* stub */
    return 0;
}

bool CCBRoleState::StealItem(int nSrcRole, int nDestRole)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::FillFiveMagicMatrix(ECBFiveMagic fm)
{
    /* stub */
}

unsigned long CCBRoleState::GetMagicIDInList(int nRoleIndex, int nPage, int nMagicIndex)
{
    /* stub */
    return 0;
}

void CCBRoleState::FillMagicList(int nRoleIndex)
{
    /* stub */
}

bool CCBRoleState::IsRecoverItem(ulong dwItemID)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::CanAction(int nIndex)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::HandleWinRoleState()
{
    /* stub */
}

bool CCBRoleState::MagicSpecAffect(tagCmdData * pCmd, int nRoleIndex)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::HandleSuicide(int nSrcRole)
{
    /* stub */
}

void CCBRoleState::VarianceRoundCounter(int nRoleIndex)
{
    /* stub */
}

void CCBRoleState::FillAIList(int nRoleIndex)
{
    /* stub */
}

bool CCBRoleState::CheckRoleValid(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::SetCoAttack(ulong dwCoAttackID)
{
    /* stub */
}

bool CCBRoleState::IsAttackCombo(ulong dwComboID)
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::GetBestRoleCureSpecStateMagic(int nRoleIndex, ECBRoleSpecState eSpecState, uchar bGreat)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsRoleItem(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::SetParam(tagParam * pParam, ulong dw1, ulong dw2, ulong dw3)
{
    /* stub */
}

bool CCBRoleState::IsSpecStateGood(ECBRoleSpecState state)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::SkillAffect(tagCmdData * pCmd, int nDestRole)
{
    /* stub */
    return 0;
}

bool CCBRoleState::RandSetPlayerLineup()
{
    /* stub */
    return FALSE;
}

void CCBRoleState::MagicKindToFiveMagic(ECBMagicKind mk, ECBFiveMagic * fm)
{
    /* stub */
}

unsigned long CCBRoleState::GetRandRoleMiscMagic(int nRoleIndex, uchar bGreat)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetInSpecStateRoleNum(ECBForce force, ECBRoleSpecState state)
{
    /* stub */
    return 0;
}

void CCBRoleState::LoadWeaponModel()
{
    /* stub */
}

void CCBRoleState::GetCoAttackRange(tagCmdData * pCmd)
{
    /* stub */
}

bool CCBRoleState::IsRecoverSkill(ulong dwSkillID)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetFightSkillPower(int nRoleIndex, ulong dwFightSkillID)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetNormalAttackDamage(int nSrc, int nDest, ulong dwParam)
{
    /* stub */
    return 0;
}

bool CCBRoleState::GetMagicKind(ulong dwMagicID, ECBMagicKind * eKind, int * nMagicIndex, int * nRoleIndex)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::GetCombatWinItem(int nStageTaskIndex)
{
    /* stub */
}

unsigned long CCBRoleState::GetBestRoleRecoverSkill(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

void CCBRoleState::FillItemList(int nRoleIndex, int nPage)
{
    /* stub */
}

void CCBRoleState::HandlePXVariance(int nRoleIndex)
{
    /* stub */
}

int CCBRoleState::GetLowestHPRole(int nSrcRole, ECBForce force)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetLowestHPRole(ECBForce force)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsTrickSpecialCostOK(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::InitRoleState()
{
    /* stub */
}

int CCBRoleState::GetRoleNumInForce(ECBForce force)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetFirstAliveRoleInForce(ECBForce force)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsAlive(int nIndex)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetMagicDamage(int nSrc, int nDest, ulong dwParam)
{
    /* stub */
    return 0;
}

void CCBRoleState::RandSetStateInInitApp()
{
    /* stub */
}

unsigned long CCBRoleState::GetBestRoleCureSpecStateItem(int nRoleIndex, ECBRoleSpecState eSpecState, uchar bGreat)
{
    /* stub */
    return 0;
}

unsigned long CCBRoleState::GetBestRoleAttackSkill(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

void CCBRoleState::FillSkillList(int nRoleIndex)
{
    /* stub */
}

bool CCBRoleState::IsAllEnemyDead(uchar bCheckHP)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::CanUseCallupMagic()
{
    /* stub */
    return FALSE;
}

void CCBRoleState::InitRoleFiveMagic()
{
    /* stub */
}

unsigned long CCBRoleState::GetBestRoleRecoverMagic(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

unsigned long CCBRoleState::GetBestRoleAttackMagic(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsGemHaveLeftUseTime(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::ConvertSpecMagic(ulong dwMagicID)
{
    /* stub */
    return 0;
}

void CCBRoleState::InitRoleSpecEquipAttrib(int nRoleIndex, int nSpecAffectIndex)
{
    /* stub */
}

void CCBRoleState::SetDefence(int nRoleIndex, uchar bDefence)
{
    /* stub */
}

bool CCBRoleState::CoAttackDamage(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetRoleAttack(int nRoleIndex)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsTrickCommonCostOK(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::CanBeSelect(tagCmdData * pCmd, int nDestRole)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::IsRecoverMagic(ulong dwMagicID)
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::GetBestRoleRecoverItem(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

void CCBRoleState::GetRoleEnglishName(int nRoleIndex, char * pInString)
{
    /* stub */
}

void CCBRoleState::UnloadWeaponModel()
{
    /* stub */
}

int CCBRoleState::CalEXP(int nLevel)
{
    /* stub */
    return 0;
}

void CCBRoleState::CancelPXVariance(int nRoleIndex, uchar bDead)
{
    /* stub */
}

int CCBRoleState::ItemAffect(tagCmdData * pCmd, int nDestRole)
{
    /* stub */
    return 0;
}

void CCBRoleState::CheckVarianceRound(int nRoleIndex)
{
    /* stub */
}

void CCBRoleState::CheckState()
{
    /* stub */
}

int CCBRoleState::CalLevel(int nEXP)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetSkillDamage(ulong dwSrc, ulong dwDest, ulong dwParam)
{
    /* stub */
    return 0;
}

void CCBRoleState::CreateMonster(int nRoleIndex, ulong dwMonsterID)
{
    /* stub */
}

ECBMagicKind CCBRoleState::GetEMagicKind(FightSkill * pFS)
{
    /* stub */
    return (ECBMagicKind)0;
}

bool CCBRoleState::GetDefence(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::Update()
{
    /* stub */
}

int CCBRoleState::GetBestNormalAttackInitPos(tagCmdData * pCmd, int * nPos1, int * nPos2)
{
    /* stub */
    return 0;
}

int CCBRoleState::CoAttackAffect(tagCmdData * pCmd, int nDestRole)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsRoleInSpecState(int nRoleIndex, ECBRoleSpecState state)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::SetCanAction(int nIndex, uchar bCanAction)
{
    /* stub */
}

void CCBRoleState::GetMagicSuffix(int nIndex, ulong dwMagicID, int * nKind, int * nMagic)
{
    /* stub */
}

bool CCBRoleState::Create()
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::GetBestRoleCureSpecStateSkill(int nRoleIndex, ECBRoleSpecState eSpecState, uchar bGreat)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetBestAttacker(ECBForce force)
{
    /* stub */
    return 0;
}

void CCBRoleState::HandleChongLouAnamo(int nRoleIndex)
{
    /* stub */
}

int CCBRoleState::GetDeadRoleNumInForce(ECBForce force)
{
    /* stub */
    return 0;
}

int CCBRoleState::CalFullMP(int nRoleIndex, int nLevel)
{
    /* stub */
    return 0;
}

void CCBRoleState::GetFightSkillRange(tagCmdData * pCmd)
{
    /* stub */
}

int CCBRoleState::MagicAffect(tagCmdData * pCmd, int nDestRole)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsReviveFightSkill(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::PreHandlePXVariance(int nRoleIndex)
{
    /* stub */
}

unsigned long CCBRoleState::GetBadMagicForEnemy(int nRoleIndex)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetMagicUseTime(int nRoleIndex, ECBMagicKind eMagicKind)
{
    /* stub */
    return 0;
}

void CCBRoleState::FillParabolaItemList(int nRoleIndex)
{
    /* stub */
}

int CCBRoleState::GetInBadSpecStateRoleNum(ECBForce force)
{
    /* stub */
    return 0;
}

unsigned long CCBRoleState::GetSkillIDInList(int nRoleIndex, int nSkillIndex)
{
    /* stub */
    return 0;
}

bool CCBRoleState::CanProtect(int nDestRole)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::CalFullAttack(int nRoleIndex, int nLevel)
{
    /* stub */
    return 0;
}

bool CCBRoleState::ItemDamage(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::IsAllWeDead(uchar bCheckHP)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::RandSetEnemyPos()
{
    /* stub */
}

void CCBRoleState::SortFriendFightSkill()
{
    /* stub */
}

int CCBRoleState::GetCoAttackPower(tagCmdData * pCmd, int nDestRole)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetBestRoleForAttackRowOrCol(uchar bRow, uchar bGetEnemy)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetNormalSpecStateRoleNum(ECBForce force)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetHP(int nRoleIndex, uchar bGetFullValue)
{
    /* stub */
    return 0;
}

bool CCBRoleState::HasUnmovableRoleInLineup(ECBFiveLineup lineup)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::IsRoleInColumn(int nRoleIndex1, int nRoleIndex2)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetPunchyAttackDamage(ulong dwSrc, ulong dwDest, ulong dwParam)
{
    /* stub */
    return 0;
}

ECBRSHPState CCBRoleState::GetHPState(int nRoleIndex)
{
    /* stub */
    return (ECBRSHPState)0;
}

bool CCBRoleState::IsHaveSpecifyMagic(int nRoleIndex, ulong dwMagicID)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetDefenceFiveMagic(int nIndex, ECBFiveMagic fm)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetRoleSpeed(int nRoleIndex)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsDestRoleAllDead(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::IsRoleInRow(int nRoleIndex1, int nRoleIndex2)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::CheckRoleNimbus(int nRoleIndex)
{
    /* stub */
    return 0;
}

ECBForce CCBRoleState::GetRoleForce(int nRoleIndex)
{
    /* stub */
    return (ECBForce)0;
}

bool CCBRoleState::AttackDamage(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetRoleMagicLevel(int nRoleIndex, ulong dwMagicID)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsCureSpecStateFightSkill(tagCmdData * pCmd, ECBRoleSpecState eSpecState)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::SkillDamage(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::CalCombatResult(uchar bFirst, int nTaskIndex)
{
    /* stub */
}

bool CCBRoleState::IsDestRole(tagCmdData * pCmd, int nRoleIndex)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetItemAttackPower(int nRoleIndex, ulong dwItemID)
{
    /* stub */
    return 0;
}

bool CCBRoleState::GetCastFightSkillSuccess(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::HasBFAMagic(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::Init()
{
    /* stub */
    return FALSE;
}

void CCBRoleState::ChangeLove(int nRoleIndex, int nValue)
{
    /* stub */
}

bool CCBRoleState::SetRoleRandPoison(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::CheckPerRound(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::GetRoleNum()
{
    /* stub */
    return 0;
}

bool CCBRoleState::CanRemoveSpecState(int nRoleIndex, ECBRoleSpecState state)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::CalSneakAttack()
{
    /* stub */
}

int CCBRoleState::GetRoleDefence(int nRoleIndex)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetLowHPRoleNum(ECBForce force)
{
    /* stub */
    return 0;
}

int CCBRoleState::ChangeGP(int nRoleIndex, int nValue, uchar bShowNum)
{
    /* stub */
    return 0;
}

int CCBRoleState::ChangeMP(int nRoleIndex, int nValue, uchar bShowNum)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsAttackSkill(ulong dwSkillID)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::ChangeHP(int nRoleIndex, int nValue, uchar bShowAction, int nAttacker, uchar bForce)
{
    /* stub */
    return 0;
}

ECBFiveLineup CCBRoleState::GetLineup(int nIndex)
{
    /* stub */
    return (ECBFiveLineup)0;
}

void CCBRoleState::HandleUncontrolableState(int nRoleIndex)
{
    /* stub */
}

void CCBRoleState::ChangeMoney(int nRoleIndex, int nValue)
{
    /* stub */
}

bool CCBRoleState::IsRoleMasteredTrick(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::CalFullDefence(int nRoleIndex, int nLevel)
{
    /* stub */
    return 0;
}

bool CCBRoleState::HasDestRole(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::WeaponSkillDamage(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::TransferGP(int nRoleLost, int nRoleGet, int nValue)
{
    /* stub */
}

void CCBRoleState::HandleNewMonster(int nSrcRole, int nDestRole)
{
    /* stub */
}

bool CCBRoleState::IsFriend(int nIndex)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::ChangeSpecState(tagCmdData * pCmd, int nRoleIndex)
{
    /* stub */
}

void CCBRoleState::WriteBackConfig()
{
    /* stub */
}

int CCBRoleState::GetPoisonedRoleNum(ECBForce force)
{
    /* stub */
    return 0;
}

void CCBRoleState::InitUI()
{
    /* stub */
}

int CCBRoleState::GetAttackFiveMagic(int nIndex, ECBFiveMagic fm)
{
    /* stub */
    return 0;
}

CCBRoleState::~CCBRoleState()
{
    /* stub */
}

int CCBRoleState::GetMP(int nRoleIndex, uchar bGetFullValue)
{
    /* stub */
    return 0;
}

void CCBRoleState::SetEnemyBeImbibeNimbus()
{
    /* stub */
}

int CCBRoleState::GetForceAverageDamageHP(ECBForce force, uchar bIncludeDead)
{
    /* stub */
    return 0;
}

int CCBRoleState::GetRoleIndexFormID(ulong dwRoleID)
{
    /* stub */
    return 0;
}

int CCBRoleState::CalFiveMagic(ulong dwSrc, ulong dwDest, ulong dwParam)
{
    /* stub */
    return 0;
}

ECBFiveMagic CCBRoleState::GetPunyFiveMagic(ECBFiveMagic fm)
{
    /* stub */
    return (ECBFiveMagic)0;
}

bool CCBRoleState::IsMultiTargetFightSkill(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

void CCBRoleState::TransferMP(int nRoleLost, int nRoleGet, int nValue)
{
    /* stub */
}

CCBRoleState::CCBRoleState(CCBSystem * pCBSystem)
{
    /* stub */
}

int CCBRoleState::FixFormula(ECBFixFormula f, int nSrcRole, int nDestRole, int n1, ulong dw1)
{
    /* stub */
    return 0;
}

bool CCBRoleState::DamageImmediate(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}

unsigned long CCBRoleState::GetBestRoleReviveMagic(int nRoleIndex, uchar bGreat, int nWeight)
{
    /* stub */
    return 0;
}

void CCBRoleState::TransferHP(int nRoleLost, int nRoleGet, int nValue)
{
    /* stub */
}

ECBRoleSpecState CCBRoleState::GetRoleWorstSpecState(int nRoleIndex)
{
    /* stub */
    return (ECBRoleSpecState)0;
}

bool CCBRoleState::IsSameFiveMagic(ECBFiveMagic fm, ECBFiveLineup fl)
{
    /* stub */
    return FALSE;
}

int CCBRoleState::CalFullHP(int nRoleIndex, int nLevel)
{
    /* stub */
    return 0;
}

bool CCBRoleState::IsHaveCallupMagic(int nRoleIndex)
{
    /* stub */
    return FALSE;
}

bool CCBRoleState::IsRoleTrick(tagCmdData * pCmd)
{
    /* stub */
    return FALSE;
}


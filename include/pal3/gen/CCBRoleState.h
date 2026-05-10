#pragma once
// Auto-generated: CCBRoleState

#include "ECBFiveLineup.h"
#include "tagRoleState.h"

class CCBStage;
class CCBSystem;
class CCBUI;
class CUtil;

class CCBRoleState {
public:
    char m_sCombatDialog[512]; // +0x0
    float m_fLastDialogTime; // +0x200
    BYTE m_bCombatDialog; // +0x204
    CCBSystem * m_pCBSystem; // +0x208
    CCBStage * m_pStage; // +0x20C
    CCBUI * m_pUI; // +0x210
    CUtil * m_pUtil; // +0x214
    BYTE m_bWeSneakAttackEnemy; // +0x218
    BYTE m_bEnemySneakAttackUs; // +0x219
    int m_nMaxRound; // +0x21C
    int m_nBossRound; // +0x220
    BYTE m_bMustFail; // +0x224
    BYTE m_bFleeAlwaysSuccess; // +0x225
    BYTE m_bCreatedNewRole; // +0x226
    tagRoleState m_Role[11]; // +0x228
    tagRoleState m_RoleXor[11]; // +0x2ED8
    DWORD m_dwEXPTable[100]; // +0x5B88
    DWORD m_dwWinTaskID; // +0x5D18
    int m_bNGHDeadVariance; // +0x5D1C
    ECBFiveLineup m_eSameRow[3][3]; // +0x5D20
    ECBFiveLineup m_eSameColumn[2][3]; // +0x5D44
    float m_fSwordStarTime; // +0x5D5C
    // total size: 0x5D60 (23904)

    int Update(); // 0x004ECB00
    char IsRoleAlive(int roleIdx); // 0x004ED010
    char GetRoleType(int roleIdx); // 0x004ED060
    int GetForce(int roleIdx); // 0x004ED100
    CCBRoleState(); // 0x004EDD60
    char _CCBRoleState(); // 0x004EDF10
    float * Reset(int a2, float *a3); // 0x004EE430
    char Create(); // 0x004EE540
    int Destroy(); // 0x004EE760
    int Init(int a2, char a3); // 0x004EE7C0
    int InitUI(int a2); // 0x004EE870
    int Update(int roleIdx); // 0x004EE890
    bool VarianceRoundCounter(_DWORD *a2); // 0x004EE990
    char CheckVarianceRound(int a2, int a3, int *a4); // 0x004EEA70
    char CancelVariance(_DWORD *a2, unsigned int a3); // 0x004EECB0
    char IsAlive(int a2, int a3); // 0x004EEE60
    void IsBoss(_DWORD *arg0, unsigned int a2); // 0x004EF4A0
    int IsAllWeDead(int a2); // 0x004EF6A0
    static _DWORD * IsAllEnemyDead(int a2, int *arg4, int *a3); // 0x004EF6C0
    int CanAction(int a2, int a3, int a4); // 0x004EF710
    int SetCanAction(unsigned int dmg, int roleIdx, int a4); // 0x004EF7E0
    char RandSetEnemyPos(const void *arg0); // 0x004EF8B0
    int CalcHealAmount(int roleIdx); // 0x004EF980
    int WriteBackRoleData(int a2, _DWORD *a3, int *a4); // 0x004EFAF0
    bool WriteBackConfig(int roleIdx, int a3); // 0x004EFD70
    bool ReviveAllFriendAtEnd(int roleIdx, int a3); // 0x004EFE90
    bool IsRoleReady(int roleIdx); // 0x004EFFC0
    int SetEnemyBeImbibeNimbus(char a2, char a3); // 0x004F0020
    bool CalSneakAttack(int a2, unsigned int a3); // 0x004F0210
    unsigned int InitRoleFiveMagic(int a2); // 0x004F0360
    static char sub_4F05A0(_DWORD *a1); // 0x004F05A0
    bool InitRoleSpecEquipAttrib(int a2); // 0x004F0640
    char UnloadWeaponModel(int a2); // 0x004F0700
    bool SetVisible(int roleIdx); // 0x004F0750
    static char GetRole(int a1, int a2); // 0x004F07D0
    unsigned __int8 GetRoleNum(int *a2); // 0x004F0830
    char GetAliveRoleNumInForce(int a2); // 0x004F1070
    char GetDeadRoleNumInForce(int a2); // 0x004F1420
    char GetFirstAliveRoleInForce(int roleIdx, int arg4); // 0x004F17C0
    char GetCastFightSkillSuccess(int a2); // 0x004F1A30
    char SetCoAttack(int a2); // 0x004F1B20
    char CanBeImbibeNimbus(int arg0, unsigned int a2); // 0x004F1CC0
    char CheckRoleValid(int a2, unsigned int roleIdx, int a4); // 0x004F1FA0
    char CheckRoleNimbus(int a2, unsigned int a3); // 0x004F2310
    char CanBeSelect(int a2, unsigned int a3); // 0x004F2350
    int SetRoleHP(int roleIdx, int value); // 0x004F2910
    int SetRoleField(int roleIdx, int value); // 0x004F2BB0
    int CalcAttackPower(int roleIdx); // 0x004F3020
    int CalcDefensePower(int roleIdx); // 0x004F31C0
    int GetMaxHP(int roleIdx); // 0x004F3380
    int GetMaxMP(int roleIdx); // 0x004F33D0
    int GetTotalRounds(); // 0x004F3420
    char CheckBuff(int roleIdx); // 0x004F3430
    char CanUseSkill(int roleIdx); // 0x004F34E0
    int CalcMagicAttack(int roleIdx); // 0x004F3570
    int CalcMPRegen(int roleIdx); // 0x004F3620
    int CalcMagicDefense(int roleIdx); // 0x004F36D0
    int GetAttackBonus(int roleIdx); // 0x004F37A0
    int GetDefenseBonus(int roleIdx); // 0x004F3820
    int GetRoleState(int roleIdx); // 0x004F38A0
    int GetSpeedBonus(int roleIdx); // 0x004F3920
    int GetRoleLevel(int roleIdx); // 0x004F39A0
    int GetRoleExp(int roleIdx); // 0x004F39F0
    char SetRoleFlag(int roleIdx, char flag); // 0x004F3A30
    int GetRoleAttr(int roleIdx); // 0x004F3A50
    int CalcMPCost(int roleIdx); // 0x004F3AD0
    int GetRoleMP(int roleIdx); // 0x004F3B90
    int GetRoleHP(int roleIdx); // 0x004F3BC0
    static int IsForce1(int force); // 0x004F3C00
    static char IsPlayerTeam(int force); // 0x004F3C20
    char GetRoleForce(int roleIdx); // 0x004F3C70
    bool IsRoleInForce(int roleIdx); // 0x004F3CC0
    char CanRoleAct(int roleIdx); // 0x004F3D10
    char GetRoleField(int roleIdx, int fieldOff); // 0x004F3D90
    int GetRoleSpeed(int roleIdx); // 0x004F3DC0
    char ProcessRound(unsigned int a2); // 0x004F3E20
    int ProcessAttackResult(int roleIdx); // 0x004F4DA0
    int ProcessMagicResult(int roleIdx); // 0x004F5070
    int CalcPhysicalDamage(int roleIdx); // 0x004F55D0
    int CalcMagicDamage(int roleIdx); // 0x004F57A0
    int ProcessSkillEffect(int roleIdx); // 0x004F5970
    int ProcessItemEffect(int roleIdx); // 0x004F5B70
    char GetRoleAI(void *pOut); // 0x004F7500
    unsigned int CheckStatus(); // 0x004F7880
    void * ProcessActions(); // 0x004F7910
    int UpdateEffects(); // 0x004F8480
    int ApplyDamage(int roleIdx, int dmg); // 0x004F98B0
    int CheckRoleStatus(int roleIdx); // 0x004FA540
    int CheckDeath(int roleIdx); // 0x004FA6A0
    int Revive(int roleIdx); // 0x004FA8B0
};

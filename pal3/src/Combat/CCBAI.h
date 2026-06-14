#pragma once
// Auto-generated: CCBAI

#include "tagDemand.h"
#include "tagVA.h"
#include "tagVAF.h"
#include "tagVAO.h"

class CCBRoleState;
class CCBSystem;
class CUtil;

class CCBAI {
public:
    _BYTE m_bNewRole[11]; // +0x0
    char _gap_00B[1]; // +0xB
    CCBSystem * m_pCBSystem; // +0xC
    CCBRoleState * m_pRoleState; // +0x10
    CUtil * m_pUtil; // +0x14
    tagVA m_VA; // +0x18
    char _gap_01C[20]; // +0x1C
    tagVAO m_VAO[32]; // +0x30
    char _gap_0B0[384]; // +0xB0
    tagVAF m_VAF[32]; // +0x230
    char _gap_2B0[896]; // +0x2B0
    tagDemand m_Demand[10][11]; // +0x630
    char _gap_7E8[1320]; // +0x7E8
    tagDemand m_EnemyDemand[5]; // +0xD10
    char _gap_D24[60]; // +0xD24
    int m_nDemandThreadTracer; // +0xD60
    char _gap_D64[4]; // +0xD64
    BYTE m_bDemandThreadTracer; // +0xD68
    char _gap_D69[71]; // +0xD69
    tagDemand m_FriendDemand[5]; // +0xDB0
    char _gap_DC4[60]; // +0xDC4
    int m_nHandleEnemyWell; // +0xE00
    char _gap_E04[4]; // +0xE04
    BYTE _todo_E08; // +0xE08
    char _tail_E09[71]; // +0xE09
    // total size: 0xE50 (3664)

    void * GetTargetRole(void *pOut); // 0x0040CFE0
    CCBAI(); // 0x004D6FF0
    void _CCBAI(); // 0x004D7030
    void Reset(); // 0x004D7040
    CCBAI * Create(int *p_DWORD); // 0x004D7080
    bool Init(); // 0x004D70C0
    void Update(); // 0x004D7100
    void Render(int nVal); // 0x004D7120
    bool HandleEnemyAction(int nRoleIndex); // 0x004D71E0
    bool HandleEnemyWell(int nRoleIndex); // 0x004D7820
    bool HandleEnemyWeak(int nRoleIndex); // 0x004D7EF0
    void ChooseRandomAction(int nSelfIdx); // 0x004D8580
    bool HandleEnemyChaos(int nRoleIndex); // 0x004D86D0
    bool HandleFriendAction(int nRoleIndex); // 0x004D8760
    bool HandleFriendNegative(int nRoleIndex); // 0x004D8AF0
    bool HandleFriendAffirmative(int nRoleIndex, char pData); // 0x004D8F20
    bool HandlePlayerNormalAttack(int nRoleIndex, int bPlayerCmd); // 0x004D9130
    void * RepeatPlayerLastOperation(); // 0x004D9360
    int * SetNewRole(); // 0x004D9380
    void FillAllDemandSatisfy(); // 0x004D93D0
    void DemandThreadTracer(); // 0x004D94F0
    void DemandChecker(unsigned int dwVal, int nVal, int nVal2); // 0x004D9740
    bool CastNormalAttack(int nRoleIndex, int nDestRole, int pDemand); // 0x004D9920
    bool CastRecoverMagic(int nRoleIndex, int nDestRole); // 0x004D9A70
    bool CastRecoverBigMagic(int nRoleIndex, int pDemand, int nVal); // 0x004D9BA0
    bool CastAttackMagic(int nRoleIndex, int nDestRole); // 0x004D9D00
    bool CastAttackBigMagic(int nRoleIndex, int pDemand); // 0x004D9E20
    bool CastSpecifyMagic(int nRoleIndex, int nDestRole, int dwID); // 0x004D9F50
    bool CastBFAMagic(int nRoleIndex, int nDestRole); // 0x004DA0A0
    bool CastBFAAttackMagic(int nRoleIndex, int pDemand, int nVal); // 0x004DA1D0
    bool CastRandEnemyMagic(int nRoleIndex, int nDestRole); // 0x004DA350
    bool CastRecoverSkill(int nRoleIndex, int nDestRole, int pDemand); // 0x004DA4F0
    bool CastRecoverBigSkill(int nRoleIndex, int pDemand); // 0x004DA640
    bool CastAttackSkill(int nRoleIndex, int nDestRole, int pDemand); // 0x004DA770
    bool CastAttackBigSkill(int nRoleIndex, int pDemand); // 0x004DA900
    bool CastRecoverItem(int nRoleIndex, int nDestRole, int pDemand); // 0x004DAA40
    bool CastRecoverBigItem(int nRoleIndex, int pDemand, int nVal); // 0x004DAB70
    bool CastAttackItem(int nRoleIndex, int nDestRole, int pDemand); // 0x004DACA0
    bool CastAttackBigItem(int nRoleIndex, int pDemand, int nVal); // 0x004DADD0
    bool CastBossPhysicalAttack(int nRoleIndex, int pDemand, int nVal); // 0x004DAF00
    bool CastReviveMagic(int nRoleIndex, int nDestRole, int pDemand); // 0x004DB030
    bool CastReviveSkill(int nRoleIndex); // 0x004DB160
    bool CastCureSpecStateMagic(); // 0x004DB270
    bool CastCureSpecStateSkill(); // 0x004DB280
    void CastCureSpecStateItem(); // 0x004DB290
    void HasVeryPunyFiveMagicRole(); // 0x004DB2A0
    bool CreateValueAutomation(); // 0x004DB2B0
    bool AddValueFunction(); // 0x004DB2C0
    bool AddValueItem(int nData, unsigned int dwData); // 0x004DB300
    bool DestroyValueAutomation(); // 0x004DB310
    int RunValueAutomation(); // 0x004DB350
    bool SpecAI(); // 0x004DB360
};

#ifndef PAL3A_CBAI_H
#define PAL3A_CBAI_H

#include "pal3a_types.h"

class CCBAI {
public:
    char _data[3664];

    bool CastBFAAttackMagic(int nRoleIndex, tagDemand * pDemand);
    bool CastReviveItem(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool CastRecoverMagic(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool HandleEnemyAction(int nRoleIndex);
    bool CastRecoverBigMagic(int nRoleIndex, tagDemand * pDemand);
    bool RepeatPlayerLastOperation(int nRoleIndex, tagCmdData * pCmd);
    bool CastRecoverItem(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool Destroy();
    bool HandleEnemyWeak(int nRoleIndex);
    bool CastAttackBigSkill(int nRoleIndex, tagDemand * pDemand);
    bool CastSpecifyMagic(int nRoleIndex, int nDestRole, ulong dwID);
    bool CastAttackMagic(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    ~CCBAI();
    bool HandleEnemyLow(int nRoleIndex);
    bool DestroyValueAutomation();
    bool CastAttackItem(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool HandleFriendNegative(int nRoleIndex);
    bool HandleFriendAction(int nRoleIndex);
    bool CastNormalAttack(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool CastCureSpecStateItem(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    void Render();
    bool HandleEnemyWell(int nRoleIndex);
    bool CastRecoverBigItem(int nRoleIndex, tagDemand * pDemand);
    void DemandThreadTracer();
    void DemandChecker();
    bool CastCureSpecStateMagic(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool Init();
    CCBAI(CCBSystem * pCBSystem);
    bool CastReviveMagic(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool AddValueItem(int nData, ulong dwData);
    bool SpecAI(int nRoleIndex);
    bool CastRandEnemyMagic(int nRoleIndex, int nDestRole);
    bool CastReviveSkill(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool CastCureSpecStateSkill(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool HandlePlayerNormalAttack(int nRoleIndex, uchar bPlayerCmd);
    void Update();
    bool CastBossPhysicalAttack(int nRoleIndex, tagDemand * pDemand);
    bool HandleEnemyChaos(int nRoleIndex);
    void Reset();
    void SetNewRole();
    void FillAllDemandSatisfy();
    bool CastRecoverSkill(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool CastAttackSkill(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool Create();
    bool HandleFriendAffirmative(int nRoleIndex);
    bool CreateValueAutomation(ECBVAKind eKind, int nSrc, int nDest);
    bool CastAttackBigItem(int nRoleIndex, tagDemand * pDemand);
    int RunValueAutomation();
    bool CastRecoverBigSkill(int nRoleIndex, tagDemand * pDemand);
    bool AddValueFunction(void * fp, int nScore, uchar bDecision);
    bool CastBFAMagic(int nRoleIndex, int nDestRole, tagDemand * pDemand);
    bool CastAttackBigMagic(int nRoleIndex, tagDemand * pDemand);
    bool HasVeryPunyFiveMagicRole(ECBForce EnemyForce, ECBForce FriendForce);
};

#endif // PAL3A_CBAI_H

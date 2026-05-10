#pragma once
// Auto-generated: tagRoleState

#include "ECBFiveLineup.h"

class tagRoleState {
public:
    DWORD dwID; // +0x0
    int nIndex; // +0x4
    char sModel[16]; // +0x8
    BYTE byUIIndex; // +0x18
    BYTE bValid; // +0x19
    BYTE bAlive; // +0x1A
    BYTE bFriend; // +0x1B
    BYTE bBoss; // +0x1C
    BYTE bCanAction; // +0x1D
    BYTE bWaitForFlee; // +0x1E
    BYTE bEnemyFriend; // +0x1F
    int nLevel; // +0x20
    int nHP; // +0x24
    int nFullHP; // +0x28
    int nGP; // +0x2C
    int nFullGP; // +0x30
    int nMP; // +0x34
    int nFullMP; // +0x38
    int nAttack; // +0x3C
    int nDefence; // +0x40
    int nSpeed; // +0x44
    int nLuck; // +0x48
    int nLove; // +0x4C
    int nMoney; // +0x50
    int nProtectRole; // +0x54
    DWORD dwAttackMode; // +0x58
    int nGPInc; // +0x5C
    BYTE byWeaponType; // +0x60
    BYTE bAttackRow; // +0x61
    BYTE bAttackColumn; // +0x62
    BYTE bAttackAll; // +0x63
    BYTE bMagicSword; // +0x64
    float fGPCostDec; // +0x68
    float fMPCostDec; // +0x6C
    float fPunchPowerInc; // +0x70
    float fSkillCentInc; // +0x74
    float fHPIncPerRound; // +0x78
    float fGPIncPerRound; // +0x7C
    float fGPIncPerRoundBak; // +0x80
    float fMPIncPerRound; // +0x84
    float fEXPIncPerCombat; // +0x88
    float fMoneyIncPerCombat; // +0x8C
    float fRecoverItemPowerInc; // +0x90
    int nStealCent; // +0x94
    BYTE bLostMoneyGetLife; // +0x98
    BYTE bMirror; // +0x99
    int nEXP; // +0x9C
    int nCombatEXP; // +0xA0
    DWORD dwSkillID[9]; // +0xA4
    BYTE bSkillMastered[9]; // +0xC8
    DWORD dwMagicID[9][6]; // +0xD4
    BYTE bMagicMastered[9][6]; // +0x1AC
    WORD byMagicUseTime[9][6]; // +0x1E2
    BYTE byMagicLevel[9][6]; // +0x24E
    DWORD dwWeaponSkillID; // +0x284
    DWORD dwCleanCent; // +0x288
    float fWeaponSkillMass; // +0x28C
    DWORD dwCorpse; // +0x290
    int nMoneyCanBeSteal; // +0x294
    DWORD dwItemCanBeSteal; // +0x298
    int nItemCanBeSteal; // +0x29C
    DWORD dwFiveMagic[7]; // +0x2A0
    ECBFiveLineup Lineup; // +0x2BC
    BYTE bDefence; // +0x2C0
    BYTE bSpecState[27]; // +0x2C1
    short snSpecStateLurk[27]; // +0x2DC
    short snSpecStateLast[27]; // +0x312
    int nSpecStateRound[27]; // +0x348
    BYTE bAIAttack; // +0x3B4
    BYTE bAIMagic; // +0x3B5
    BYTE bAISkill; // +0x3B6
    BYTE bAIUseItem; // +0x3B7
    BYTE bAINegative; // +0x3B8
    BYTE bAI; // +0x3B9
    BYTE bAbsorbHPWorm; // +0x3BA
    BYTE byAbsorbHPWormRound; // +0x3BB
    int nKiller; // +0x3BC
    float fDeadTime; // +0x3C0
    BYTE bDeadImbibeNimbus; // +0x3C4
    BYTE bVariance; // +0x3C5
    BYTE bVarianceRun; // +0x3C6
    int nBeforeVarianceHP; // +0x3C8
    int nBeforeVarianceFullHP; // +0x3CC
    int nBeforeVarianceDef; // +0x3D0
    int nCurVarianceRound; // +0x3D4
    int nMaxVarianceRound; // +0x3D8
    int nBFARound; // +0x3DC
    int nMaxBFARound; // +0x3E0
    gbGeomNode * pLeftWeapon[3]; // +0x3E4
    gbGeomNode * pRightWeapon[3]; // +0x3F0
    int nRound; // +0x3FC
    BYTE bRepeatLastOperation; // +0x400
    BYTE bDoNormalAttack; // +0x401
    BYTE bDoFlee; // +0x402
    BYTE bTransMtl; // +0x403
    BYTE bFleeing; // +0x404
    BYTE bFleed; // +0x405
    int nFleeCent; // +0x408
    char * pHPSign; // +0x40C
    // total size: 0x410 (1040)

};

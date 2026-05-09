#pragma once
// Auto-generated: tagRoleState

#include "ECBFiveLineup.h"

class gbGeomNode;

class tagRoleState {
public:
    unsigned long dwID; // +0x0
    int nIndex; // +0x4
    char sModel[16]; // +0x8
    unsigned char byUIIndex; // +0x18
    unsigned char bValid; // +0x19
    unsigned char bAlive; // +0x1A
    unsigned char bFriend; // +0x1B
    unsigned char bBoss; // +0x1C
    unsigned char bCanAction; // +0x1D
    unsigned char bWaitForFlee; // +0x1E
    unsigned char bEnemyFriend; // +0x1F
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
    unsigned long dwAttackMode; // +0x58
    int nGPInc; // +0x5C
    unsigned char byWeaponType; // +0x60
    unsigned char bAttackRow; // +0x61
    unsigned char bAttackColumn; // +0x62
    unsigned char bAttackAll; // +0x63
    unsigned char bMagicSword; // +0x64
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
    unsigned char bLostMoneyGetLife; // +0x98
    unsigned char bMirror; // +0x99
    int nEXP; // +0x9C
    int nCombatEXP; // +0xA0
    unsigned long dwSkillID[9]; // +0xA4
    unsigned char bSkillMastered[9]; // +0xC8
    unsigned long dwMagicID[9][6]; // +0xD4
    unsigned char bMagicMastered[9][6]; // +0x1AC
    unsigned short byMagicUseTime[9][6]; // +0x1E2
    unsigned char byMagicLevel[9][6]; // +0x24E
    unsigned long dwWeaponSkillID; // +0x284
    unsigned long dwCleanCent; // +0x288
    float fWeaponSkillMass; // +0x28C
    unsigned long dwCorpse; // +0x290
    int nMoneyCanBeSteal; // +0x294
    unsigned long dwItemCanBeSteal; // +0x298
    int nItemCanBeSteal; // +0x29C
    unsigned long dwFiveMagic[7]; // +0x2A0
    ECBFiveLineup Lineup; // +0x2BC
    unsigned char bDefence; // +0x2C0
    unsigned char bSpecState[27]; // +0x2C1
    short snSpecStateLurk[27]; // +0x2DC
    short snSpecStateLast[27]; // +0x312
    int nSpecStateRound[27]; // +0x348
    unsigned char bAIAttack; // +0x3B4
    unsigned char bAIMagic; // +0x3B5
    unsigned char bAISkill; // +0x3B6
    unsigned char bAIUseItem; // +0x3B7
    unsigned char bAINegative; // +0x3B8
    unsigned char bAI; // +0x3B9
    unsigned char bAbsorbHPWorm; // +0x3BA
    unsigned char byAbsorbHPWormRound; // +0x3BB
    int nKiller; // +0x3BC
    float fDeadTime; // +0x3C0
    unsigned char bDeadImbibeNimbus; // +0x3C4
    unsigned char bVariance; // +0x3C5
    unsigned char bVarianceRun; // +0x3C6
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
    unsigned char bRepeatLastOperation; // +0x400
    unsigned char bDoNormalAttack; // +0x401
    unsigned char bDoFlee; // +0x402
    unsigned char bTransMtl; // +0x403
    unsigned char bFleeing; // +0x404
    unsigned char bFleed; // +0x405
    int nFleeCent; // +0x408
    char * pHPSign; // +0x40C
    // total size: 0x410 (1040)

};

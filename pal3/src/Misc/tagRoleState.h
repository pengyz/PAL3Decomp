#pragma once
// Auto-generated: tagRoleState

class CCBStage;
class CCBSystem;

class tagRoleState {
public:
    UINT dwID; // +0x0
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
    CCBSystem * pCCBSystem; // +0x30
    CCBStage * nMP; // +0x34
    int nFullMP; // +0x38
    int nAttack; // +0x3C
    int nDefence; // +0x40
    int nSpeed; // +0x44
    int nLuck; // +0x48
    int nLove; // +0x4C
    int nMoney; // +0x50
    int nProtectRole; // +0x54
    UINT dwAttackMode; // +0x58
    int nGPInc; // +0x5C
    BYTE byWeaponType; // +0x60
    BYTE bAttackRow; // +0x61
    BYTE bAttackColumn; // +0x62
    BYTE bAttackAll; // +0x63
    BYTE bMagicSword; // +0x64
    char _gap_065[3]; // +0x65
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
    char _gap_09A[2]; // +0x9A
    int nEXP; // +0x9C
    int nCombatEXP; // +0xA0
    UINT dwSkillID[9]; // +0xA4
    _BYTE bSkillMastered[9]; // +0xC8
    char _gap_0D1[3]; // +0xD1
    UINT dwMagicID[9][6]; // +0xD4
    _BYTE bMagicMastered[9][6]; // +0x1AC
    WORD byMagicUseTime[9][6]; // +0x1E2
    char _tail_24E[10]; // +0x24E
    // total size: 0x258 (600)

};

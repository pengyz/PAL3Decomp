#include "RoleAtt.h"
#pragma once
// Auto-generated: PlayerAtt

#include "PlayerItem.h"

class PlayerAtt : public RoleAtt {
public:
    char _gap_000[852]; // +0x0
    PlayerItem hat; // +0x354
    char _gap_358[8]; // +0x358
    PlayerItem cloth; // +0x360
    char _gap_364[8]; // +0x364
    PlayerItem shoes; // +0x36C
    char _gap_370[8]; // +0x370
    PlayerItem wear[2]; // +0x378
    char _gap_380[16]; // +0x380
    PlayerItem weapon; // +0x390
    char _gap_394[8]; // +0x394
    int maxrolevalue[12]; // +0x39C
    int currolevalue[12]; // +0x3CC
    int nProtectRole; // +0x3FC
    UINT dwWeaponSkillID; // +0x400
    UINT dwCleanCent; // +0x404
    float fWeaponSkillMass; // +0x408
    UINT dwSkillID[9]; // +0x40C
    _BYTE bSkillMastered[9]; // +0x430
    char _gap_439[3]; // +0x439
    UINT dwMagicID[9][6]; // +0x43C
    _BYTE bMagicMastered[9][6]; // +0x514
    WORD byMagicUseTime[9][6]; // +0x54A
    _BYTE byMagicLevel[9][6]; // +0x5B6
    BYTE bAutoCtrl; // +0x5EC
    BYTE bAIAttack; // +0x5ED
    BYTE bAIMagic; // +0x5EE
    BYTE bAISkill; // +0x5EF
    BYTE bAIUseItem; // +0x5F0
    BYTE bAINegative; // +0x5F1
    BYTE byLineup; // +0x5F2
    char _tail_5F3[1]; // +0x5F3
    // total size: 0x5F4 (1524)

    static void CheckCurRV(); // 0x0043A690
};

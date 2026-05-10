#pragma once
// Auto-generated: PlayerAtt

#include "PlayerItem.h"
#include "RoleAtt.h"

class PlayerAtt : public RoleAtt {
public:
    PlayerItem hat; // +0x354
    PlayerItem cloth; // +0x360
    PlayerItem shoes; // +0x36C
    PlayerItem wear[2]; // +0x378
    PlayerItem weapon; // +0x390
    int maxrolevalue[12]; // +0x39C
    int currolevalue[12]; // +0x3CC
    int nProtectRole; // +0x3FC
    DWORD dwWeaponSkillID; // +0x400
    DWORD dwCleanCent; // +0x404
    float fWeaponSkillMass; // +0x408
    DWORD dwSkillID[9]; // +0x40C
    BYTE bSkillMastered[9]; // +0x430
    DWORD dwMagicID[9][6]; // +0x43C
    BYTE bMagicMastered[9][6]; // +0x514
    WORD byMagicUseTime[9][6]; // +0x54A
    BYTE byMagicLevel[9][6]; // +0x5B6
    BYTE bAutoCtrl; // +0x5EC
    BYTE bAIAttack; // +0x5ED
    BYTE bAIMagic; // +0x5EE
    BYTE bAISkill; // +0x5EF
    BYTE bAIUseItem; // +0x5F0
    BYTE bAINegative; // +0x5F1
    BYTE byLineup; // +0x5F2
    // total size: 0x5F4 (1524)

};

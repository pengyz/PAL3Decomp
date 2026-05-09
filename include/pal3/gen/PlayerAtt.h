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
    unsigned long dwWeaponSkillID; // +0x400
    unsigned long dwCleanCent; // +0x404
    float fWeaponSkillMass; // +0x408
    unsigned long dwSkillID[9]; // +0x40C
    unsigned char bSkillMastered[9]; // +0x430
    unsigned long dwMagicID[9][6]; // +0x43C
    unsigned char bMagicMastered[9][6]; // +0x514
    unsigned short byMagicUseTime[9][6]; // +0x54A
    unsigned char byMagicLevel[9][6]; // +0x5B6
    unsigned char bAutoCtrl; // +0x5EC
    unsigned char bAIAttack; // +0x5ED
    unsigned char bAIMagic; // +0x5EE
    unsigned char bAISkill; // +0x5EF
    unsigned char bAIUseItem; // +0x5F0
    unsigned char bAINegative; // +0x5F1
    unsigned char byLineup; // +0x5F2
    // total size: 0x5F4 (1524)

};

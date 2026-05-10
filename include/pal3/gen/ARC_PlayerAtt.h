#pragma once
// Auto-generated: ARC_PlayerAtt

#include "ARC_PlayerItem.h"
#include "ARC_RoleAtt.h"

class ARC_PlayerAtt : public ARC_RoleAtt {
public:
    ARC_PlayerItem hat; // +0x354
    ARC_PlayerItem cloth; // +0x360
    ARC_PlayerItem shoes; // +0x36C
    ARC_PlayerItem wear[2]; // +0x378
    ARC_PlayerItem weapon; // +0x390
    int maxrolevalue[12]; // +0x39C
    int currolevalue[12]; // +0x3CC
    unsigned long dwWeaponSkillID; // +0x3FC
    unsigned long dwCleanCent; // +0x400
    float fWeaponSkillMass; // +0x404
    unsigned long dwSkillID[6]; // +0x408
    unsigned char bSkillMastered[6]; // +0x420
    unsigned long dwMagicID[8][6]; // +0x428
    unsigned char bMagicMastered[8][6]; // +0x4E8
    unsigned char byMagicUseTime[8][6]; // +0x518
    unsigned char byMagicLevel[8][6]; // +0x548
    unsigned char bAutoCtrl; // +0x578
    unsigned char bAIAttack; // +0x579
    unsigned char bAIMagic; // +0x57A
    unsigned char bAISkill; // +0x57B
    unsigned char bAIUseItem; // +0x57C
    unsigned char bAINegative; // +0x57D
    unsigned char byLineup; // +0x57E
    // total size: 0x580 (1408)

};

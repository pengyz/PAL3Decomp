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
    DWORD dwWeaponSkillID; // +0x3FC
    DWORD dwCleanCent; // +0x400
    float fWeaponSkillMass; // +0x404
    DWORD dwSkillID[6]; // +0x408
    BYTE bSkillMastered[6]; // +0x420
    DWORD dwMagicID[8][6]; // +0x428
    BYTE bMagicMastered[8][6]; // +0x4E8
    BYTE byMagicUseTime[8][6]; // +0x518
    BYTE byMagicLevel[8][6]; // +0x548
    BYTE bAutoCtrl; // +0x578
    BYTE bAIAttack; // +0x579
    BYTE bAIMagic; // +0x57A
    BYTE bAISkill; // +0x57B
    BYTE bAIUseItem; // +0x57C
    BYTE bAINegative; // +0x57D
    BYTE byLineup; // +0x57E
    // total size: 0x580 (1408)

};

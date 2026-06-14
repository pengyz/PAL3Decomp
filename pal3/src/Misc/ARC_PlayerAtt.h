#include "ARC_RoleAtt.h"
#pragma once
// Auto-generated: ARC_PlayerAtt

#include "ARC_PlayerItem.h"

class ARC_PlayerAtt : public ARC_RoleAtt {
public:
    char _gap_000[852]; // +0x0
    ARC_PlayerItem * hat; // +0x354
    char _gap_358[4]; // +0x358
    int nScriptSpeed; // +0x35C
    ARC_PlayerItem cloth; // +0x360
    char _gap_364[8]; // +0x364
    ARC_PlayerItem shoes; // +0x36C
    char _gap_370[8]; // +0x370
    ARC_PlayerItem wear[2]; // +0x378
    char _gap_380[12]; // +0x380
    int nScriptCounter; // +0x38C
    ARC_PlayerItem weapon; // +0x390
    char _gap_394[8]; // +0x394
    int maxrolevalue[12]; // +0x39C
    int currolevalue[12]; // +0x3CC
    UINT dwWeaponSkillID; // +0x3FC
    UINT dwCleanCent; // +0x400
    float fWeaponSkillMass; // +0x404
    UINT dwSkillID[6]; // +0x408
    _BYTE bSkillMastered[6]; // +0x420
    char _gap_426[2]; // +0x426
    UINT dwMagicID[8][6]; // +0x428
    _BYTE bMagicMastered[8][6]; // +0x4E8
    _BYTE byMagicUseTime[8][6]; // +0x518
    _BYTE byMagicLevel[8][6]; // +0x548
    BYTE bAutoCtrl; // +0x578
    BYTE bAIAttack; // +0x579
    BYTE bAIMagic; // +0x57A
    BYTE bAISkill; // +0x57B
    BYTE bAIUseItem; // +0x57C
    BYTE bAINegative; // +0x57D
    BYTE byLineup; // +0x57E
    char _tail_57F[1]; // +0x57F
    // total size: 0x580 (1408)

    int Refresh(); // 0x004A12F0
    int Create(int id, int nVal); // 0x004A16C0
};

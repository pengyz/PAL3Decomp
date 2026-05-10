#pragma once
// Auto-generated: FightInfo

#include "ECBBattleFieldAttr.h"
#include "ECBFiveMagic.h"
#include "ECBMeetEnemy.h"

class Role;

class FightInfo {
public:
    unsigned long monsterID[6]; // +0x0
    int nAllMonsterNum; // +0x18
    int nMaxRound; // +0x1C
    char sSceneName[32]; // +0x20
    ECBFiveMagic eSceneFiveMagic; // +0x40
    ECBMeetEnemy eMeetType; // +0x44
    ECBBattleFieldAttr eBattleFieldAttr; // +0x48
    unsigned char bMustFail; // +0x4C
    int nRoleWillNotBeAttack; // +0x50
    unsigned char bScript; // +0x54
    unsigned char bBossMusic; // +0x55
    unsigned char bFiveNimbus; // +0x56
    unsigned char bPXVariance; // +0x57
    unsigned char bFirst; // +0x58
    Role * pMosnter; // +0x5C
    // total size: 0x60 (96)

};

#pragma once
// Auto-generated: FightInfo

#include "ECBBattleFieldAttr.h"
#include "ECBFiveMagic.h"
#include "ECBMeetEnemy.h"

class Role;

class FightInfo {
public:
    DWORD monsterID[6]; // +0x0
    int nAllMonsterNum; // +0x18
    int nMaxRound; // +0x1C
    char sSceneName[32]; // +0x20
    ECBFiveMagic eSceneFiveMagic; // +0x40
    ECBMeetEnemy eMeetType; // +0x44
    ECBBattleFieldAttr eBattleFieldAttr; // +0x48
    BYTE bMustFail; // +0x4C
    int nRoleWillNotBeAttack; // +0x50
    BYTE bScript; // +0x54
    BYTE bBossMusic; // +0x55
    BYTE bFiveNimbus; // +0x56
    BYTE bPXVariance; // +0x57
    BYTE bFirst; // +0x58
    Role * pMosnter; // +0x5C
    // total size: 0x60 (96)

};

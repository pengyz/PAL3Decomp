#pragma once
// Auto-generated: ARC_PlayerMgrInfo

#include "ARC_Inventory.h"
#include "ARC_MonsterStar.h"
#include "ARC_PlayerAtt.h"
#include "ARC_Reoccupy.h"

class ARC_PlayerMgrInfo {
public:
    int m_nHuaYingMode; // +0x0
    int dwWeaponWU; // +0x4
    int m_favor[6]; // +0x8
    ARC_PlayerAtt m_att[5]; // +0x20
    char _gap_034[7020]; // +0x34
    _BYTE m_inteam[5]; // +0x1BA0
    char _gap_1BA5[3]; // +0x1BA5
    ARC_Inventory m_inventory; // +0x1BA8
    char _gap_1BAC[36]; // +0x1BAC
    ARC_Reoccupy m_reoccupy; // +0x1BD0
    char _gap_1BD4[12]; // +0x1BD4
    ARC_MonsterStar m_starts[10]; // +0x1BE0
    char _gap_1C08[120]; // +0x1C08
    _BYTE m_byGemUseTime[8]; // +0x1C80
    UINT reverse[18]; // +0x1C88
    // total size: 0x1CD0 (7376)

};

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
    unsigned char m_inteam[5]; // +0x1BA0
    ARC_Inventory m_inventory; // +0x1BA8
    ARC_Reoccupy m_reoccupy; // +0x1BD0
    ARC_MonsterStar m_starts[10]; // +0x1BE0
    unsigned char m_byGemUseTime[8]; // +0x1C80
    unsigned long reverse[18]; // +0x1C88
    // total size: 0x1CD0 (7376)

};

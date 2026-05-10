#pragma once
// Auto-generated: PlayerMgr

#include "Comp_Donate.h"
#include "Inventory.h"
#include "MonsterStar.h"
#include "PlayerAtt.h"
#include "PtrArray.h"
#include "Reoccupy.h"
#include "Role.h"
#include "RoleTaskPool.h"

class CParticleEffect;

class PlayerMgr {
public:
    PtrArray m_pMsgBuffer; // +0x0
    int m_underctrl; // +0x10
    int m_bStartNGHEffect; // +0x14
    int m_nHuaYingMode; // +0x18
    int m_favor[6]; // +0x1C
    int m_favor_old[6]; // +0x34
    RoleTaskPool m_RoleTask; // +0x4C
    Comp_Donate m_CompDonate[10][5]; // +0x2E0
    Inventory m_inventory; // +0x538
    Reoccupy m_reoccupy; // +0x560
    int dwWeaponWU; // +0x570
    PlayerAtt m_att[5]; // +0x574
    Role m_role[5]; // +0x2EDC
    Role m_huaYing; // +0xDA1C
    int m_bNGHS; // +0xFC5C
    int m_bWPXS; // +0xFC60
    Role m_FYS[3]; // +0xFC64
    CParticleEffect * pNGHVarianceParticle; // +0x16324
    Role m_SeekingMouse; // +0x16328
    Role m_Bee; // +0x18568
    int m_inteam[5]; // +0x1A7A8
    int m_skill[5]; // +0x1A7BC
    MonsterStar m_starts[10]; // +0x1A7D0
    int m_pstate; // +0x1A870
    float m_fFStime; // +0x1A874
    int m_byGemUseTime[8]; // +0x1A878
    int m_dwCombatTimes; // +0x1A898
    int nImbibeNimbusTimes; // +0x1A89C
    int nNimbus[5]; // +0x1A8A0
    int bHaveNimbus; // +0x1A8B4
    int bPXVariance; // +0x1A8B8
    int m_bFinalCombat; // +0x1A8BC
    int m_nCombatHurtHP; // +0x1A8C0
    int m_nCombatHurtMP; // +0x1A8C4
    int m_bShowStatuary; // +0x1A8C8
    // total size: 0x1A8CC (108748)

};

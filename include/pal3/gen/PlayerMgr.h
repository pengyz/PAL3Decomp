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
    Comp_Donate m_CompDonate[10][5]; // +0x2F8
    Inventory m_inventory; // +0x488
    Reoccupy m_reoccupy; // +0x4B0
    int dwWeaponWU; // +0x4C0
    PlayerAtt m_att[5]; // +0x4C4
    Role m_role[5]; // +0x2288
    Role m_huaYing; // +0xCF30
    int m_bNGHS; // +0xF1B8
    int m_bWPXS; // +0xF1BC
    Role m_FYS[3]; // +0xF1C0
    CParticleEffect * pNGHVarianceParticle; // +0x15958
    Role m_SeekingMouse; // +0x1595C
    Role m_Bee; // +0x17BE4
    int m_inteam[5]; // +0x19E6C
    int m_skill[5]; // +0x19E80
    MonsterStar m_starts[10]; // +0x19E94
    int m_pstate; // +0x19F34
    float m_fFStime; // +0x19F38
    int m_byGemUseTime[8]; // +0x19F3C
    int m_dwCombatTimes; // +0x19F5C
    int nImbibeNimbusTimes; // +0x19F60
    int nNimbus[5]; // +0x19F64
    int bHaveNimbus; // +0x19F78
    int bPXVariance; // +0x19F7C
    int m_bFinalCombat; // +0x19F80
    int m_nCombatHurtHP; // +0x19F84
    int m_nCombatHurtMP; // +0x19F88
    int m_bShowStatuary; // +0x19F8C
    // total size: 0x19F90 (106384)

};

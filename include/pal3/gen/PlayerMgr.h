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
    Reoccupy m_reoccupy; // +0x548
    int dwWeaponWU; // +0x54C
    PlayerAtt m_att[5]; // +0x550
    Role m_role[5]; // +0x2EB8
    Role m_huaYing; // +0xD9E4
    int m_bNGHS; // +0xFC20
    int m_bWPXS; // +0xFC24
    Role m_FYS[3]; // +0xFC28
    CParticleEffect * pNGHVarianceParticle; // +0x162DC
    Role m_SeekingMouse; // +0x162E0
    Role m_Bee; // +0x1851C
    int m_inteam[5]; // +0x1A758
    int m_skill[5]; // +0x1A76C
    MonsterStar m_starts[10]; // +0x1A780
    int m_pstate; // +0x1A820
    float m_fFStime; // +0x1A824
    int m_byGemUseTime[8]; // +0x1A828
    int m_dwCombatTimes; // +0x1A848
    int nImbibeNimbusTimes; // +0x1A84C
    int nNimbus[5]; // +0x1A850
    int bHaveNimbus; // +0x1A864
    int bPXVariance; // +0x1A868
    int m_bFinalCombat; // +0x1A86C
    int m_nCombatHurtHP; // +0x1A870
    int m_nCombatHurtMP; // +0x1A874
    int m_bShowStatuary; // +0x1A878
    // total size: 0x1A87C (108668)

};

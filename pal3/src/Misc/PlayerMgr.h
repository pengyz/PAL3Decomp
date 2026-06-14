#pragma once
// Auto-generated: PlayerMgr

#include "Inventory.h"
#include "PtrArray.h"
#include "Reoccupy.h"
#include "RoleTaskPool.h"

class CCBUIPanel;
class CParticleEffect;

class PlayerMgr {
public:
    struct PoisonState;


    struct PoisonState {
        _BYTE _tail_000[32];
    };
    PtrArray m_pMsgBuffer; // +0x0
    char _gap_004[12]; // +0x4
    int m_underctrl; // +0x10
    int m_bStartNGHEffect; // +0x14
    int m_nHuaYingMode; // +0x18
    char _gap_01C[48]; // +0x1C
    RoleTaskPool m_RoleTask; // +0x4C
    char _gap_050[1080]; // +0x50
    Inventory m_inventory; // +0x488
    char _gap_48C[36]; // +0x48C
    Reoccupy m_reoccupy; // +0x4B0
    char _gap_4B4[12]; // +0x4B4
    int dwWeaponWU; // +0x4C0
    char _gap_4C4[60660]; // +0x4C4
    int m_bNGHS; // +0xF1B8
    int m_bWPXS; // +0xF1BC
    char _gap_F1C0[26520]; // +0xF1C0
    CParticleEffect * pNGHVarianceParticle; // +0x15958
    char _gap_1595C[17880]; // +0x1595C
    int m_pstate; // +0x19F34
    float m_fFStime; // +0x19F38
    char _gap_19F3C[32]; // +0x19F3C
    int m_dwCombatTimes; // +0x19F5C
    int nImbibeNimbusTimes; // +0x19F60
    char _gap_19F64[20]; // +0x19F64
    int bHaveNimbus; // +0x19F78
    int bPXVariance; // +0x19F7C
    int m_bFinalCombat; // +0x19F80
    int m_nCombatHurtHP; // +0x19F84
    int m_nCombatHurtMP; // +0x19F88
    int m_bShowStatuary; // +0x19F8C
    char _tail_19F90[672]; // +0x19F90
    // total size: 0x1A230 (107056)

    void ctor(); // 0x0045AE60
    unsigned __int8 LoadState(const void *arg0); // 0x0045B7A0
    int InitCombatUI(int nVal); // 0x0045B990
    void InitMode(int nVal); // 0x00461C50
    int SendInputToRole(unsigned __int8 pData); // 0x004620E0
    int SetSelectionFlags(int nFlags); // 0x00462120
    int CreatePanelElements(CCBUIPanel *arg0); // 0x004623A0
    void SetupPlayerDisplay(int nVal); // 0x00469D90
    BOOL HandleInput(int nInputID, int nParam, int nFlags); // 0x00469EB0
    char ToggleSlot0(unsigned __int8 pData); // 0x00471220
    char ToggleSlot1(unsigned __int8 pData); // 0x004712D0
    char ToggleSlot2(unsigned __int8 pData); // 0x00471380
    char ToggleSlot3(unsigned __int8 pData); // 0x00471430
    char ToggleSlot4(unsigned __int8 pData); // 0x004714E0
};

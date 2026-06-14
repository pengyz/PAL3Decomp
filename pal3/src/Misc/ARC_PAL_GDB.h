#pragma once
// Auto-generated: ARC_PAL_GDB

#include "ARC_ComboAttack.h"
#include "ARC_FightItem.h"
#include "ARC_FightSkill.h"
#include "ARC_OutFile.h"
#include "ARC_RoleAtt.h"

class ARC_PAL_GDB {
public:
    ARC_OutFile m_head; // +0x0
    char _gap_004[156]; // +0x4
    ARC_RoleAtt m_RoleData[200]; // +0xA0
    char _gap_3C0[169600]; // +0x3C0
    ARC_FightSkill m_SkillData[300]; // +0x29A40
    char _gap_29EF0[226800]; // +0x29EF0
    ARC_FightItem m_ItemData[500]; // +0x614E0
    char _gap_61CB0[398000]; // +0x61CB0
    ARC_ComboAttack m_ComboData[10]; // +0xC2F60
    char _gap_C2F88[6280]; // +0xC2F88
    int i; // +0xC4810
    BYTE mLoaded; // +0xC4814
    char _tail_C4815[3]; // +0xC4815
    // total size: 0xC4818 (804888)

};

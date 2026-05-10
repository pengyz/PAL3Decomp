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
    ARC_RoleAtt m_RoleData[200]; // +0xA0
    ARC_FightSkill m_SkillData[300]; // +0x29A40
    ARC_FightItem m_ItemData[500]; // +0x614E0
    ARC_ComboAttack m_ComboData[10]; // +0xC2F60
    int i; // +0xC4810
    unsigned char mLoaded; // +0xC4814
    // total size: 0xC4818 (804888)

};

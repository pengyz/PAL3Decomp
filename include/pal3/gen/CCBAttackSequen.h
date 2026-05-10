#pragma once
// Auto-generated: CCBAttackSequen

#include "ECBStageLockFlag.h"
#include "tagAttackSequen.h"

class CCBRoleState;
class CCBSystem;
class CCBUI;

class CCBAttackSequen {
public:
    CCBSystem * m_pCBSystem; // +0x0
    CCBUI * m_pUI; // +0x4
    CCBRoleState * m_pRole; // +0x8
    tagAttackSequen m_Sequen[11]; // +0xC
    BYTE m_bEnable; // +0x1C4
    BYTE m_bPause; // +0x1C5
    BYTE m_bVisible; // +0x1C6
    BYTE m_bLocked; // +0x1C7
    ECBStageLockFlag m_eLockFlag[11]; // +0x1C8
    // total size: 0x1F4 (500)

    int Update(); // 0x004DB5C0
    char ProcessQueue(); // 0x004DBA60
    char CheckComplete(); // 0x004DBB20
    int AdvanceStep(); // 0x004DBD40
};

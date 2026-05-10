#pragma once
// Auto-generated: PAL_GDB

#include "ComboAttack.h"
#include "FightItem.h"
#include "FightSkill.h"
#include "OutFile.h"
#include "RoleAtt.h"

class PAL_GDB {
public:
    OutFile m_head; // +0x0
    RoleAtt m_RoleData[200]; // +0xA0
    FightSkill m_SkillData[300]; // +0x29A40
    FightItem m_ItemData[512]; // +0x614E0
    ComboAttack m_ComboData[10]; // +0xC54E0
    int i; // +0xC6DB8
    // total size: 0xC6DBC (814524)

    char LoadLanguage(char *path); // 0x00457410
    int GDB_LoadFile(); // 0x00479040
    int GDB_GetRole(unsigned int a2); // 0x00479050
    int GDB_GetRoleNum(int a2); // 0x00479080
    int GDB_GetSkillNum(int a2); // 0x00479130
    int GDB_GetSkillID(); // 0x004791A0
    int GDB_GetItemNum(int a2); // 0x004791E0
    static int GDB_GetComboID(); // 0x004792C0
};

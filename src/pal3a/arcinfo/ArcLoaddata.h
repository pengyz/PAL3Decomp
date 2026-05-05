#ifndef PAL3A_ARCLOADDATA_H
#define PAL3A_ARCLOADDATA_H

#include "pal3a_types.h"

class ARC_PAL_GDB {
public:
    char _data[804888];

    int GDB_GetRoleNum();
    unsigned long GDB_GetRoleID(int index);
    ARC_PAL_GDB();
    int GDB_GetSkillNum();
    unsigned long GDB_GetSkillID(int index);
    ARC_ComboAttack * GDB_GetCombo(ulong ID);
    int GDB_GetItemNum();
    unsigned long GDB_GetItemID(int index);
    ~ARC_PAL_GDB();
    ARC_RoleAtt * GDB_GetRole(ulong ID);
    ARC_FightItem * GDB_GetItem(ulong ID);
    ARC_FightSkill * GDB_GetSkill(ulong ID);
    bool GDB_LoadFile();
    unsigned long GDB_GetComboID(int index);
    int GDB_GetComboNum();
};

#endif // PAL3A_ARCLOADDATA_H

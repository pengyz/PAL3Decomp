#ifndef PAL3A_LOADDATA_H
#define PAL3A_LOADDATA_H

#include "pal3a_types.h"

class PAL_GDB {
public:
    char _data[814524];

    RoleAtt * GDB_GetRole(ulong ID);
    FightItem * GDB_GetItem(ulong ID);
    ~PAL_GDB();
    int GDB_GetSkillNum();
    unsigned long GDB_GetRoleID(int index);
    unsigned long GDB_GetSkillID(int index);
    int GDB_GetRoleNum();
    unsigned long GDB_GetItemID(int index);
    int GDB_GetItemNum();
    ComboAttack * GDB_GetCombo(ulong ID);
    PAL_GDB();
    FightSkill * GDB_GetSkill(ulong ID);
    unsigned long GDB_GetComboID(int index);
    int GDB_GetComboNum();
    bool GDB_LoadFile();
};

#endif // PAL3A_LOADDATA_H

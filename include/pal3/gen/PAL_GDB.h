#pragma once
// Auto-generated from IDA decomp - PAL_GDB
// 10 methods

class PAL_GDB {
public:
    char LoadLanguage(char *path);  // 0x00457410
    char PAL_GDB();  // 0x00478E00
    int ~PAL_GDB(int a2);  // 0x00478FD0
    int GDB_LoadFile();  // 0x00479040
    int GDB_GetRole(unsigned int a2);  // 0x00479050
    int GDB_GetRoleNum(int a2);  // 0x00479080
    int GDB_GetSkillNum(int a2);  // 0x00479130
    int GDB_GetSkillID();  // 0x004791A0
    int GDB_GetItemNum(int a2);  // 0x004791E0
    static int() GDB_GetComboID();  // 0x004792C0
};

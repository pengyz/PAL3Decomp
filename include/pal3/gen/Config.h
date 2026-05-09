#pragma once
// Auto-generated from IDA decomp - Config
// 3 methods

class Config {
public:
    int ReadINIInt(char *filename, char *key);  // 0x0042FDA0
    static char *__thiscall(void *this, char *filename, char *key) ReadINIString();  // 0x0042FDC0
    bool ReadINI(char *filename, char *section);  // 0x0042FDE0
};

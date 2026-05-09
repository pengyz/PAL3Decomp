#pragma once
// Auto-generated: Config

class Config {
public:
    int ReadINIInt(char *filename, char *key); // 0x0042FDA0
    char * ReadINIString(char *filename, char *key); // 0x0042FDC0
    bool ReadINI(char *filename, char *section); // 0x0042FDE0
};

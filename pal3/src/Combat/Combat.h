#pragma once
// Auto-generated: Combat

class Combat {
public:
    _BYTE _tail_000[4]; // +0x0
    // total size: 0x4 (4)

    int GetSlotCount(); // 0x0040CCD0
    char Func_4CDB60(); // 0x004CDB60
    char LogMessage(char *a2, int a3, char *format, ...); // 0x004DFD20
    unsigned __int8 HandleControlCmd(int idx); // 0x004F4820
};

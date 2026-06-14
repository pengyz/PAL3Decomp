#pragma once
// Auto-generated: Config

class Config {
public:
    char _gap_000[4]; // +0x0
    _BYTE * m_ptr_4; // +0x4
    char _tail_008[28]; // +0x8
    // total size: 0x24 (36)

    int ReadINIInt(char *filename, char *key); // 0x0042FDA0
    char * FormatSectionPath(char *filename, char *key); // 0x0042FDC0
    bool ReadSectionAsInt(char *filename, char *section); // 0x0042FDE0
    int * ResetField7(); // 0x0042FEB0
    int InitDefaults(int *p_DWORD, int *p_DWORD2); // 0x0042FEC0
    BOOL ReadFloatArray(int nVal, int nVal2, int *pnVal, int *pnVal2); // 0x0042FF40
    int SetSlotValue(int nVal, int nVal2); // 0x00430080
    bool GetNextEntry(int nVal, int *pnVal, int *pnVal2, int *p_DWORD); // 0x004300A0
    int ParseSection(int nVal); // 0x00430670
};

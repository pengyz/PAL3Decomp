#ifndef PAL3A_FINDARC_H
#define PAL3A_FINDARC_H

#include "pal3a_types.h"

class FindArc {
public:
    char _data[9476];

    ~FindArc();
    bool ReadReg(char * KEY_ROOT, char * KEY_NAME, char * outstr);
    bool ReadReg(char * KEY_ROOT, char * KEY_NAME, ulong * key_value);
    bool GetArc();
    FindArc();
    bool CheckReg(HKEY__ * key, char * subKey);
    bool CheckSetRegValue(long checksion, char * caption);
    void RemoveReg(char * KEY_ROOT);
    bool WriteReg(char * KEY_ROOT, char * KEY_NAME, ulong key_value);
};

#endif // PAL3A_FINDARC_H

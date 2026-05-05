#ifndef PAL3A_UTILOBJ_H
#define PAL3A_UTILOBJ_H

#include "pal3a_types.h"

class util {
public:
    char _data[1044];

    CIniFile * GetIniReader();
    void AddOneForNumInString(char * sOut, char * sIn);
    unsigned long Crc32(char * pData);
    ~util();
    CLoad3DS * Get3DSLoader();
    util();
    void InitCrc32Table();
};

#endif // PAL3A_UTILOBJ_H

#ifndef PAL3A_NAMESYS_H
#define PAL3A_NAMESYS_H

#include "pal3a_types.h"

class NameSys {
public:
    char _data[280];

    ~NameSys();
    NameSys();
    unsigned long GetLastItemId();
    void load(_iobuf * fd);
    bool IsGetAll();
    void IncRef(int flag);
    void init();
    void CheckName();
    void Read();
    void ZeroRef(int flag);
    void save(_iobuf * fd);
};

#endif // PAL3A_NAMESYS_H

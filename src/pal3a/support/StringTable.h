#ifndef PAL3A_STRINGTABLE_H
#define PAL3A_STRINGTABLE_H

#include "pal3a_types.h"

class StringTable {
public:
    std::map<std::string, std::string> m_data;

    StringTable();
    ~StringTable();
    void Load(char *filename);
    const char *operator[](const char *key);
};

#endif // PAL3A_STRINGTABLE_H

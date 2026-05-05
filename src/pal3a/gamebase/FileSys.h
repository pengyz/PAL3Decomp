#ifndef PAL3A_FILESYS_H
#define PAL3A_FILESYS_H

#include "pal3a_types.h"

class OpenBaseFile {
public:
    char _data[4];

    ~OpenBaseFile();
    OpenBaseFile();
};

class OpenNULLFile {
public:
    char _data[4];

    ~OpenNULLFile();
    OpenNULLFile();
};

class OpenSceneFile {
public:
    char _data[1];

    OpenSceneFile(char * path, char * name);
    ~OpenSceneFile();
};

void FileSysInit();
void FileSysDestory();

#endif // PAL3A_FILESYS_H

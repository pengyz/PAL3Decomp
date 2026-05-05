#ifndef PAL3A_SCENEDATA_H
#define PAL3A_SCENEDATA_H

#include "pal3a_types.h"

class SCNFile {
public:
    char _data[187596];

    ~SCNFile();
    void Load(char * cityname, char * name);
    SCNFile();
    int Save();
};

unsigned char _ObjCollideType(ObjectInfo * obj);

#endif // PAL3A_SCENEDATA_H

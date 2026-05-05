#ifndef PAL3A_ARC_COMMON_H
#define PAL3A_ARC_COMMON_H

#include "pal3a_types.h"

class ARC_Inventory {
public:
    char _data[40];

    ARC_PlayerItem GetItem(ARC_PlayerItem * __$ReturnUdt);
    bool Read(_iobuf * fp);
    int TypeArrayBuild(ARC_PlayerItem_Type type);
    ARC_PlayerItem TypeArray(ARC_PlayerItem * __$ReturnUdt);
    void Clear();
    int GetTotalNum();
    ARC_PlayerItem * Find(ARC_PlayerItem * item);
    int TypeArraySize();
};

class ARC_PlayerAtt {
public:
    char _data[64];

    void CalMaxRV(uchar isAll);
};

class ARC_PlayerMgrInfo {
public:
    char _data[64];

    bool LoadData(_iobuf * fp);
};

class ARC_Reoccupy {
public:
    char _data[16];

    unsigned long GetID(int cur);
    int GetNum();
    bool Read(_iobuf * fp);
};

bool LoadARCFile(_iobuf * fp);
bool LoadArcBrief(int index, ARC_ArcBrief * brief);

#endif // PAL3A_ARC_COMMON_H

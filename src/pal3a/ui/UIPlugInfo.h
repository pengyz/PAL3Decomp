#ifndef PAL3A_UIPLUGINFO_H
#define PAL3A_UIPLUGINFO_H

#include "pal3a_types.h"

class ArtistPlugIn {
public:
    char _data[64];

    tagRECT GetMaxRect(tagRECT * __$ReturnUdt, char * name);
    void SetLibFolder(char * folder);
    _PlugInfo * GetInfo(char * name);
    _PlugInfo * GetInfo(int index);
    char * GetLib(char * _texName);
    UIPosMaker * GetPosMaker();
    void GetPlugFileInfo(char * filename);
    tagRECT GetRect(tagRECT * __$ReturnUdt);
    ~ArtistPlugIn();
    ArtistPlugIn(char * filename);
    ArtistPlugIn();
};

class UIPosMaker {
public:
    char _data[12];

    bool LoadPosFile();
    bool GetPos(int nIndex, int * nx, int * ny);
    bool GetPos(uint nameCrc, int * nx, int * ny);
    UIPosMaker();
    ~UIPosMaker();
};

class _PlugInfo {
public:
    char _data[64];

    bool _CalculateUV();
};

#endif // PAL3A_UIPLUGINFO_H

#ifndef PAL3A_UI_TEXTUREINFO_H
#define PAL3A_UI_TEXTUREINFO_H

#include "pal3a_types.h"

class Parent_Data {
public:
    char _data[4];

    int _CheckKeyWord(char** srcKey, char * cmpKey);
    ~Parent_Data();
    int _CheckStr(char * string, char** outstr);
    unsigned long GetSize(char * FileName);
    Parent_Data();
    char * spstr(char * s);
    int spstr(char * s, char** s1);
};

class _TextureLib_Data {
public:
    char _data[536];

    unsigned int _GetItemNum(void * pMem);
    ~_TextureLib_Data();
    bool GetLibInfo(char * FileName);
    bool _CheckItem(char * Str, char * Format);
    void SetLibFolder(char * folder);
    _TextureLib_Data();
    char * GetLib(char * _texName);
    _Texture_Info * GetTextureInfo(int index);
    _Texture_Info * GetTextureInfo(char * _texName);
};

class _Texture_Info {
public:
    char _data[64];

    bool _CalculateUV();
};

#endif // PAL3A_UI_TEXTUREINFO_H

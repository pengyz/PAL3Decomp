#include "Parent_Data.h"
#pragma once
// Auto-generated: TextureLibDataBase

class Parent_Data;
class _Texture_Info;

class TextureLibDataBase : public Parent_Data {
public:
    char _gap_000[4]; // +0x0
    char * Seps; // +0x4
    char * tok; // +0x8
    char _libfolder[512]; // +0xC
    int _realNum; // +0x20C
    _Texture_Info * m_pData; // +0x210
    BYTE _isLoadTLI; // +0x214
    char _gap_215[47]; // +0x215
    float m_fScrollSpeed; // +0x244
    // total size: 0x248 (584)

    int CountEntries(); // 0x00443A00
    int SearchByIndex(); // 0x00443A90
    __int64 AutoScrollParticles(char *pszBuf, int nVal, TextureLibDataBase *pTextureLibDataBase, int nVal2); // 0x004B4FE0
    __int64 AutoScrollParticlesEx(char *pszBuf, TextureLibDataBase *pTextureLibDataBase, int nVal, int nVal2); // 0x004B51A0
    __int64 UpdateCircularMotion(char *pszBuf, int nVal, TextureLibDataBase *p, int nVal2); // 0x004B5380
    __int64 UpdateOrbitalMotion(char *pszBuf, int nVal, TextureLibDataBase *p, int nVal2); // 0x004B5450
    __int64 UpdateLinearMotion(char *pszBuf, int nVal, TextureLibDataBase *p, int nVal2); // 0x004B5750
    void RenderFrame(int nVal, int nVal2, int nVal3, int nVal4); // 0x004B5D20
    char LoadLibrary(char *pszBuf, int nVal, TextureLibDataBase *pTextureLibDataBase, int nVal2); // 0x004B5EE0
    char UpdateByMode(char *pszBuf, int nVal, TextureLibDataBase *p, int nVal2); // 0x004B60F0
    __int64 GetTextureByName(char *pszBuf, int nVal, TextureLibDataBase *pTextureLibDataBase, int nVal2); // 0x004B6300
    Parent_Data * CreateParentData(LPCSTR lpString); // 0x0053FDD0
    void _TextureLib_Data(); // 0x0053FFA0
    unsigned int _GetItemNum(void *pData); // 0x005400E0
    int _CheckItem(char *pszName, char *pszBuf); // 0x00540210
    void SetLibFolder(char *pszFolder); // 0x00540440
    bool GetLibInfo(char *pszName); // 0x00540650
    char * GetLib(char *pszName); // 0x005407A0
    _Texture_Info * GetTextureInfo(char *pszName); // 0x005408E0
    _Texture_Info * GetTextureInfoByIndex(int nIndex); // 0x00540A20
};

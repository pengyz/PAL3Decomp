#pragma once
// Auto-generated: CJ_FindFile

class CJ_FindFile {
public:
    char m_strRoot[324]; // +0x0
    char * m_pNextInfo; // +0x144
    char * m_hContext; // +0x148
    char * m_pFoundInfo; // +0x14C
    char m_fileName[324]; // +0x150
    char m_strbuf[324]; // +0x294
    BYTE m_bClosed; // +0x3D8
    char _tail_3D9[3]; // +0x3D9
    // total size: 0x3DC (988)

    int Create(int id, void *pRect, int parent, char *tex); // 0x00450F90
};

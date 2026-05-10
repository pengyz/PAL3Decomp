#pragma once
// Auto-generated: CPK

#include "ECPKMode.h"
#include "tagCPKHeader.h"
#include "tagCPKTable.h"

class gbVFile;

class CPK {
public:
    DWORD m_dwAllocGranularity; // +0x0
    DWORD CrcTable[256]; // +0x0
    ECPKMode m_eMode; // +0x4
    tagCPKHeader m_CPKHeader; // +0x8
    tagCPKTable m_CPKTable[32768]; // +0x88
    gbVFile * m_pgbVFile[8]; // +0xE0088
    BYTE m_bLoaded; // +0xE00A8
    DWORD m_dwCPKHandle; // +0xE00AC
    DWORD m_dwCPKMappingHandle; // +0xE00B0
    char m_szCPKFileName[260]; // +0xE00B4
    int m_nOpenedFileNum; // +0xE01B8
    // total size: 0xE01BC (917948)

};

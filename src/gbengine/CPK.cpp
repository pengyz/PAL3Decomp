/**
 * gbengine.dll - CPK
 * CPK archive file system (LZO compression, CRC32 hashing)
 */

#include "gbengine/gbVFileSystem.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>

// Static members
unsigned long CPK::CrcTable[256];

// CRC32 table initialization
void CPK::InitCrcTable(void) {
    for (unsigned int i = 0; i < 256; i++) {
        unsigned long crc = i;
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
        CrcTable[i] = crc;
    }
}

// Calculate CRC32 of a string
unsigned long CPK::Crc(const char* str) {
    if (!str) return 0;

    unsigned long crc = 0xFFFFFFFF;
    while (*str) {
        unsigned char byte = (unsigned char)*str;
        if (byte >= 'A' && byte <= 'Z') byte += 32; // Convert to lowercase
        if (byte == '\\') byte = '/'; // Normalize path separator

        crc = (crc >> 8) ^ CrcTable[(crc ^ byte) & 0xFF];
        str++;
    }

    return crc ^ 0xFFFFFFFF;
}

unsigned long CPK::GetAllocationGranularity(void) {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    return sysInfo.dwAllocationGranularity;
}

void CPK::Reset(void) {
    m_dwAllocGranularity = 0;
    m_eMode = CPKM_Null;
    memset(&m_CPKHeader, 0, sizeof(m_CPKHeader));
    memset(m_CPKTable, 0, sizeof(m_CPKTable));
    for (int i = 0; i < CPK_MAX_OPEN_FILES; i++) {
        m_pCPKFile[i] = NULL;
    }
    m_bLoaded = 0;
    m_dwCPKHandle = 0;
    m_dwCPKMappingHandle = 0;
    m_szCPKFileName[0] = '\0';
    m_nOpenedFileNum = 0;
}

bool CPK::IsDir(unsigned long tableIndex) {
    if (tableIndex >= CPK_MAX_TABLE_NUM) return false;
    return (m_CPKTable[tableIndex].dwFlag & CPK_FLAG_ISDIR) != 0;
}

int CPK::GetTableIndex(const char* filename) {
    if (!filename) return -1;
    unsigned long crc = Crc(filename);
    return GetTableIndexFromCRC(crc);
}

int CPK::GetTableIndexFromCRC(unsigned long crc) {
    for (unsigned int i = 0; i < m_CPKHeader.dwValidTableNum; i++) {
        if (m_CPKTable[i].dwCRC == crc) {
            if ((m_CPKTable[i].dwFlag & CPK_FLAG_ISDELETED) == 0) {
                return i;
            }
        }
    }
    return -1;
}

bool CPK::GetFileSize(unsigned long& packedSize, unsigned long& originSize,
                      unsigned long tableIndex) {
    if (tableIndex >= CPK_MAX_TABLE_NUM) return false;

    CPKTable* entry = &m_CPKTable[tableIndex];
    if (entry->dwFlag & CPK_FLAG_ISDELETED) return false;

    packedSize = entry->dwPackedSize;
    originSize = entry->dwOriginSize;
    return true;
}

bool CPK::IsLoaded(void) {
    return m_bLoaded != 0;
}

bool CPK::IsValidCPK(const char* filename) {
    if (!filename) return false;

    HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;

    CPKHeader header;
    DWORD bytesRead = 0;
    BOOL result = ReadFile(hFile, &header, sizeof(CPKHeader), &bytesRead, NULL);
    CloseHandle(hFile);

    if (!result || bytesRead != sizeof(CPKHeader)) return false;
    if (header.dwLable != CPK_LABEL) return false;

    return true;
}

bool CPK::Load(const char* filename) {
    if (!filename || m_bLoaded) return false;

    // Open CPK file
    HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;

    // Read header
    DWORD bytesRead = 0;
    if (!ReadFile(hFile, &m_CPKHeader, sizeof(CPKHeader), &bytesRead, NULL) ||
        bytesRead != sizeof(CPKHeader)) {
        CloseHandle(hFile);
        return false;
    }

    // Verify magic
    if (m_CPKHeader.dwLable != CPK_LABEL) {
        CloseHandle(hFile);
        return false;
    }

    // Read file table
    SetFilePointer(hFile, m_CPKHeader.dwTableStart, NULL, FILE_BEGIN);
    DWORD tableSize = m_CPKHeader.dwValidTableNum * sizeof(CPKTable);
    if (!ReadFile(hFile, m_CPKTable, tableSize, &bytesRead, NULL) ||
        bytesRead != tableSize) {
        CloseHandle(hFile);
        return false;
    }

    // Create file mapping for memory-mapped access
    m_dwCPKHandle = (unsigned long)hFile;
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    m_dwCPKMappingHandle = (unsigned long)hMapping;

    strncpy(m_szCPKFileName, filename, sizeof(m_szCPKFileName) - 1);
    m_szCPKFileName[sizeof(m_szCPKFileName) - 1] = '\0';

    m_dwAllocGranularity = GetAllocationGranularity();
    m_bLoaded = 1;

    return true;
}

bool CPK::Unload(void) {
    if (!m_bLoaded) return false;

    // Close all open files
    for (int i = 0; i < CPK_MAX_OPEN_FILES; i++) {
        if (m_pCPKFile[i]) {
            Close(m_pCPKFile[i]);
        }
    }

    // Close mapping and file
    if (m_dwCPKMappingHandle) {
        CloseHandle((HANDLE)m_dwCPKMappingHandle);
        m_dwCPKMappingHandle = 0;
    }

    if (m_dwCPKHandle) {
        CloseHandle((HANDLE)m_dwCPKHandle);
        m_dwCPKHandle = 0;
    }

    Reset();
    return true;
}

bool CPK::IsFileExist(const char* filename) {
    if (!m_bLoaded || !filename) return false;
    return GetTableIndex(filename) >= 0;
}

bool CPK::Close(CPKFile* pFile) {
    if (!pFile) return false;

    // Unmap memory if mapped
    if (pFile->lpMapAddress) {
        UnmapViewOfFile(pFile->lpMapAddress);
        pFile->lpMapAddress = NULL;
    }

    // Free decompressed data if allocated
    if (pFile->lpMem) {
        free(pFile->lpMem);
        pFile->lpMem = NULL;
    }

    pFile->bValid = 0;
    m_nOpenedFileNum--;

    return true;
}

bool CPK::Read(void* buffer, unsigned long size, CPKFile* pFile) {
    if (!buffer || !pFile || !pFile->bValid) return false;

    unsigned long remaining = pFile->dwFileSize - pFile->dwPointer;
    if (size > remaining) size = remaining;

    void* pSrc = pFile->lpMem ? pFile->lpMem : pFile->lpStartAddress;
    if (!pSrc) return false;

    memcpy(buffer, (char*)pSrc + pFile->dwPointer, size);
    pFile->dwPointer += size;

    return true;
}

unsigned long CPK::Seek(CPKFile* pFile, int offset, unsigned long origin) {
    if (!pFile || !pFile->bValid) return 0;

    unsigned long newPos = pFile->dwPointer;

    switch (origin) {
        case FILE_BEGIN:
            newPos = offset;
            break;
        case FILE_CURRENT:
            newPos = pFile->dwPointer + offset;
            break;
        case FILE_END:
            newPos = pFile->dwFileSize + offset;
            break;
    }

    if (newPos > pFile->dwFileSize) {
        newPos = pFile->dwFileSize;
    }

    pFile->dwPointer = newPos;
    return newPos;
}

/**
 * gbengine.dll - gbVFileSystem.cpp
 * Virtual File System implementation for PAL3 (仙剑奇侠传3)
 *
 * Contains: CPK, CPKFile, gbVFile, gbVFile1, gbVFileSystem, CIniFile
 *
 * CPK is a custom archive format using LZO compression and CRC32 filename hashing.
 * Structure sizes verified against PAL3A.PDB:
 *   sizeof(CPKHeader) == 0x80
 *   sizeof(CPKTable)  == 0x1C
 *   sizeof(CPK)       == 0xE01BC
 *   sizeof(gbVFileSystem) == 0xE01D4
 */

#include "gbengine/gbVFileSystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External declarations
extern int gbstricmp(const char* s1, const char* s2);
extern void gbLogInfo(char* fmt, ...);

// LZO compression/decompression - using miniLZO
extern "C" {
#include "lzo/minilzo.h"
}

// Static member definitions
int CPK::s_bCrcTableInitialized = 0;
unsigned long CPK::CrcTable[256];

// Global pointer to the virtual file system
gbVFileSystem* g_pVFileSys = NULL;


// ############################################################################
//  CPKFile Implementation
// ############################################################################

CPKFile::CPKFile()
{
    bValid = 0;
    lpRealData = 0;
}

CPKFile::~CPKFile()
{
}

CPKFile& CPKFile::operator=(const CPKFile& other)
{
    memcpy(this, &other, sizeof(CPKFile));
    return *this;
}

void* CPKFile::GetRealData()
{
    return lpRealData;
}


// ############################################################################
//  CPK Implementation
// ############################################################################

#pragma auto_inline(off)

CPK::CPK()
{
    memset(this, 0, sizeof(CPK));
    m_eMode = CPKM_FileMapping;

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    m_dwAllocGranularity = si.dwAllocationGranularity;

    if (!s_bCrcTableInitialized) {
        InitCrcTable();
    }

    for (int i = 0; i < CPK_MAX_OPEN_FILES; i++) {
        gbVFile* p = (gbVFile*)operator new(sizeof(gbVFile));
        if (p) {
            p->cpkFile.bValid = 0;
            p->cpkFile.lpRealData = 0;
        }
        m_pCPKFile[i] = p;
        if (p) {
            p->cpkFile.bValid = 0;
        }
    }
}

CPK::~CPK()
{
    Unload();
    for (int i = 0; i < CPK_MAX_OPEN_FILES; i++) {
        if (m_pCPKFile[i]) {
            delete (unsigned char*)m_pCPKFile[i];
            m_pCPKFile[i] = NULL;
        }
    }
}

CPK& CPK::operator=(const CPK& other)
{
    memcpy(this, &other, sizeof(CPK));
    return *this;
}

void CPK::InitCrcTable()
{
    if (!s_bCrcTableInitialized) {
        int v0 = 0;
        unsigned long* v1 = CrcTable;
        do {
            int v2 = 8;
            int v3 = v0 << 24;
            do {
                if (v3 >= 0)
                    v3 *= 2;
                else
                    v3 = (2 * v3) ^ 0x04C11DB7;
                --v2;
            } while (v2);
            *v1++ = (unsigned long)v3;
            ++v0;
        } while ((int)v1 < (int)&s_bCrcTableInitialized);
        s_bCrcTableInitialized = 1;
    }
}

unsigned long CPK::Crc(const char* a1)
{
    if (!*a1)
        return 0;

    const char* v2 = a1 + 1;
    int v3 = (unsigned char)*a1 << 24;
    if (a1[1]) {
        v3 |= (unsigned char)a1[1] << 16;
        v2 = a1 + 2;
        if (a1[2]) {
            v3 |= (unsigned char)a1[2] << 8;
            v2 = a1 + 3;
            if (a1[3]) {
                v3 |= (unsigned char)a1[3];
                v2 = a1 + 4;
            }
        }
    }

    unsigned char v5 = *(unsigned char*)v2;
    unsigned int i = ~(unsigned int)v3;
    while (v5) {
        i = CrcTable[i >> 24] ^ (v5 | (i << 8));
        v5 = *++v2;
    }
    return ~i;
}

bool CPK::Load(const char* filename)
{
    if (m_bLoaded)
        return 0;

    HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return 0;

    m_dwCPKHandle = (unsigned long)hFile;

    DWORD bytesRead = 0;
    ReadFile(hFile, &m_CPKHeader, sizeof(CPKHeader), &bytesRead, NULL);
    if (bytesRead != sizeof(CPKHeader)) {
        CloseHandle(hFile);
        m_dwCPKHandle = 0;
        return 0;
    }

    if (m_CPKHeader.dwLable != CPK_LABEL) {
        CloseHandle(hFile);
        m_dwCPKHandle = 0;
        return 0;
    }

    SetFilePointer(hFile, m_CPKHeader.dwTableStart, NULL, FILE_BEGIN);

    unsigned long tableSize = m_CPKHeader.dwValidTableNum * sizeof(CPKTable);
    ReadFile(hFile, m_CPKTable, tableSize, &bytesRead, NULL);
    if (bytesRead != tableSize) {
        CloseHandle(hFile);
        m_dwCPKHandle = 0;
        return 0;
    }

    if (m_eMode == CPKM_FileMapping) {
        HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
        m_dwCPKMappingHandle = (unsigned long)hMapping;
    }

    strncpy(m_szCPKFileName, filename, sizeof(m_szCPKFileName) - 1);
    m_szCPKFileName[sizeof(m_szCPKFileName) - 1] = '\0';

    m_bLoaded = 1;
    m_nOpenedFileNum = 0;

    return 1;
}

bool CPK::Unload()
{
    if (!m_bLoaded)
        return 0;

    if (m_eMode == CPKM_FileMapping) {
        CloseHandle((HANDLE)m_dwCPKMappingHandle);
    }
    CloseHandle((HANDLE)m_dwCPKHandle);

    memset(&m_CPKHeader, 0, sizeof(m_CPKHeader));
    memset(m_CPKTable, 0, sizeof(m_CPKTable));
    m_dwCPKHandle = (unsigned long)-1;
    m_dwCPKMappingHandle = (unsigned long)-1;
    m_bLoaded = 0;
    memset(m_szCPKFileName, 0, sizeof(m_szCPKFileName));
    m_nOpenedFileNum = 0;
    gbVFile** p = m_pCPKFile;
    int n = 8;
    do {
        gbVFile* f = *p++;
        --n;
        f->cpkFile.bValid = 0;
    } while (n);

    return 1;
}

void CPK::Reset(void) {
    memset(&m_CPKHeader, 0, sizeof(m_CPKHeader));
    memset(m_CPKTable, 0, sizeof(m_CPKTable));
    m_dwCPKHandle = (unsigned long)-1;
    m_dwCPKMappingHandle = (unsigned long)-1;
    m_bLoaded = 0;
    memset(m_szCPKFileName, 0, sizeof(m_szCPKFileName));
    m_nOpenedFileNum = 0;
    gbVFile** p = m_pCPKFile;
    int n = 8;
    do {
        gbVFile* f = *p++;
        --n;
        f->cpkFile.bValid = 0;
    } while (n);
}

void CPK::SetOpenMode(ECPKMode mode)
{
    if (!m_bLoaded) {
        m_eMode = mode;
    }
}

bool CPK::IsValidCPK(const char* filename)
{
    HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return 0;

    CPKHeader header;
    DWORD bytesRead = 0;
    ReadFile(hFile, &header, sizeof(CPKHeader), &bytesRead, NULL);
    CloseHandle(hFile);

    if (bytesRead != sizeof(CPKHeader))
        return 0;
    if (header.dwLable != CPK_LABEL)
        return 0;
    return 1;
}

bool CPK::IsFileExist(const char* filename)
{
    if (!m_bLoaded)
        return 0;

    char lowerName[260];
    lstrcpyA(lowerName, filename);
    _strlwr(lowerName);

    unsigned long crc = Crc(lowerName);

    for (unsigned long i = 0; i < m_CPKHeader.dwValidTableNum; i++) {
        if (m_CPKTable[i].dwCRC == crc) {
            if ((m_CPKTable[i].dwFlag & CPK_FLAG_ISFILE) &&
                !(m_CPKTable[i].dwFlag & CPK_FLAG_ISDELETED)) {
                return 1;
            }
        }
    }

    return 0;
}

bool CPK::IsLoaded()
{
    return m_bLoaded;
}

CPKFile* CPK::Open(const char* filename)
{
    if (!m_bLoaded)
        return NULL;

    if (m_nOpenedFileNum >= 7)
        return NULL;

    // Calculate CRC for lookup
    char lowerName[260];
    lstrcpyA(lowerName, filename);
    _strlwr(lowerName);
    unsigned long crc = Crc(lowerName);

    // Binary search in table
    int lo = 0;
    int hi = (int)m_CPKHeader.dwValidTableNum;
    int tableIndex = -1;

    while (1) {
        int mid = lo + (hi - lo) / 2;
        unsigned long midCrc = m_CPKTable[mid].dwCRC;
        if (crc == midCrc) {
            // Check flags
            unsigned long flags = m_CPKTable[mid].dwFlag;
            if ((flags & CPK_FLAG_ISFILE) && !(flags & CPK_FLAG_ISDELETED)) {
                tableIndex = mid;
                break;
            }
            // Not a valid entry, continue search
            goto next;
        }
next:
        if (hi == lo + 1)
            return NULL;
        if (crc < midCrc)
            hi = lo + (hi - lo) / 2;
        else
            lo += (hi - lo) / 2;
        if (hi == lo)
            return NULL;
    }

    if (tableIndex == -1)
        return NULL;

    CPKTable* pEntry = &m_CPKTable[tableIndex];

    // Find a free CPKFile slot
    int freeSlot = 0;
    gbVFile* pBlock = NULL;
    for (freeSlot = 0; freeSlot < CPK_MAX_OPEN_FILES; freeSlot++) {
        pBlock = (gbVFile*)m_pCPKFile[freeSlot];
        if (!pBlock->cpkFile.bValid)
            break;
    }
    if (freeSlot >= CPK_MAX_OPEN_FILES)
        return NULL;

    if (!pBlock)
        return NULL;

    CPKFile* pFile = &pBlock->cpkFile;
    pFile->bValid = 1;
    strcpy(pBlock->fullPath, filename);
    pFile->lpMapAddress = 0;

    DWORD dwStartPos = pEntry->dwStartPos;
    DWORD dwAlignedStart = dwStartPos;

    if (m_eMode == CPKM_FileMapping) {
        dwAlignedStart = dwStartPos - dwStartPos % m_dwAllocGranularity;
    }
    DWORD dwOffset = dwStartPos - dwAlignedStart;

    if (m_eMode == CPKM_FileMapping) {
        DWORD dwMapSize = dwOffset + pEntry->dwPackedSize + pEntry->dwExtraInfoSize;
        void* lpMap = MapViewOfFile((HANDLE)m_dwCPKMappingHandle,
                                    FILE_MAP_READ, 0, dwAlignedStart, dwMapSize);
        pFile->lpMapAddress = lpMap;
        if (!lpMap) {
            pFile->bValid = 0;
            return NULL;
        }
    }

    pFile->dwCRC = pEntry->dwCRC;
    pFile->dwFatherCRC = pEntry->dwFatherCRC;
    pFile->nTableIndex = tableIndex;
    pFile->pTableItem = pEntry;
    pFile->lpStartAddress = (char*)pFile->lpMapAddress + dwOffset;
    pFile->bCompressed = (pEntry->dwFlag & CPK_FLAG_NOTCOMPRESSED) != CPK_FLAG_NOTCOMPRESSED;
    pFile->dwOffset = dwOffset;
    pFile->dwFileSize = pEntry->dwOriginSize;
    pFile->dwPointer = 0;

    if (pFile->bCompressed == 1 && pEntry->dwOriginSize) {
        // Decompress
        void* lpDecompressed = malloc(pEntry->dwOriginSize);
        pFile->lpRealData = lpDecompressed;
        if (!lpDecompressed) {
            if (m_eMode == CPKM_FileMapping)
                UnmapViewOfFile(pFile->lpMapAddress);
            pFile->bValid = 0;
            return NULL;
        }
        // Decompress from lpStartAddress to lpRealData
        DeCompress(lpDecompressed, pFile->lpStartAddress, pEntry->dwPackedSize);
    } else {
        pFile->lpRealData = pFile->lpStartAddress;
    }

    if (m_eMode != CPKM_FileMapping) {
        // Normal mode: seek to file start
        SetFilePointer((HANDLE)m_dwCPKHandle, pEntry->dwStartPos, NULL, FILE_BEGIN);
    }

    m_nOpenedFileNum++;
    return pFile;
}

bool CPK::Close(CPKFile* pFile)
{
    if (m_eMode == CPKM_FileMapping) {
        if (!pFile->lpMapAddress)
            return 0;
        UnmapViewOfFile(pFile->lpMapAddress);
        if (pFile->bCompressed && pFile->lpRealData) {
            free(pFile->lpRealData);
        }
    }
    pFile->bValid = 0;
    m_nOpenedFileNum--;
    return 1;
}

bool CPK::Read(void* buffer, unsigned long size, CPKFile* pFile)
{
    if (m_eMode == CPKM_FileMapping) {
        memcpy(buffer, (char*)pFile->lpRealData + pFile->dwPointer, size);
    } else {
        DWORD bytesRead;
        ReadFile((HANDLE)m_dwCPKHandle, buffer, size, &bytesRead, NULL);
    }
    pFile->dwPointer += size;
    return 1;
}

int CPK::ReadChar(CPKFile* pFile)
{
    unsigned char ch;
    if (Read(&ch, 1, pFile))
        return (int)ch;
    return -1;
}

char* CPK::ReadLine(char* buffer, int maxLen, CPKFile* pFile)
{
    if (!pFile || !pFile->bValid || !buffer || maxLen <= 0)
        return NULL;

    int i = 0;
    while (i < maxLen - 1) {
        if (pFile->dwPointer >= pFile->dwFileSize) {
            if (i == 0) return NULL;
            break;
        }
        int ch = ReadChar(pFile);
        if (ch == -1) {
            if (i == 0) return NULL;
            break;
        }
        buffer[i] = (char)ch;
        if (ch == '\n' && i >= 1 && buffer[i - 1] == '\r')
            break;
        i++;
    }
    if (i > 0)
        buffer[i] = '\0';
    else
        return NULL;

    return buffer;
}

unsigned long CPK::LoadFile(void* buffer, const char* filename)
{
    if (!buffer || !filename)
        return 0;

    CPKFile* pFile = Open(filename);
    if (!pFile)
        return 0;

    unsigned long fileSize = pFile->dwFileSize;

    void* pData = pFile->GetRealData();
    if (pData) {
        memcpy(buffer, pData, fileSize);
    } else {
        fileSize = 0;
    }

    Close(pFile);
    return fileSize;
}

unsigned long CPK::Compress(void* dst, void* src, unsigned long srcLen)
{
    unsigned long dstLen = 0;
    unsigned char* workMem = (unsigned char*)malloc(LZO1X_1_MEM_COMPRESS);
    if (!workMem)
        return 0;

    int result = lzo1x_1_compress((const unsigned char*)src, srcLen,
                                  (unsigned char*)dst, &dstLen, workMem);
    free(workMem);

    if (result != 0)
        return 0;

    return dstLen;
}

unsigned long CPK::DeCompress(void* dst, void* src, unsigned long srcLen)
{
    unsigned long dstLen = 0;

    int result = lzo1x_decompress((const unsigned char*)src, srcLen,
                                  (unsigned char*)dst, &dstLen, NULL);

    if (result != 0)
        return 0;

    return dstLen;
}

unsigned long CPK::GetSize(CPKFile* pFile)
{
    return pFile->dwFileSize;
}

unsigned long CPK::GetCPKHandle()
{
    return m_dwCPKHandle;
}

unsigned long CPK::Tell(CPKFile* pFile)
{
    return pFile->dwPointer;
}

void CPK::Rewind(CPKFile* pFile)
{
    pFile->dwPointer = 0;
}

unsigned long CPK::Seek(CPKFile* pFile, int offset, unsigned long origin)
{
    int newPos;
    if (origin == 0) {      // SEEK_SET
        newPos = offset;
    } else if (origin == 1) { // SEEK_CUR
        newPos = offset + (int)pFile->dwPointer;
    } else if (origin == 2) { // SEEK_END
        newPos = (int)pFile->dwFileSize - offset;
    } else {
        return (unsigned long)-1;
    }

    pFile->dwPointer = (unsigned long)newPos;

    if (m_eMode != CPKM_FileMapping) {
        SetFilePointer((HANDLE)m_dwCPKHandle, pFile->dwPointer + pFile->pTableItem->dwStartPos, NULL, FILE_BEGIN);
    }

    return pFile->dwPointer;
}

int CPK::GetTableIndex(const char* filename)
{
    if (!filename)
        return -1;

    char lowerName[260];
    lstrcpyA(lowerName, filename);
    _strlwr(lowerName);

    unsigned long crc = Crc(lowerName);
    return GetTableIndexFromCRC(crc);
}

int CPK::GetTableIndexFromCRC(unsigned long crc)
{
    for (unsigned long i = 0; i < m_CPKHeader.dwValidTableNum; i++) {
        if (m_CPKTable[i].dwCRC == crc) {
            return (int)i;
        }
    }
    return -1;
}

unsigned long CPK::GetAllocationGranularity()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwAllocationGranularity;
}

bool CPK::IsDir(unsigned long crc)
{
    if (crc == 0) {
        return true;
    }

    int lo = 0;
    int hi = m_CPKHeader.dwValidTableNum;
    int idx;
    if (hi != 0) {
        do {
            idx = (hi - lo) / 2 + lo;
            if (crc == m_CPKTable[idx].dwCRC &&
                (m_CPKTable[idx].dwFlag & CPK_FLAG_ISFILE) &&
                !(m_CPKTable[idx].dwFlag & CPK_FLAG_ISDELETED))
                goto found;
            if (hi == lo + 1) break;
            if (crc >= m_CPKTable[idx].dwCRC) {
                lo = idx;
            } else {
                hi = idx;
            }
        } while (hi != lo);
    }
    idx = -1;
found:
    return (m_CPKTable[idx].dwFlag >> 1) & 1;
}


// ############################################################################
//  gbVFile Implementation
// ############################################################################

gbVFile::gbVFile()
{
}

gbVFile::~gbVFile()
{
}

gbVFile& gbVFile::operator=(const gbVFile& other)
{
    memcpy(this, &other, sizeof(gbVFile));
    return *this;
}


// ############################################################################
//  gbVFile1 Implementation
// ############################################################################

gbVFile1& gbVFile1::operator=(const gbVFile1& other)
{
    memcpy(this, &other, sizeof(gbVFile1));
    return *this;
}

char* gbVFile1::GetFullPath()
{
    return fullPath;
}

char* gbVFile1::GetFileName(char* buf, int bufLen)
{
    if (!buf || bufLen <= 0)
        return NULL;

    const char* p = strrchr(fullPath, '\\');
    const char* p2 = strrchr(fullPath, '/');
    if (p2 > p) p = p2;

    if (p) {
        p++;
    } else {
        p = fullPath;
    }

    strncpy(buf, p, bufLen - 1);
    buf[bufLen - 1] = '\0';
    return buf;
}

char* gbVFile1::GetDir(char* buf, int bufLen)
{
    if (!buf || bufLen <= 0)
        return NULL;

    const char* p = strrchr(fullPath, '\\');
    const char* p2 = strrchr(fullPath, '/');
    if (p2 > p) p = p2;

    if (p) {
        int len = (int)(p - fullPath);
        if (len >= bufLen) len = bufLen - 1;
        strncpy(buf, fullPath, len);
        buf[len] = '\0';
    } else {
        buf[0] = '\0';
    }

    return buf;
}

char* gbVFile1::GetTitle(char* buf, int bufLen)
{
    if (!buf || bufLen <= 0)
        return NULL;

    char filename[260];
    GetFileName(filename, sizeof(filename));

    char* dot = strrchr(filename, '.');
    if (dot) {
        int len = (int)(dot - filename);
        if (len >= bufLen) len = bufLen - 1;
        strncpy(buf, filename, len);
        buf[len] = '\0';
    } else {
        strncpy(buf, filename, bufLen - 1);
        buf[bufLen - 1] = '\0';
    }

    return buf;
}


// ############################################################################
//  gbVFileSystem Implementation
// ############################################################################

gbVFileSystem::gbVFileSystem()
{
    // CPK constructor called automatically for m_cpk
    IsInit = 0;
    m_pckfp = NULL;
}

gbVFileSystem::~gbVFileSystem()
{
    Release();
}

gbVFileSystem& gbVFileSystem::operator=(const gbVFileSystem& other)
{
    memcpy(this, &other, sizeof(gbVFileSystem));
    return *this;
}

// Helper: allocate gbVFile array (16 entries, each 0x140 bytes)
// Original uses 'eh vector constructor iterator' with count prefix
static gbVFile* AllocFileBuffer()
{
    // Allocate: 4 bytes (count) + 16 * sizeof(gbVFile) = 0x1404
    unsigned char* raw = (unsigned char*)operator new(0x1404u);
    if (raw) {
        gbVFile* arr = (gbVFile*)(raw + 4);
        *(unsigned long*)raw = 16;  // count prefix
        // Call constructor on each element
        for (int i = 0; i < 16; i++) {
            arr[i].flags = 0;
            arr[i].cpkFile.lpRealData = 0;
        }
        return arr;
    }
    return NULL;
}

static void FreeFileBuffer(gbVFile* arr)
{
    if (arr) {
        unsigned char* raw = (unsigned char*)arr - 4;
        // Call destructor on each element
        for (int i = 0; i < 16; i++) {
            arr[i].~gbVFile();
        }
        operator delete(raw);
    }
}

int gbVFileSystem::Init(char* lpFileName)
{
    if (lpFileName && *lpFileName) {
        if (!strcmp(lpFileName, "MemImage")) {
            rtDirectory = NULL;
            Type = VFSYS_MEMIMAGE;
            pFileBuffer = AllocFileBuffer();
            for (int i = 0; i < 16; i++) {
                pFileBuffer[i].flags = 0;
            }
        } else {
            int len = (int)strlen(lpFileName) + 10;
            if (len < 256)
                len = 256;
            rtDirectory = (char*)malloc(len);
            strcpy(rtDirectory, lpFileName);

            DWORD attr = GetFileAttributesA(lpFileName);
            if (attr == (DWORD)-1)
                return 0;

            if (attr & FILE_ATTRIBUTE_DIRECTORY) {
                // Directory mode: ensure trailing separator
                unsigned int slen = strlen(lpFileName) + 1;
                char lastChar = lpFileName[slen - 2];
                if (lastChar != '\\' && lastChar != '/') {
                    rtDirectory[slen - 1] = '/';
                    rtDirectory[slen] = '\0';
                }
                Type = VFSYS_DISKFILE;
                pFileBuffer = AllocFileBuffer();
                for (int i = 0; i < 16; i++) {
                    pFileBuffer[i].flags = 0;
                }
            } else {
                // File mode: load as CPK
                Type = VFSYS_PACKFILE;
                if (!m_cpk.Load(lpFileName))
                    return 0;
            }
        }
    } else {
        // NULL or empty path: default disk mode
        rtDirectory = NULL;
        Type = VFSYS_DISKFILE;
        pFileBuffer = AllocFileBuffer();
        for (int i = 0; i < 16; i++) {
            pFileBuffer[i].flags = 0;
        }
    }

    IsInit = 1;
    return 1;
}

void gbVFileSystem::Release()
{
    if (rtDirectory)
        free(rtDirectory);

    if (pFileBuffer)
        FreeFileBuffer(pFileBuffer);

    if (m_pckfp)
        fclose(m_pckfp);

    IsInit = 0;
    m_cpk.Unload();
}

gbVFile* gbVFileSystem::NewFileEntry()
{
    int i = 0;
    gbVFile* p = pFileBuffer;
    while (p->flags) {
        if (++i >= 16)
            return NULL;
        p++;
    }
    return &pFileBuffer[i];
}

void gbVFileSystem::DelFileEntry(gbVFile* pFile)
{
    pFile->flags = 0;
}

gbVFile* gbVFileSystem::OpenFile(const char* filename, unsigned int openFlags)
{
    if (Type == VFSYS_PACKFILE) {
        CPKFile* cpkFile = m_cpk.Open(filename);
        if (cpkFile) {
            // CPKFile is embedded in the 0x140 block at offset 272
            // The gbVFile is at block_start = (char*)cpkFile - 272
            gbVFile* result = (gbVFile*)((char*)cpkFile - 272);
            if (result)
                result->fp = (void*)openFlags;  // store flags at fp field
            return result;
        }
        return NULL;
    }

    if (Type == VFSYS_MEMIMAGE) {
        // Find free slot
        int i = 0;
        gbVFile* p = pFileBuffer;
        while (p->flags) {
            if (++i >= 16)
                return NULL;
            p++;
        }
        gbVFile* entry = &pFileBuffer[i];
        if (entry) {
            strcpy(entry->fullPath, filename);
            entry->bufSize = 256;
            entry->flags = openFlags;
            void* buf = malloc(0x100);
            entry->fp = buf;
            entry->memPtr = buf;
            return entry;
        }
        return NULL;
    }

    // VFSYS_DISKFILE
    int i = 0;
    gbVFile* p = pFileBuffer;
    while (p->flags) {
        if (++i >= 16)
            return NULL;
        p++;
    }
    gbVFile* entry = &pFileBuffer[i];
    if (!entry)
        return NULL;

    strcpy(entry->fullPath, filename);

    // Build full path
    char fullPath[256];
    if (rtDirectory) {
        strcpy(fullPath, rtDirectory);
        strcat(fullPath, filename);
    } else {
        strcpy(fullPath, filename);
    }

    // Determine fopen mode
    char mode[4];
    strcpy(mode, "rb");
    if (openFlags & 2)
        mode[0] = 'w';
    if (openFlags & 0x400)
        mode[1] = 't';

    FILE* fp = fopen(fullPath, mode);
    if (fp) {
        entry->fp = fp;
        entry->flags = openFlags;
        return entry;
    } else {
        entry->flags = 0;
    }
    return NULL;
}

void gbVFileSystem::CloseFile(gbVFile* pFile)
{
    if (Type == VFSYS_PACKFILE) {
        if (pFile)
            m_cpk.Close(&pFile->cpkFile);
        else
            m_cpk.Close(NULL);
    } else if (Type == VFSYS_MEMIMAGE) {
        free(pFile->fp);
        pFile->flags = 0;
    } else {
        // VFSYS_DISKFILE
        fclose((FILE*)pFile->fp);
        pFile->flags = 0;
    }
}

void gbVFileSystem::Read(void* buffer, unsigned int size, gbVFile* pFile)
{
    if (Type == VFSYS_PACKFILE) {
        CPKFile* cpk = pFile ? &pFile->cpkFile : NULL;
        m_cpk.Read(buffer, size, cpk);
    } else if (Type == VFSYS_MEMIMAGE) {
        memcpy(buffer, pFile->memPtr, size);
        pFile->memPtr = (char*)pFile->memPtr + size;
    } else {
        // VFSYS_DISKFILE
        if (fread(buffer, size, 1, (FILE*)pFile->fp) != 1) {
            gbLogInfo("Error on read file,path=%s\r\n", pFile->fullPath);
        }
    }
}

void gbVFileSystem::Write(void* buffer, unsigned int size, gbVFile* pFile)
{
    if (Type == VFSYS_DISKFILE) {
        fwrite(buffer, size, 1, (FILE*)pFile->fp);
    } else if (Type == VFSYS_MEMIMAGE) {
        unsigned int offset = (unsigned int)((char*)pFile->memPtr - (char*)pFile->fp);
        unsigned int needed = size + offset;
        if (needed > pFile->bufSize) {
            pFile->bufSize = 2 * needed;
            void* newBuf = malloc(2 * needed);
            memcpy(newBuf, pFile->fp, offset);
            void* oldBuf = pFile->fp;
            free(oldBuf);
            pFile->fp = newBuf;
            pFile->memPtr = (char*)newBuf + offset;
        }
        memcpy(pFile->memPtr, buffer, size);
        pFile->memPtr = (char*)pFile->memPtr + size;
    }
}

int gbVFileSystem::ReadChar(gbVFile* pFile)
{
    int t = Type;
    if (t == VFSYS_PACKFILE) {
        CPKFile* cpk = pFile ? &pFile->cpkFile : NULL;
        return m_cpk.ReadChar(cpk);
    } else if (!t) {
        return fgetc((FILE*)pFile->fp);
    } else {
        if (t == VFSYS_MEMIMAGE) {
            char* ptr = (char*)pFile->memPtr;
            int result = (unsigned char)*ptr;
            pFile->memPtr = ptr + 1;
            return result;
        } else {
            return -1;
        }
    }
}

char* gbVFileSystem::ReadLine(char* buffer, int maxLen, gbVFile* pFile)
{
    if (Type == VFSYS_PACKFILE) {
        CPKFile* cpk = pFile ? &pFile->cpkFile : NULL;
        return m_cpk.ReadLine(buffer, maxLen, cpk);
    } else if (Type == VFSYS_MEMIMAGE) {
        int i = 0;
        if (maxLen - 1 <= 0)
            return NULL;
        char* result = buffer;
        do {
            if ((unsigned int)((char*)pFile->memPtr - (char*)pFile->fp) >= pFile->bufSize)
                break;
            buffer[i] = *(char*)pFile->memPtr;
            pFile->memPtr = (char*)pFile->memPtr + 1;
            if (buffer[i] == '\n' && i >= 1 && buffer[i - 1] == '\r')
                break;
            i++;
        } while (i < maxLen - 1);
        if (i > 0)
            buffer[i] = '\0';
        else
            return NULL;
        return result;
    } else {
        // VFSYS_DISKFILE
        return fgets(buffer, maxLen, (FILE*)pFile->fp);
    }
}

void gbVFileSystem::Seek(gbVFile* pFile, long offset, int origin)
{
    if (Type == VFSYS_PACKFILE) {
        CPKFile* cpk = pFile ? &pFile->cpkFile : NULL;
        switch (origin) {
            case 1: // GBVFS_SEEK_SET
                m_cpk.Seek(cpk, offset, 0);
                break;
            case 2: // GBVFS_SEEK_CUR
                m_cpk.Seek(cpk, offset, 1);
                break;
            case 3: // GBVFS_SEEK_END
                m_cpk.Seek(cpk, offset, 2);
                break;
        }
    } else if (Type == VFSYS_MEMIMAGE) {
        switch (origin) {
            case 1: // GBVFS_SEEK_SET
                pFile->memPtr = (char*)pFile->fp + offset;
                break;
            case 2: // GBVFS_SEEK_CUR
                pFile->memPtr = (char*)pFile->memPtr + offset;
                break;
            case 3: // GBVFS_SEEK_END
                pFile->memPtr = (char*)pFile->fp + pFile->bufSize - offset;
                break;
        }
    } else {
        // VFSYS_DISKFILE: translate custom origin to stdio
        int stdOrigin = origin;
        switch (origin) {
            case 1: stdOrigin = SEEK_SET; break;
            case 2: stdOrigin = SEEK_CUR; break;
            case 3: stdOrigin = SEEK_END; break;
        }
        fseek((FILE*)pFile->fp, offset, stdOrigin);
    }
}

void gbVFileSystem::Rewind(gbVFile* pFile)
{
    int t = Type;
    if (t == VFSYS_PACKFILE) {
        CPKFile* cpk = pFile ? &pFile->cpkFile : NULL;
        cpk->dwPointer = 0;
    } else if (!t) {
        rewind((FILE*)pFile->fp);
    } else {
        if (t == VFSYS_MEMIMAGE) {
            pFile->memPtr = pFile->fp;
        }
    }
}

long gbVFileSystem::TellPos(gbVFile* pFile)
{
    int t = Type;
    if (t == VFSYS_PACKFILE) {
        CPKFile* cpk = pFile ? &pFile->cpkFile : NULL;
        return (long)cpk->dwPointer;
    } else if (!t) {
        return ftell((FILE*)pFile->fp);
    } else {
        if (t == VFSYS_MEMIMAGE) {
            return (long)((char*)pFile->memPtr - (char*)pFile->fp);
        } else {
            return -1;
        }
    }
}

long gbVFileSystem::GetFileSize(gbVFile* pFile)
{
    if (Type == VFSYS_PACKFILE) {
        if (pFile)
            return (long)pFile->cpkFile.dwFileSize;
        else
            return 0;
    } else if (Type == VFSYS_MEMIMAGE) {
        return (long)pFile->bufSize;
    } else {
        // VFSYS_DISKFILE: seek to end, get position, seek back
        Seek(pFile, 0, GBVFS_SEEK_END);
        long size = TellPos(pFile);
        Seek(pFile, 0, GBVFS_SEEK_SET);
        return size;
    }
}

int gbVFileSystem::FileExistNum(char* filename)
{
    if (Type == VFSYS_PACKFILE) {
        return m_cpk.IsFileExist(filename);
    }

    if (Type != VFSYS_DISKFILE)
        return 0;

    // Build full path
    char fullPath[256];
    if (rtDirectory) {
        strcpy(fullPath, rtDirectory);
        strcat(fullPath, filename);
    } else {
        strcpy(fullPath, filename);
    }

    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(fullPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE)
        return 0;

    int count = 1;
    while (FindNextFileA(hFind, &findData))
        count++;

    FindClose(hFind);
    return count;
}

int gbVFileSystem::FindItem(const char* filename)
{
    int lo = 0;
    int hi = m_itemcount;
    if (hi < 0)
        return -1;

    while (1) {
        int mid = (hi + lo) / 2;
        int cmp = gbstricmp(filename, pFileBuffer[mid].fullPath);
        if (!cmp)
            break;
        if (cmp < 0)
            hi = mid - 1;
        else
            lo = mid + 1;
        if (lo > hi)
            return -1;
    }
    if (lo <= hi)
        return (hi + lo) / 2;
    else
        return -1;
}


// ############################################################################
//  CIniFile Implementation
// ############################################################################

CIniFile::CIniFile()
{
    m_pFile = NULL;
    m_nState = -1;
}

CIniFile::~CIniFile()
{
    if (m_pFile) {
        g_pVFileSys->CloseFile(m_pFile);
        m_pFile = NULL;
        m_nState = -1;
    }
}

CIniFile& CIniFile::operator=(const CIniFile& other)
{
    m_pFile = other.m_pFile;
    m_nState = other.m_nState;
    return *this;
}

int CIniFile::OpenFileRead(const char* filename)
{
    if (!g_pVFileSys || !filename)
        return 0;

    m_pFile = g_pVFileSys->OpenFile(filename, 0x401);
    if (m_pFile) {
        m_nState = 0;
        return 1;
    }
    return 0;
}

int CIniFile::OpenFileWrite(const char* filename)
{
    if (!g_pVFileSys || !filename)
        return 0;

    m_pFile = g_pVFileSys->OpenFile(filename, 0x402);
    if (m_pFile) {
        m_nState = 1;
        return 1;
    }
    return 0;
}

void CIniFile::CloseFile()
{
    if (m_pFile && g_pVFileSys) {
        g_pVFileSys->CloseFile(m_pFile);
        m_pFile = NULL;
    }
    m_nState = -1;
}

int CIniFile::ReadSection(char* sectionName)
{
    if (!m_pFile || !g_pVFileSys || !sectionName)
        return 0;

    char line[512];
    while (g_pVFileSys->ReadLine(line, sizeof(line), m_pFile) != NULL) {
        char* p = line;
        while (*p == ' ' || *p == '\t') p++;

        if (*p == '[') {
            p++;
            char* end = strchr(p, ']');
            if (end) {
                *end = '\0';
                if (_stricmp(p, sectionName) == 0) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void CIniFile::ReadStart()
{
    if (m_pFile && g_pVFileSys) {
        g_pVFileSys->Rewind(m_pFile);
    }
}

int CIniFile::ReadLine(const char* key, char* value, int maxLen)
{
    if (!m_pFile || !g_pVFileSys || !key || !value)
        return 0;

    char line[512];
    if (g_pVFileSys->ReadLine(line, sizeof(line), m_pFile) == NULL)
        return 0;

    char* p = line;
    while (*p == ' ' || *p == '\t') p++;

    int keyLen = (int)strlen(key);
    if (_strnicmp(p, key, keyLen) != 0)
        return 0;

    p += keyLen;
    while (*p == ' ' || *p == '\t') p++;
    if (*p == '=') p++;
    while (*p == ' ' || *p == '\t') p++;

    strncpy(value, p, maxLen - 1);
    value[maxLen - 1] = '\0';

    int len = (int)strlen(value);
    while (len > 0 && (value[len - 1] == ' ' || value[len - 1] == '\t' ||
                       value[len - 1] == '\r' || value[len - 1] == '\n')) {
        value[--len] = '\0';
    }

    return 1;
}

int CIniFile::ReadLine(const char* key, int* value)
{
    char buf[256];
    if (ReadLine(key, buf, sizeof(buf))) {
        *value = atoi(buf);
        return 1;
    }
    return 0;
}

int CIniFile::ReadLine(const char* key, float* value)
{
    char buf[256];
    if (ReadLine(key, buf, sizeof(buf))) {
        *value = (float)atof(buf);
        return 1;
    }
    return 0;
}

int CIniFile::ReadLine(const char* key, double* value)
{
    char buf[256];
    if (ReadLine(key, buf, sizeof(buf))) {
        *value = atof(buf);
        return 1;
    }
    return 0;
}

void CIniFile::WriteSection(const char* section)
{
    FILE* fp = (FILE*)m_pFile->fp;
    fprintf(fp, "[%s]\r\n", section);
}

void CIniFile::WriteLine(const char* key, const char* value)
{
    FILE* fp = (FILE*)m_pFile->fp;
    fprintf(fp, "%s=%s\r\n", key, value);
}

void CIniFile::WriteLine(const char* key, int value)
{
    FILE* fp = (FILE*)m_pFile->fp;
    fprintf(fp, "%s=%d\r\n", key, value);
}

void CIniFile::WriteLine(const char* key, float value)
{
    FILE* fp = (FILE*)m_pFile->fp;
    fprintf(fp, "%s=%f\r\n", key, (double)value);
}

void CIniFile::WriteLine(const char* key, double value)
{
    FILE* fp = (FILE*)m_pFile->fp;
    fprintf(fp, "%s=%f\r\n", key, value);
}

void CIniFile::WriteLineSeperator()
{
    FILE* fp = (FILE*)m_pFile->fp;
    fprintf(fp, "\r\n");
}

int CIniFile::IfRead()
{
    return m_nState;
}

gbVFile* CIniFile::GetFilePointer()
{
    return m_pFile;
}


// ############################################################
// gbVTextFile Implementation
// ############################################################

#pragma auto_inline(off)

class gbVTextFile {
public:
    char lineBuf[0x400];
    gbVFile* m_pFile;

public:
    gbVTextFile(char* p0);
    gbVTextFile();
    ~gbVTextFile();
    gbVTextFile& operator=(const gbVTextFile& other);
    void Close();
    void Open(char* p0);
    char* ReadLine();
    void Rewind();
};

gbVTextFile::gbVTextFile(char* p0) {
    m_pFile = g_pVFileSys->OpenFile(p0, 0x401);
}

gbVTextFile::gbVTextFile() {
    m_pFile = NULL;
}

gbVTextFile& gbVTextFile::operator=(const gbVTextFile& other) {
    if (this != &other) {
        Close();
        memcpy(lineBuf, other.lineBuf, sizeof(lineBuf));
        m_pFile = other.m_pFile;
    }
    return *this;
}

char* gbVTextFile::ReadLine() {
    if (!m_pFile || !g_pVFileSys)
        return NULL;

    char* result = g_pVFileSys->ReadLine(lineBuf, sizeof(lineBuf) - 1, m_pFile);
    if (!result)
        return NULL;

    int len = (int)strlen(lineBuf);
    while (len > 0 && (lineBuf[len - 1] == '\n' || lineBuf[len - 1] == '\r')) {
        lineBuf[--len] = '\0';
    }

    return lineBuf;
}

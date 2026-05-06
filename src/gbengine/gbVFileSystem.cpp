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

#ifndef INVALID_SET_FILE_POINTER
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
#endif
#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif

// LZO stub implementations (real LZO will be linked at final integration)
extern "C" {
    int lzo1x_1_compress(const unsigned char* src, unsigned long src_len,
                         unsigned char* dst, unsigned long* dst_len,
                         void* wrkmem)
    {
        memcpy(dst, src, src_len);
        *dst_len = src_len;
        return 0;
    }

    int lzo1x_decompress(const unsigned char* src, unsigned long src_len,
                         unsigned char* dst, unsigned long* dst_len,
                         void* wrkmem)
    {
        memcpy(dst, src, src_len);
        *dst_len = src_len;
        return 0;
    }
}

// LZO work memory size
#define LZO1X_1_MEM_COMPRESS (16384 * sizeof(unsigned char*))

// Static member definitions
int CPK::s_bCrcTableInitialized = 0;

// Global pointer to the virtual file system
gbVFileSystem* g_pVFileSys = NULL;


// ############################################################################
//
//  IMPLEMENTATION
//
// ############################################################################


// ============================================================================
// CPKFile Implementation
// ============================================================================

CPKFile::CPKFile()
{
    memset(this, 0, sizeof(CPKFile));
}

CPKFile::~CPKFile()
{
    // Trivial destructor - memory is managed by CPK
}

CPKFile& CPKFile::operator=(const CPKFile& other)
{
    if (this != &other) {
        memcpy(this, &other, sizeof(CPKFile));
    }
    return *this;
}

void* CPKFile::GetRealData()
{
    if (!bValid)
        return NULL;

    // If we have decompressed data in memory, return it
    if (lpMem)
        return lpMem;

    // Otherwise return the mapped start address
    return lpStartAddress;
}


// ============================================================================
// CPK Implementation
// ============================================================================

CPK::CPK()
{
    // Zero the entire structure
    memset(this, 0, sizeof(CPK));

    // Default open mode is FileMapping
    m_eMode = CPKM_FileMapping;

    // Get system allocation granularity
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    m_dwAllocGranularity = si.dwAllocationGranularity;

    // Initialize CRC table if not done yet
    if (!s_bCrcTableInitialized) {
        InitCrcTable();
    }

    // Allocate CPKFile handles
    for (int i = 0; i < CPK_MAX_OPEN_FILES; i++) {
        m_pCPKFile[i] = new CPKFile();
    }
}

CPK::~CPK()
{
    Unload();

    // Free CPKFile handles
    for (int i = 0; i < CPK_MAX_OPEN_FILES; i++) {
        if (m_pCPKFile[i]) {
            delete m_pCPKFile[i];
            m_pCPKFile[i] = NULL;
        }
    }
}

CPK& CPK::operator=(const CPK& other)
{
    if (this != &other) {
        memcpy(this, &other, sizeof(CPK));
    }
    return *this;
}

void CPK::InitCrcTable()
{
    // Standard CRC32 table generation with polynomial 0x04C11DB7
    unsigned long v0 = 0;
    unsigned long* v1 = CrcTable;
    unsigned long v2;
    unsigned long v3;
    do {
        v2 = 8;
        v3 = v0 << 24;
        do {
            if (v3 & 0x80000000) {
                v3 = (v3 << 1) ^ 0x04C11DB7;
            } else {
                v3 <<= 1;
            }
            --v2;
        } while (v2);
        *v1 = v3;
        ++v1;
        ++v0;
    } while (v1 < CrcTable + 256);

    s_bCrcTableInitialized = 1;
}

unsigned long CPK::Crc(const char* str)
{
    unsigned char* s = (unsigned char*)str;
    unsigned long x = 0;
    int i;

    // Process first 4 bytes
    for (i = 0; i < 4; i++) {
        x = (x << 8);
        if (*s) x |= *s++;
    }
    x = ~x;

    // Process remaining bytes
    while (*s) {
        x = CrcTable[x >> 24] ^ (*s++ | (x << 8));
    }

    return ~x;
}

bool CPK::Load(const char* filename)
{
    if (m_bLoaded)
        return 0;

    // Open the CPK file
    HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return 0;

    m_dwCPKHandle = (unsigned long)hFile;

    // Read the header
    DWORD bytesRead = 0;
    ReadFile(hFile, &m_CPKHeader, sizeof(CPKHeader), &bytesRead, NULL);
    if (bytesRead != sizeof(CPKHeader)) {
        CloseHandle(hFile);
        m_dwCPKHandle = 0;
        return 0;
    }

    // Validate magic number
    if (m_CPKHeader.dwLable != CPK_LABEL) {
        CloseHandle(hFile);
        m_dwCPKHandle = 0;
        return 0;
    }

    // Seek to file table
    SetFilePointer(hFile, m_CPKHeader.dwTableStart, NULL, FILE_BEGIN);

    // Read the file table
    unsigned long tableSize = m_CPKHeader.dwValidTableNum * sizeof(CPKTable);
    ReadFile(hFile, m_CPKTable, tableSize, &bytesRead, NULL);
    if (bytesRead != tableSize) {
        CloseHandle(hFile);
        m_dwCPKHandle = 0;
        return 0;
    }

    // Create file mapping for memory-mapped I/O
    if (m_eMode == CPKM_FileMapping) {
        HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
        m_dwCPKMappingHandle = (unsigned long)hMapping;
    }

    // Store filename
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

    // Close all open files
    for (int i = 0; i < CPK_MAX_OPEN_FILES; i++) {
        if (m_pCPKFile[i] && m_pCPKFile[i]->bValid) {
            Close(m_pCPKFile[i]);
        }
    }

    // Close file mapping
    if (m_dwCPKMappingHandle) {
        CloseHandle((HANDLE)m_dwCPKMappingHandle);
        m_dwCPKMappingHandle = 0;
    }

    // Close file handle
    if (m_dwCPKHandle) {
        CloseHandle((HANDLE)m_dwCPKHandle);
        m_dwCPKHandle = 0;
    }

    m_bLoaded = 0;
    Reset();

    return 1;
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

void CPK::SetOpenMode(ECPKMode mode)
{
    m_eMode = mode;
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

    // Convert filename to lowercase for CRC computation
    char lowerName[260];
    strncpy(lowerName, filename, sizeof(lowerName) - 1);
    lowerName[sizeof(lowerName) - 1] = '\0';
    _strlwr(lowerName);

    // Compute CRC and look up in table
    unsigned long crc = Crc(lowerName);

    for (unsigned long i = 0; i < m_CPKHeader.dwValidTableNum; i++) {
        if (m_CPKTable[i].dwCRC == crc) {
            // Check it's a file and not deleted
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

    // Find a free CPKFile handle
    CPKFile* pFile = NULL;
    int handleIndex = -1;
    for (int i = 0; i < CPK_MAX_OPEN_FILES; i++) {
        if (m_pCPKFile[i] && !m_pCPKFile[i]->bValid) {
            pFile = m_pCPKFile[i];
            handleIndex = i;
            break;
        }
    }

    if (!pFile)
        return NULL;  // No free handles

    // Look up the file in the table
    int tableIndex = GetTableIndex(filename);
    if (tableIndex < 0)
        return NULL;

    CPKTable* pEntry = &m_CPKTable[tableIndex];

    // Check it's a valid file entry
    if (!(pEntry->dwFlag & CPK_FLAG_ISFILE))
        return NULL;
    if (pEntry->dwFlag & CPK_FLAG_ISDELETED)
        return NULL;

    // Initialize the CPKFile handle
    memset(pFile, 0, sizeof(CPKFile));
    pFile->bValid = 1;
    pFile->dwCRC = pEntry->dwCRC;
    pFile->dwFatherCRC = pEntry->dwFatherCRC;
    pFile->nTableIndex = tableIndex;
    pFile->pTableItem = pEntry;
    pFile->dwFileSize = pEntry->dwOriginSize;
    pFile->dwPointer = 0;

    // Check if the file is compressed
    pFile->bCompressed = (pEntry->dwFlag & CPK_FLAG_NOTCOMPRESSED) ? 0 : 1;

    if (m_eMode == CPKM_FileMapping) {
        // Memory-mapped I/O: map the relevant portion
        unsigned long dwStartPos = pEntry->dwStartPos;
        unsigned long dwAlignedStart = (dwStartPos / m_dwAllocGranularity) * m_dwAllocGranularity;
        unsigned long dwOffset = dwStartPos - dwAlignedStart;
        unsigned long dwMapSize = pEntry->dwPackedSize + dwOffset;

        void* lpMapAddr = MapViewOfFile((HANDLE)m_dwCPKMappingHandle,
                                        FILE_MAP_READ,
                                        0, dwAlignedStart, dwMapSize);
        if (!lpMapAddr) {
            pFile->bValid = 0;
            return NULL;
        }

        pFile->lpMapAddress = lpMapAddr;
        pFile->lpStartAddress = (unsigned char*)lpMapAddr + dwOffset;
        pFile->dwOffset = dwOffset;

        // If compressed, decompress into memory
        if (pFile->bCompressed) {
            void* lpDecompressed = malloc(pEntry->dwOriginSize);
            if (!lpDecompressed) {
                UnmapViewOfFile(lpMapAddr);
                pFile->bValid = 0;
                return NULL;
            }
            DeCompress(lpDecompressed, pFile->lpStartAddress, pEntry->dwPackedSize);
            pFile->lpMem = lpDecompressed;
        }
    } else {
        // Normal I/O: read via ReadFile
        HANDLE hFile = (HANDLE)m_dwCPKHandle;
        SetFilePointer(hFile, pEntry->dwStartPos, NULL, FILE_BEGIN);

        void* lpData = malloc(pEntry->dwPackedSize);
        if (!lpData) {
            pFile->bValid = 0;
            return NULL;
        }

        DWORD bytesRead = 0;
        ReadFile(hFile, lpData, pEntry->dwPackedSize, &bytesRead, NULL);

        if (pFile->bCompressed) {
            void* lpDecompressed = malloc(pEntry->dwOriginSize);
            if (!lpDecompressed) {
                free(lpData);
                pFile->bValid = 0;
                return NULL;
            }
            DeCompress(lpDecompressed, lpData, pEntry->dwPackedSize);
            free(lpData);
            pFile->lpMem = lpDecompressed;
            pFile->lpStartAddress = lpDecompressed;
        } else {
            pFile->lpMem = lpData;
            pFile->lpStartAddress = lpData;
        }
    }

    m_nOpenedFileNum++;
    return pFile;
}

bool CPK::Close(CPKFile* pFile)
{
    if (!pFile || !pFile->bValid)
        return 0;

    // Unmap memory-mapped view
    if (m_eMode == CPKM_FileMapping && pFile->lpMapAddress) {
        UnmapViewOfFile(pFile->lpMapAddress);
        pFile->lpMapAddress = NULL;
    }

    // Free decompressed data buffer
    if (pFile->lpMem) {
        free(pFile->lpMem);
        pFile->lpMem = NULL;
    }

    // If normal mode and not compressed, the start address was allocated
    if (m_eMode != CPKM_FileMapping && !pFile->bCompressed && pFile->lpStartAddress) {
        // Already freed via lpMem above in normal mode
    }

    pFile->bValid = 0;
    pFile->lpStartAddress = NULL;
    pFile->dwPointer = 0;

    if (m_nOpenedFileNum > 0)
        m_nOpenedFileNum--;

    return 1;
}

bool CPK::Read(void* buffer, unsigned long size, CPKFile* pFile)
{
    if (!pFile || !pFile->bValid || !buffer)
        return 0;

    void* pData = pFile->GetRealData();
    if (!pData)
        return 0;

    // Clamp read size to available data
    unsigned long remaining = pFile->dwFileSize - pFile->dwPointer;
    if (size > remaining)
        size = remaining;

    memcpy(buffer, (unsigned char*)pData + pFile->dwPointer, size);
    pFile->dwPointer += size;

    return 1;
}

int CPK::ReadChar(CPKFile* pFile)
{
    if (!pFile || !pFile->bValid)
        return -1;

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
        int ch = ReadChar(pFile);
        if (ch == -1) {
            if (i == 0) return NULL;
            break;
        }
        if (ch == '\n') {
            break;
        }
        if (ch == '\r') {
            // Check for \r\n
            int next = ReadChar(pFile);
            if (next != '\n' && next != -1) {
                // Put back - adjust pointer
                pFile->dwPointer--;
            }
            break;
        }
        buffer[i++] = (char)ch;
    }
    buffer[i] = '\0';

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

    if (result != 0)  // LZO_E_OK == 0
        return 0;

    return dstLen;
}

unsigned long CPK::DeCompress(void* dst, void* src, unsigned long srcLen)
{
    unsigned long dstLen = 0;

    int result = lzo1x_decompress((const unsigned char*)src, srcLen,
                                  (unsigned char*)dst, &dstLen, NULL);

    if (result != 0)  // LZO_E_OK == 0
        return 0;

    return dstLen;
}

unsigned long CPK::GetSize(CPKFile* pFile)
{
    if (!pFile)
        return 0;
    return pFile->dwFileSize;
}

unsigned long CPK::GetCPKHandle()
{
    return m_dwCPKHandle;
}

unsigned long CPK::Tell(CPKFile* pFile)
{
    if (!pFile)
        return 0;
    return pFile->dwPointer;
}

void CPK::Rewind(CPKFile* pFile)
{
    if (pFile) {
        pFile->dwPointer = 0;
    }
}

unsigned long CPK::Seek(CPKFile* pFile, int offset, unsigned long origin)
{
    if (!pFile || !pFile->bValid)
        return (unsigned long)-1;

    long newPos;
    switch (origin) {
        case SEEK_SET:  // 0
            newPos = offset;
            break;
        case SEEK_CUR:  // 1
            newPos = (long)pFile->dwPointer + offset;
            break;
        case SEEK_END:  // 2
            newPos = (long)pFile->dwFileSize + offset;
            break;
        default:
            return (unsigned long)-1;
    }

    if (newPos < 0)
        newPos = 0;
    if ((unsigned long)newPos > pFile->dwFileSize)
        newPos = (long)pFile->dwFileSize;

    pFile->dwPointer = (unsigned long)newPos;
    return pFile->dwPointer;
}

int CPK::GetTableIndex(const char* filename)
{
    if (!filename)
        return -1;

    // Convert to lowercase for CRC matching
    char lowerName[260];
    strncpy(lowerName, filename, sizeof(lowerName) - 1);
    lowerName[sizeof(lowerName) - 1] = '\0';
    _strlwr(lowerName);

    // Convert backslashes to forward slashes (or vice versa) for consistency
    // The CPK format typically uses forward slashes internally

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
    return m_dwAllocGranularity;
}

bool CPK::IsDir(unsigned long tableIndex)
{
    if (tableIndex >= m_CPKHeader.dwValidTableNum)
        return 0;
    return (m_CPKTable[tableIndex].dwFlag & CPK_FLAG_ISDIR) ? 1 : 0;
}


// ============================================================================
// gbVFile Implementation
// ============================================================================

gbVFile::gbVFile()
{
    memset(this, 0, sizeof(gbVFile));
}

gbVFile::~gbVFile()
{
    // Trivial destructor
}

gbVFile& gbVFile::operator=(const gbVFile& other)
{
    if (this != &other) {
        memcpy(this, &other, sizeof(gbVFile));
    }
    return *this;
}


// ============================================================================
// gbVFile1 Implementation
// ============================================================================

gbVFile1& gbVFile1::operator=(const gbVFile1& other)
{
    if (this != &other) {
        memcpy(this, &other, sizeof(gbVFile1));
    }
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

    // Extract filename from full path (after last '\' or '/')
    const char* p = strrchr(fullPath, '\\');
    const char* p2 = strrchr(fullPath, '/');
    if (p2 > p) p = p2;

    if (p) {
        p++; // skip the separator
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

    // Extract directory part (everything before last '\' or '/')
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

    // Get filename first
    char filename[260];
    GetFileName(filename, sizeof(filename));

    // Remove extension
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


// ============================================================================
// gbVFileSystem Implementation
// ============================================================================

gbVFileSystem::gbVFileSystem()
{
    IsInit = 0;
    rtDirectory = NULL;
    pFileBuffer = NULL;
    Type = VFSYS_DISKFILE;
    m_pckfp = NULL;
    m_itemcount = 0;
    // CPK constructor is called automatically
}

gbVFileSystem::~gbVFileSystem()
{
    Release();
}

gbVFileSystem& gbVFileSystem::operator=(const gbVFileSystem& other)
{
    if (this != &other) {
        memcpy(this, &other, sizeof(gbVFileSystem));
    }
    return *this;
}

int gbVFileSystem::Init(char* path)
{
    if (!path)
        return 0;

    // Store the root directory
    int len = (int)strlen(path);
    rtDirectory = (char*)malloc(len + 1);
    if (!rtDirectory)
        return 0;
    strcpy(rtDirectory, path);

    // Try to load the CPK file
    // Look for a .cpk file at the given path
    char cpkPath[260];

    // Check if path itself is a .cpk file
    const char* ext = strrchr(path, '.');
    if (ext && (_stricmp(ext, ".cpk") == 0)) {
        // Path is a .cpk file directly
        strncpy(cpkPath, path, sizeof(cpkPath) - 1);
        cpkPath[sizeof(cpkPath) - 1] = '\0';

        if (m_cpk.IsValidCPK(cpkPath)) {
            m_cpk.SetOpenMode(CPKM_FileMapping);
            if (m_cpk.Load(cpkPath)) {
                Type = VFSYS_PACKFILE;
                IsInit = 1;
                return 1;
            }
        }
    }

    // Try appending ".cpk" to the path
    _snprintf(cpkPath, sizeof(cpkPath), "%s.cpk", path);
    if (m_cpk.IsValidCPK(cpkPath)) {
        m_cpk.SetOpenMode(CPKM_FileMapping);
        if (m_cpk.Load(cpkPath)) {
            Type = VFSYS_PACKFILE;
            IsInit = 1;
            return 1;
        }
    }

    // Fall back to disk file mode
    Type = VFSYS_DISKFILE;
    IsInit = 1;
    return 1;
}

void gbVFileSystem::Release()
{
    if (m_cpk.IsLoaded()) {
        m_cpk.Unload();
    }

    if (rtDirectory) {
        free(rtDirectory);
        rtDirectory = NULL;
    }

    if (pFileBuffer) {
        delete pFileBuffer;
        pFileBuffer = NULL;
    }

    IsInit = 0;
}

gbVFile* gbVFileSystem::NewFileEntry()
{
    gbVFile* pFile = new gbVFile();
    return pFile;
}

void gbVFileSystem::DelFileEntry(gbVFile* pFile)
{
    if (pFile) {
        delete pFile;
    }
}

gbVFile* gbVFileSystem::OpenFile(const char* filename, unsigned int flags)
{
    if (!filename || !IsInit)
        return NULL;

    gbVFile* pFile = NewFileEntry();
    if (!pFile)
        return NULL;

    if (Type == VFSYS_PACKFILE && m_cpk.IsLoaded()) {
        // Try opening from CPK archive first
        CPKFile* cpkFile = m_cpk.Open(filename);
        if (cpkFile) {
            pFile->bValid = 1;
            pFile->dwCRC = cpkFile->dwCRC;
            pFile->dwFatherCRC = cpkFile->dwFatherCRC;
            pFile->nTableIndex = cpkFile->nTableIndex;
            pFile->lpMapAddress = cpkFile->lpMapAddress;
            pFile->lpStartAddress = cpkFile->lpStartAddress;
            pFile->dwOffset = cpkFile->dwOffset;
            pFile->bCompressed = cpkFile->bCompressed;
            pFile->lpMem = cpkFile->lpMem;
            pFile->dwFileSize = cpkFile->dwFileSize;
            pFile->dwPointer = 0;
            pFile->pTableItem = cpkFile->pTableItem;
            pFile->hFile = INVALID_HANDLE_VALUE;
            pFile->openMode = 0;  // CPK mode
            return pFile;
        }
    }

    // Fall back to disk file
    char fullPath[260];
    if (rtDirectory) {
        _snprintf(fullPath, sizeof(fullPath), "%s\\%s", rtDirectory, filename);
    } else {
        strncpy(fullPath, filename, sizeof(fullPath) - 1);
        fullPath[sizeof(fullPath) - 1] = '\0';
    }

    DWORD access = GENERIC_READ;
    DWORD creation = OPEN_EXISTING;
    if (flags & 1) {  // Write mode
        access = GENERIC_READ | GENERIC_WRITE;
        creation = OPEN_ALWAYS;
    }

    HANDLE hFile = CreateFileA(fullPath, access, FILE_SHARE_READ,
                               NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        DelFileEntry(pFile);
        return NULL;
    }

    pFile->bValid = 1;
    pFile->hFile = hFile;
    pFile->openMode = 1;  // Disk mode
    pFile->dwPointer = 0;

    // Get file size
    DWORD fileSize = ::GetFileSize(hFile, NULL);
    if (fileSize != INVALID_FILE_SIZE) {
        pFile->dwFileSize = fileSize;
    }

    return pFile;
}

void gbVFileSystem::CloseFile(gbVFile* pFile)
{
    if (!pFile)
        return;

    if (pFile->openMode == 1) {
        // Disk file
        if (pFile->hFile && pFile->hFile != INVALID_HANDLE_VALUE) {
            CloseHandle(pFile->hFile);
            pFile->hFile = INVALID_HANDLE_VALUE;
        }
    } else {
        // CPK file - close via CPK
        // The CPKFile handle was used to populate gbVFile, so we need to
        // clean up mapped/allocated memory
        if (pFile->lpMapAddress) {
            UnmapViewOfFile(pFile->lpMapAddress);
            pFile->lpMapAddress = NULL;
        }
        if (pFile->lpMem) {
            free(pFile->lpMem);
            pFile->lpMem = NULL;
        }
    }

    pFile->bValid = 0;
    DelFileEntry(pFile);
}

void gbVFileSystem::Read(void* buffer, unsigned int size, gbVFile* pFile)
{
    if (!pFile || !pFile->bValid || !buffer)
        return;

    if (pFile->openMode == 1) {
        // Disk file
        DWORD bytesRead = 0;
        ReadFile(pFile->hFile, buffer, size, &bytesRead, NULL);
        pFile->dwPointer += bytesRead;
    } else {
        // CPK file - read from memory
        void* pData = pFile->lpMem ? pFile->lpMem : pFile->lpStartAddress;
        if (!pData)
            return;

        unsigned long remaining = pFile->dwFileSize - pFile->dwPointer;
        if (size > remaining)
            size = (unsigned int)remaining;

        memcpy(buffer, (unsigned char*)pData + pFile->dwPointer, size);
        pFile->dwPointer += size;
    }
}

void gbVFileSystem::Write(void* buffer, unsigned int size, gbVFile* pFile)
{
    if (!pFile || !pFile->bValid || !buffer)
        return;

    if (pFile->openMode == 1) {
        // Disk file
        DWORD bytesWritten = 0;
        WriteFile(pFile->hFile, buffer, size, &bytesWritten, NULL);
        pFile->dwPointer += bytesWritten;
    }
}

int gbVFileSystem::ReadChar(gbVFile* pFile)
{
    if (!pFile || !pFile->bValid)
        return -1;

    unsigned char ch = 0;
    unsigned int prevPos = pFile->dwPointer;
    Read(&ch, 1, pFile);
    if (pFile->dwPointer > prevPos)
        return (int)ch;

    return -1;
}

char* gbVFileSystem::ReadLine(char* buffer, int maxLen, gbVFile* pFile)
{
    if (!pFile || !pFile->bValid || !buffer || maxLen <= 0)
        return NULL;

    int i = 0;
    while (i < maxLen - 1) {
        int ch = ReadChar(pFile);
        if (ch == -1) {
            if (i == 0) return NULL;
            break;
        }
        if (ch == '\n') {
            break;
        }
        if (ch == '\r') {
            // Check for \r\n
            int next = ReadChar(pFile);
            if (next != '\n' && next != -1) {
                // Put back - seek back by 1
                Seek(pFile, -1, SEEK_CUR);
            }
            break;
        }
        buffer[i++] = (char)ch;
    }
    buffer[i] = '\0';

    return buffer;
}

void gbVFileSystem::Seek(gbVFile* pFile, long offset, int origin)
{
    if (!pFile || !pFile->bValid)
        return;

    if (pFile->openMode == 1) {
        // Disk file
        DWORD moveMethod;
        switch (origin) {
            case SEEK_SET: moveMethod = FILE_BEGIN; break;
            case SEEK_CUR: moveMethod = FILE_CURRENT; break;
            case SEEK_END: moveMethod = FILE_END; break;
            default: return;
        }
        DWORD newPos = SetFilePointer(pFile->hFile, offset, NULL, moveMethod);
        if (newPos != INVALID_SET_FILE_POINTER) {
            pFile->dwPointer = newPos;
        }
    } else {
        // CPK file - adjust pointer in memory
        long newPos;
        switch (origin) {
            case SEEK_SET:
                newPos = offset;
                break;
            case SEEK_CUR:
                newPos = (long)pFile->dwPointer + offset;
                break;
            case SEEK_END:
                newPos = (long)pFile->dwFileSize + offset;
                break;
            default:
                return;
        }

        if (newPos < 0)
            newPos = 0;
        if ((unsigned long)newPos > pFile->dwFileSize)
            newPos = (long)pFile->dwFileSize;

        pFile->dwPointer = (unsigned long)newPos;
    }
}

void gbVFileSystem::Rewind(gbVFile* pFile)
{
    if (!pFile || !pFile->bValid)
        return;

    if (pFile->openMode == 1) {
        SetFilePointer(pFile->hFile, 0, NULL, FILE_BEGIN);
    }
    pFile->dwPointer = 0;
}

long gbVFileSystem::TellPos(gbVFile* pFile)
{
    if (!pFile || !pFile->bValid)
        return -1;

    if (pFile->openMode == 1) {
        return (long)SetFilePointer(pFile->hFile, 0, NULL, FILE_CURRENT);
    }

    return (long)pFile->dwPointer;
}

long gbVFileSystem::GetFileSize(gbVFile* pFile)
{
    if (!pFile || !pFile->bValid)
        return -1;

    if (pFile->openMode == 1) {
        // Disk file
        DWORD size = ::GetFileSize(pFile->hFile, NULL);
        if (size == INVALID_FILE_SIZE)
            return -1;
        return (long)size;
    }

    // CPK file
    return (long)pFile->dwFileSize;
}

int gbVFileSystem::FileExistNum(char* filename)
{
    if (!filename || !IsInit)
        return 0;

    if (Type == VFSYS_PACKFILE && m_cpk.IsLoaded()) {
        // Check in CPK
        if (m_cpk.IsFileExist(filename))
            return 1;
    }

    // Check on disk
    char fullPath[260];
    if (rtDirectory) {
        _snprintf(fullPath, sizeof(fullPath), "%s\\%s", rtDirectory, filename);
    } else {
        strncpy(fullPath, filename, sizeof(fullPath) - 1);
        fullPath[sizeof(fullPath) - 1] = '\0';
    }

    DWORD attribs = GetFileAttributesA(fullPath);
    if (attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY)) {
        return 1;
    }

    return 0;
}

int gbVFileSystem::FindItem(const char* filename)
{
    if (!filename || !IsInit)
        return -1;

    if (Type == VFSYS_PACKFILE && m_cpk.IsLoaded()) {
        int index = m_cpk.GetTableIndex(filename);
        if (index >= 0)
            return index;
    }

    return -1;
}


// ============================================================================
// CIniFile Implementation
// ============================================================================

CIniFile::CIniFile()
{
    m_pFile = NULL;
    m_nState = -1;  // 0xFFFFFFFF
}

CIniFile::~CIniFile()
{
    CloseFile();
}

CIniFile& CIniFile::operator=(const CIniFile& other)
{
    if (this != &other) {
        m_pFile = other.m_pFile;
        m_nState = other.m_nState;
    }
    return *this;
}

int CIniFile::OpenFileRead(const char* filename)
{
    if (!g_pVFileSys || !filename)
        return 0;

    m_pFile = g_pVFileSys->OpenFile(filename, 0);  // Read mode
    if (m_pFile) {
        m_nState = 0;  // Opened for reading
        return 1;
    }
    return 0;
}

int CIniFile::OpenFileWrite(const char* filename)
{
    if (!g_pVFileSys || !filename)
        return 0;

    m_pFile = g_pVFileSys->OpenFile(filename, 1);  // Write mode
    if (m_pFile) {
        m_nState = 1;  // Opened for writing
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
        // Skip whitespace
        char* p = line;
        while (*p == ' ' || *p == '\t') p++;

        // Check for section header [SectionName]
        if (*p == '[') {
            p++;
            char* end = strchr(p, ']');
            if (end) {
                *end = '\0';
                if (_stricmp(p, sectionName) == 0) {
                    return 1;  // Found the section
                }
            }
        }
    }

    return 0;  // Section not found
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

    // Skip whitespace
    char* p = line;
    while (*p == ' ' || *p == '\t') p++;

    // Check if this line starts with the key
    int keyLen = (int)strlen(key);
    if (_strnicmp(p, key, keyLen) != 0)
        return 0;

    p += keyLen;

    // Skip whitespace and '='
    while (*p == ' ' || *p == '\t') p++;
    if (*p == '=') p++;
    while (*p == ' ' || *p == '\t') p++;

    // Copy value
    strncpy(value, p, maxLen - 1);
    value[maxLen - 1] = '\0';

    // Trim trailing whitespace/newline
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
    if (!m_pFile || !g_pVFileSys || !section)
        return;

    char line[512];
    _snprintf(line, sizeof(line), "[%s]\r\n", section);
    g_pVFileSys->Write(line, (unsigned int)strlen(line), m_pFile);
}

void CIniFile::WriteLine(const char* key, const char* value)
{
    if (!m_pFile || !g_pVFileSys || !key || !value)
        return;

    char line[512];
    _snprintf(line, sizeof(line), "%s=%s\r\n", key, value);
    g_pVFileSys->Write(line, (unsigned int)strlen(line), m_pFile);
}

void CIniFile::WriteLine(const char* key, int value)
{
    if (!m_pFile || !g_pVFileSys || !key)
        return;

    char line[512];
    _snprintf(line, sizeof(line), "%s=%d\r\n", key, value);
    g_pVFileSys->Write(line, (unsigned int)strlen(line), m_pFile);
}

void CIniFile::WriteLine(const char* key, float value)
{
    if (!m_pFile || !g_pVFileSys || !key)
        return;

    char line[512];
    _snprintf(line, sizeof(line), "%s=%f\r\n", key, value);
    g_pVFileSys->Write(line, (unsigned int)strlen(line), m_pFile);
}

void CIniFile::WriteLine(const char* key, double value)
{
    if (!m_pFile || !g_pVFileSys || !key)
        return;

    char line[512];
    _snprintf(line, sizeof(line), "%s=%f\r\n", key, value);
    g_pVFileSys->Write(line, (unsigned int)strlen(line), m_pFile);
}

void CIniFile::WriteLineSeperator()
{
    if (!m_pFile || !g_pVFileSys)
        return;

    const char* sep = "\r\n";
    g_pVFileSys->Write((void*)sep, 2, m_pFile);
}

int CIniFile::IfRead()
{
    return (m_nState == 0) ? 1 : 0;
}

gbVFile* CIniFile::GetFilePointer()
{
    return m_pFile;
}


// ============================================================
// Additional export implementations
// ============================================================

#pragma optimize("", off)
#pragma auto_inline(off)

// Class definitions needed for moved functions
class gbVTextFile {
public:
    char lineBuf[0x400];    // +0x000: line buffer (1024 bytes)
    gbVFile* m_pFile;       // +0x400: file handle

public:
    gbVTextFile(char * p0);

public:
    gbVTextFile();

public:
    ~gbVTextFile();

public:
    class gbVTextFile & operator=(class gbVTextFile const & p0);

public:
    void Close();

public:
    void Open(char * p0);

public:
    char * ReadLine();

public:
    void Rewind();

};

// ---- gbVTextFile ----
gbVTextFile::gbVTextFile(char * p0) {
    m_pFile = g_pVFileSys->OpenFile(p0, 0x401);
}

gbVTextFile::gbVTextFile() {
    m_pFile = 0;
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
    if (!m_pFile || !g_pVFileSys) {
        return NULL;
    }

    // Read a line from the file
    char* result = g_pVFileSys->ReadLine(lineBuf, sizeof(lineBuf) - 1, m_pFile);
    if (!result) {
        return NULL;
    }

    // Trim trailing newline/carriage return
    int len = (int)strlen(lineBuf);
    while (len > 0 && (lineBuf[len - 1] == '\n' || lineBuf[len - 1] == '\r')) {
        lineBuf[--len] = '\0';
    }

    return lineBuf;
}


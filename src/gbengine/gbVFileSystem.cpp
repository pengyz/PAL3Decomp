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

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// ============================================================================
// CPK Constants and Flags
// ============================================================================

#define CPK_LABEL           0x1A545352  // "RST\x1A"
#define CPK_MAX_TABLE_NUM   0x8000
#define CPK_MAX_OPEN_FILES  8

#define CPK_FLAG_ISFILE         0x00000001
#define CPK_FLAG_ISDIR          0x00000002
#define CPK_FLAG_UNKNOWN1       0x00000004
#define CPK_FLAG_UNKNOWN2       0x00000008
#define CPK_FLAG_ISDELETED      0x00000010
#define CPK_FLAG_NOTCOMPRESSED  0x00010000

// ============================================================================
// ECPKMode enum
// ============================================================================

enum ECPKMode {
    CPKM_Null = 0,
    CPKM_Normal = 1,
    CPKM_FileMapping = 2,
    CPKM_Overlapped = 3,
    CPKM_End = 4
};

// ============================================================================
// CPKHeader (0x80 = 128 bytes, with reserved padding)
// ============================================================================

struct CPKHeader {
    unsigned long dwLable;          // 0x00: magic 0x1A545352
    unsigned long dwVersion;        // 0x04
    unsigned long dwTableStart;     // 0x08
    unsigned long dwDataStart;      // 0x0C
    unsigned long dwMaxFileNum;     // 0x10
    unsigned long dwFileNum;        // 0x14
    unsigned long dwIsFormatted;    // 0x18
    unsigned long dwSizeOfHeader;   // 0x1C
    unsigned long dwValidTableNum;  // 0x20
    unsigned long dwMaxTableNum;    // 0x24
    unsigned long dwFragmentNum;    // 0x28
    unsigned long dwPackageSize;    // 0x2C
    unsigned long dwReserved[0x14]; // 0x30: 80 bytes reserved
};

// ============================================================================
// CPKTable (0x1C = 28 bytes per entry)
// ============================================================================

struct CPKTable {
    unsigned long dwCRC;            // 0x00: filename CRC32
    unsigned long dwFlag;           // 0x04: flags
    unsigned long dwFatherCRC;      // 0x08: parent directory CRC32
    unsigned long dwStartPos;       // 0x0C: data offset in archive
    unsigned long dwPackedSize;     // 0x10: compressed size
    unsigned long dwOriginSize;     // 0x14: original size
    unsigned long dwExtraInfoSize;  // 0x18: extra info size (filename length)
};

// ============================================================================
// CPKFile class - Handle for an opened file within a CPK archive
// ============================================================================

class CPKFile {
public:
    unsigned char bValid;           // +0x00: is this handle in use
    unsigned long dwCRC;            // +0x04: file CRC
    unsigned long dwFatherCRC;      // +0x08: parent CRC
    int           nTableIndex;      // +0x0C: index into CPK file table
    void*         lpMapAddress;     // +0x10: memory-mapped base address
    void*         lpStartAddress;   // +0x14: start of file data in mapping
    unsigned long dwOffset;         // +0x18: offset for mapping alignment
    unsigned char bCompressed;      // +0x1C: is the data compressed
    void*         lpMem;            // +0x20: decompressed data buffer
    unsigned long dwFileSize;       // +0x24: original file size
    unsigned long dwPointer;        // +0x28: current read position
    CPKTable*     pTableItem;       // +0x2C: pointer to table entry

    // Padding to reach ~0x140 bytes (original size from Ghidra)
    unsigned char _reserved[0x140 - 0x30];

    CPKFile();
    ~CPKFile();
    CPKFile& operator=(const CPKFile& other);
    void* GetRealData();
};

// ============================================================================
// CPK class - CPK archive reader
// sizeof(CPK) == 0xE01BC
// ============================================================================

class CPK {
public:
    unsigned long   m_dwAllocGranularity;           // +0x00
    ECPKMode        m_eMode;                        // +0x04
    CPKHeader       m_CPKHeader;                    // +0x08 (0x80 bytes)
    CPKTable        m_CPKTable[CPK_MAX_TABLE_NUM];  // +0x88 (0x8000 * 0x1C = 0xE0000 bytes)
    CPKFile*        m_pCPKFile[CPK_MAX_OPEN_FILES]; // +0xE0088 (8 pointers)
    unsigned char   m_bLoaded;                      // +0xE00A8
    unsigned long   m_dwCPKHandle;                  // +0xE00AC (HANDLE as DWORD)
    unsigned long   m_dwCPKMappingHandle;           // +0xE00B0
    char            m_szCPKFileName[0x104];          // +0xE00B4
    int             m_nOpenedFileNum;               // +0xE01B8

    // Static CRC table
    static unsigned long CrcTable[256];
    static int s_bCrcTableInitialized;

    CPK();
    ~CPK();
    CPK& operator=(const CPK& other);

    // Public methods
    static void InitCrcTable();
    static unsigned long Crc(const char* str);
    int  Load(const char* filename);
    int  Unload();
    int  IsValidCPK(const char* filename);
    int  IsFileExist(const char* filename);
    int  IsLoaded();
    CPKFile* Open(const char* filename);
    int  Close(CPKFile* pFile);
    int  Read(void* buffer, unsigned long size, CPKFile* pFile);
    int  ReadChar(CPKFile* pFile);
    char* ReadLine(char* buffer, int maxLen, CPKFile* pFile);
    unsigned long LoadFile(void* buffer, const char* filename);
    unsigned long Compress(void* dst, void* src, unsigned long srcLen);
    unsigned long DeCompress(void* dst, void* src, unsigned long srcLen);
    unsigned long GetSize(CPKFile* pFile);
    unsigned long GetCPKHandle();
    unsigned long Seek(CPKFile* pFile, int offset, int origin);
    unsigned long Tell(CPKFile* pFile);
    void Rewind(CPKFile* pFile);
    void SetOpenMode(ECPKMode mode);

    // These are private in the original binary but we keep them accessible
    // for use by gbVFileSystem methods in the same translation unit.
    void Reset();
    int  GetFileSize(unsigned long& packedSize, unsigned long& originSize, unsigned long tableIndex);
    int  GetTableIndex(const char* filename);
    int  GetTableIndexFromCRC(unsigned long crc);
    unsigned long GetAllocationGranularity();
    int  IsDir(unsigned long tableIndex);
};

// Static member definitions
unsigned long CPK::CrcTable[256];
int CPK::s_bCrcTableInitialized = 0;

// ============================================================================
// gbVFile class - Virtual file handle
// ============================================================================

class gbVFile {
public:
    unsigned char   bValid;         // +0x00: handle is active
    unsigned long   dwCRC;          // +0x04
    unsigned long   dwFatherCRC;    // +0x08
    int             nTableIndex;    // +0x0C
    void*           lpMapAddress;   // +0x10
    void*           lpStartAddress; // +0x14
    unsigned long   dwOffset;       // +0x18
    unsigned char   bCompressed;    // +0x1C
    void*           lpMem;          // +0x20
    unsigned long   dwFileSize;     // +0x24
    unsigned long   dwPointer;      // +0x28
    CPKTable*       pTableItem;     // +0x2C

    // Disk file handle (for non-CPK mode)
    HANDLE          hFile;          // +0x30
    int             openMode;       // +0x34: 0=CPK, 1=disk

    gbVFile();
    ~gbVFile();
    gbVFile& operator=(const gbVFile& other);
};

// ============================================================================
// gbVFile1 class - Extended file info with path manipulation
// ============================================================================

class gbVFile1 {
public:
    char fullPath[260];     // +0x00: MAX_PATH

    gbVFile1& operator=(const gbVFile1& other);
    char* GetFullPath();
    char* GetFileName(char* buf, int bufLen);
    char* GetDir(char* buf, int bufLen);
    char* GetTitle(char* buf, int bufLen);
    char* GetEntry();
};

// ============================================================================
// gbVFileSystem class - Virtual file system
// sizeof(gbVFileSystem) == 0xE01D4
// ============================================================================

enum gbVFSType {
    VFSYS_DISKFILE = 0,
    VFSYS_PACKFILE = 1,
    VFSYS_MEMIMAGE = 2
};

class gbVFileSystem {
public:
    int             IsInit;         // +0x00
    char*           rtDirectory;    // +0x04
    gbVFile*        pFileBuffer;    // +0x08
    gbVFSType       Type;           // +0x0C
    FILE*           m_pckfp;        // +0x10
    unsigned int    m_itemcount;    // +0x14
    CPK             m_cpk;          // +0x18

    gbVFileSystem();
    ~gbVFileSystem();
    gbVFileSystem& operator=(const gbVFileSystem& other);

    int     Init(char* path);
    void    Release();
    gbVFile* OpenFile(const char* filename, unsigned int flags);
    void    CloseFile(gbVFile* pFile);
    gbVFile* NewFileEntry();
    void    DelFileEntry(gbVFile* pFile);
    int     Read(void* buffer, unsigned int size, gbVFile* pFile);
    int     Write(void* buffer, unsigned int size, gbVFile* pFile);
    int     ReadChar(gbVFile* pFile);
    char*   ReadLine(char* buffer, int maxLen, gbVFile* pFile);
    void    Seek(gbVFile* pFile, long offset, int origin);
    void    Rewind(gbVFile* pFile);
    long    TellPos(gbVFile* pFile);
    long    GetFileSize(gbVFile* pFile);
    int     FileExistNum(char* filename);
    int     FindItem(const char* filename);
};

// Global pointer to the virtual file system
gbVFileSystem* g_pVFileSys = NULL;

// ============================================================================
// CIniFile class - INI file reader/writer using gbVFileSystem
// ============================================================================

class CIniFile {
public:
    gbVFile*    m_pFile;        // +0x00: file handle
    int         m_nState;       // +0x04: state (-1 = not opened)

    CIniFile();
    ~CIniFile();
    CIniFile& operator=(const CIniFile& other);

    int  OpenFileRead(const char* filename);
    int  OpenFileWrite(const char* filename);
    void CloseFile();
    int  ReadSection(char* sectionName);
    void ReadStart();
    int  ReadLine(const char* key, char* value, int maxLen);
    int  ReadLine(const char* key, int* value);
    int  ReadLine(const char* key, float* value);
    int  ReadLine(const char* key, double* value);
    void WriteLine(const char* key, const char* value);
    void WriteLine(const char* key, int value);
    void WriteLine(const char* key, float value);
    void WriteLine(const char* key, double value);
    void WriteLineSeperator();
    void WriteSection(const char* section);
    int  IfRead();
    gbVFile* GetFilePointer();
};


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

int CPK::Load(const char* filename)
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

int CPK::Unload()
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

void CPK::Reset()
{
    memset(&m_CPKHeader, 0, sizeof(CPKHeader));
    memset(m_CPKTable, 0, sizeof(m_CPKTable));
    m_nOpenedFileNum = 0;
    m_szCPKFileName[0] = '\0';
}

void CPK::SetOpenMode(ECPKMode mode)
{
    m_eMode = mode;
}

int CPK::IsValidCPK(const char* filename)
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

int CPK::IsFileExist(const char* filename)
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

int CPK::IsLoaded()
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

int CPK::Close(CPKFile* pFile)
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

int CPK::Read(void* buffer, unsigned long size, CPKFile* pFile)
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

unsigned long CPK::Seek(CPKFile* pFile, int offset, int origin)
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

int CPK::GetFileSize(unsigned long& packedSize, unsigned long& originSize, unsigned long tableIndex)
{
    if (tableIndex >= m_CPKHeader.dwValidTableNum)
        return 0;

    packedSize = m_CPKTable[tableIndex].dwPackedSize;
    originSize = m_CPKTable[tableIndex].dwOriginSize;
    return 1;
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

int CPK::IsDir(unsigned long tableIndex)
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

char* gbVFile1::GetEntry()
{
    // Return the file extension (including the dot)
    char* dot = strrchr(fullPath, '.');
    if (dot)
        return dot;
    return NULL;
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

int gbVFileSystem::Read(void* buffer, unsigned int size, gbVFile* pFile)
{
    if (!pFile || !pFile->bValid || !buffer)
        return 0;

    if (pFile->openMode == 1) {
        // Disk file
        DWORD bytesRead = 0;
        ReadFile(pFile->hFile, buffer, size, &bytesRead, NULL);
        pFile->dwPointer += bytesRead;
        return (int)bytesRead;
    } else {
        // CPK file - read from memory
        void* pData = pFile->lpMem ? pFile->lpMem : pFile->lpStartAddress;
        if (!pData)
            return 0;

        unsigned long remaining = pFile->dwFileSize - pFile->dwPointer;
        if (size > remaining)
            size = (unsigned int)remaining;

        memcpy(buffer, (unsigned char*)pData + pFile->dwPointer, size);
        pFile->dwPointer += size;
        return (int)size;
    }
}

int gbVFileSystem::Write(void* buffer, unsigned int size, gbVFile* pFile)
{
    if (!pFile || !pFile->bValid || !buffer)
        return 0;

    if (pFile->openMode == 1) {
        // Disk file
        DWORD bytesWritten = 0;
        WriteFile(pFile->hFile, buffer, size, &bytesWritten, NULL);
        pFile->dwPointer += bytesWritten;
        return (int)bytesWritten;
    }

    // Cannot write to CPK files
    return 0;
}

int gbVFileSystem::ReadChar(gbVFile* pFile)
{
    if (!pFile || !pFile->bValid)
        return -1;

    unsigned char ch;
    int bytesRead = Read(&ch, 1, pFile);
    if (bytesRead > 0)
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

#pragma once

#include <windows.h>
#include <stdio.h>

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
    friend class gbVFileSystem;
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

    // Static (non-CRC)
    static int s_bCrcTableInitialized;

    CPK();
    ~CPK();
    CPK& operator=(const CPK& other);

    // Public methods
    bool Load(const char* filename);
    bool Unload();
    bool IsValidCPK(const char* filename);
    bool IsFileExist(const char* filename);
    bool IsLoaded();
    CPKFile* Open(const char* filename);
    bool Close(CPKFile* pFile);
    bool Read(void* buffer, unsigned long size, CPKFile* pFile);
    int  ReadChar(CPKFile* pFile);
    char* ReadLine(char* buffer, int maxLen, CPKFile* pFile);
    unsigned long LoadFile(void* buffer, const char* filename);
    unsigned long Compress(void* dst, void* src, unsigned long srcLen);
    unsigned long DeCompress(void* dst, void* src, unsigned long srcLen);
    unsigned long GetSize(CPKFile* pFile);
    unsigned long GetCPKHandle();
    unsigned long Seek(CPKFile* pFile, int offset, unsigned long origin);
    unsigned long Tell(CPKFile* pFile);
    void Rewind(CPKFile* pFile);
    void SetOpenMode(ECPKMode mode);

private:
    static unsigned long CrcTable[256];
    static void InitCrcTable();
    static unsigned long Crc(const char* str);
    void Reset();
    bool GetFileSize(unsigned long& packedSize, unsigned long& originSize, unsigned long tableIndex);
    int  GetTableIndex(const char* filename);
    int  GetTableIndexFromCRC(unsigned long crc);
    unsigned long GetAllocationGranularity();
    bool IsDir(unsigned long tableIndex);
};

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
    unsigned int GetEntry();
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
    void    Read(void* buffer, unsigned int size, gbVFile* pFile);
    void    Write(void* buffer, unsigned int size, gbVFile* pFile);
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
extern gbVFileSystem* g_pVFileSys;

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

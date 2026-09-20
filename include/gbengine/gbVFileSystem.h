#pragma once

#include <windows.h>
#include <stdio.h>
#include "gbengine/gbengine_export.h"

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
// sizeof(CPKFile) == 0x30 (48 bytes, embedded at gbVFile+272)
// ============================================================================

class CPKFile {
public:
    unsigned char bValid;           // +0x00: is this handle in use
    unsigned char _pad1[3];         // +0x01: padding
    unsigned long dwCRC;            // +0x04: file CRC
    unsigned long dwFatherCRC;      // +0x08: parent CRC
    int           nTableIndex;      // +0x0C: index into CPK file table
    void*         lpMapAddress;     // +0x10: memory-mapped base address
    void*         lpStartAddress;   // +0x14: start of file data in mapping
    unsigned long dwOffset;         // +0x18: offset for mapping alignment
    unsigned char bCompressed;      // +0x1C: is the data compressed
    unsigned char _pad2[3];         // +0x1D: padding
    void*         lpRealData;       // +0x20: pointer to readable data (decompressed or mapped)
    unsigned long dwFileSize;       // +0x24: original file size
    unsigned long dwPointer;        // +0x28: current read position
    CPKTable*     pTableItem;       // +0x2C: pointer to table entry

    CPKFile();
    ~CPKFile();
    CPKFile& operator=(const CPKFile& other);
    void* GetRealData();
};

// Forward declaration (defined below)
class gbVFile;

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
    gbVFile*        m_pCPKFile[CPK_MAX_OPEN_FILES]; // +0xE0088: gbVFile[8] (each 0x140 bytes)
    bool            m_bLoaded;                      // +0xE00A8
    unsigned char   _pad[3];                        // +0xE00A9
    unsigned long   m_dwCPKHandle;                  // +0xE00AC (HANDLE as DWORD)
    unsigned long   m_dwCPKMappingHandle;           // +0xE00B0
    char            m_szCPKFileName[0x104];          // +0xE00B4
    int             m_nOpenedFileNum;               // +0xE01B8

    // Static
    static int s_bCrcTableInitialized;

    // F70（第 124 轮）：GBAPI 按成员给，**只给 IAT 里真实存在的方法**（A 级清单：GBENGINE 模块
    // 的 9 个 CPK 符号 —— ctor/dtor/Load/IsValidCPK/Open/Close/DeCompress/Seek/SetOpenMode）。
    // 类级 GBAPI 对"引擎导出 + 游戏侧又实现"的类是错的：`Init`/`InitPackFiles` 由 PAL3.exe 实现
    // （0x0053DB90 / 0x0053C250，在 PAL3 的 .text 里）⇒ 类级 dllimport 让它们的定义变成
    // "全局函数里的 this"（实测 C2673 ×16）。
    GBAPI CPK();
    GBAPI ~CPK();
    CPK& operator=(const CPK& other);

    // Public methods
    GBAPI bool Load(const char* filename);
    bool Unload();
    GBAPI bool IsValidCPK(const char* filename);
    bool IsFileExist(const char* filename);
    bool IsLoaded();
    GBAPI CPKFile* Open(const char* filename);
    GBAPI bool Close(CPKFile* pFile);
    bool Read(void* buffer, unsigned long size, CPKFile* pFile);
    int  ReadChar(CPKFile* pFile);
    char* ReadLine(char* buffer, int maxLen, CPKFile* pFile);
    unsigned long LoadFile(void* buffer, const char* filename);
    unsigned long Compress(void* dst, void* src, unsigned long srcLen);
    GBAPI unsigned long DeCompress(void* dst, void* src, unsigned long srcLen);
    unsigned long GetSize(CPKFile* pFile);
    unsigned long GetCPKHandle();
    GBAPI unsigned long Seek(CPKFile* pFile, int offset, unsigned long origin);
    unsigned long Tell(CPKFile* pFile);
    void Rewind(CPKFile* pFile);
    GBAPI void SetOpenMode(ECPKMode mode);

    // PAL3.exe 侧实现（注解/IDA 类型，A 级）—— 不带 GBAPI：
    //   CPK *__thiscall CPK::Init()          @0x0053DB90
    //   CPK *__thiscall CPK::InitPackFiles() @0x0053C250
    CPK* Init();
    CPK* InitPackFiles();

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
// sizeof(gbVFile) == 0x140 (320 bytes)
//
// Layout:
//   +0x000: DWORD flags      (0=unused, nonzero=open mode flags)
//   +0x004: FILE* fp          (disk mode) / void* memBuf (memimage mode)
//   +0x008: DWORD bufSize     (memimage: buffer capacity)
//   +0x00C: char fullPath[256] (filename)
//   +0x10C: void* memPtr      (memimage: current read/write pointer)
//   +0x110: CPKFile cpkFile   (CPK mode: embedded CPKFile, 48 bytes)
//   +0x140: end
// ============================================================================

class gbVFile {
public:
    unsigned long   flags;          // +0x00: 0=free, nonzero=in-use (stores open flags)
    void*           fp;             // +0x04: FILE* (disk) or buffer ptr (memimage)
    unsigned long   bufSize;        // +0x08: buffer size (memimage)
    char            fullPath[256];  // +0x0C: file path
    void*           memPtr;         // +0x10C: memimage current read/write ptr
    CPKFile         cpkFile;        // +0x110: embedded CPKFile (0x30 bytes)

    gbVFile();
    ~gbVFile();
    gbVFile& operator=(const gbVFile& other);
};

// ============================================================================
// gbVFile1 class - Extended file info with path manipulation
// ============================================================================

class gbVFile1 {
public:
    int field_00;           // +0x00
    int field_04;           // +0x04
    int field_08;           // +0x08
    char fullPath[260];     // +0x0C: MAX_PATH

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
//
// Layout:
//   +0x00: int IsInit
//   +0x04: char* rtDirectory
//   +0x08: gbVFile* pFileBuffer  (array of 16 gbVFile, allocated via eh vector ctor)
//   +0x0C: gbVFSType Type
//   +0x10: FILE* m_pckfp
//   +0x14: int m_itemcount
//   +0x18: CPK m_cpk (0xE01BC bytes)
// ============================================================================

enum gbVFSType {
    VFSYS_DISKFILE = 0,
    VFSYS_PACKFILE = 1,
    VFSYS_MEMIMAGE = 2
};

// Seek origins used by gbVFileSystem (NOT standard SEEK_SET/CUR/END!)
#define GBVFS_SEEK_SET  1
#define GBVFS_SEEK_CUR  2
#define GBVFS_SEEK_END  3

class GBAPI gbVFileSystem {
public:
    int             IsInit;         // +0x00
    char*           rtDirectory;    // +0x04
    gbVFile*        pFileBuffer;    // +0x08: array of 16 gbVFile entries
    gbVFSType       Type;           // +0x0C
    FILE*           m_pckfp;        // +0x10
    int             m_itemcount;    // +0x14
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

// Global pointer to the virtual file system.
// PAL3.exe does NOT define it: it imports the variable from gbengine.dll
// (IDA: PAL3.exe .idata entry for GBENGINE, IAT slot 0x0056A598). Without
// __declspec(dllimport) MSVC6 emits a direct absolute store/load
// (C7 05 <addr>) instead of the original IAT-indirect form
// (8B 0D <addr> / 89 01), so every site that touches it differs by bytes.
extern GBAPI gbVFileSystem* g_pVFileSys;

// ============================================================================
// CIniFile class - INI file reader/writer using gbVFileSystem
// ============================================================================

// F70（第 123 轮）：GBAPI（dllimport）**按成员给**，只给真正来自 gbengine.dll 的方法
// （IAT 实测清单：%TEMP%\dd105\imports.json 的 GBENGINE 模块，A 级）。类级 GBAPI 对
// "引擎导出 + 游戏侧又实现"的类是错的：`LoadData`/`LoadStructuredConfig` 由 **PAL3.exe 自己实现**
// （0x004EC700 / 0x00504130 在 PAL3 的 .text 里），类级 dllimport 会让它们的定义触发 C2491 /
// 退化成"全局函数里的 this"（实测 C2673 ×4 + C2039 连锁）。
class CIniFile {
public:
    gbVFile*    m_pFile;        // +0x00: file handle
    int         m_nState;       // +0x04: state (-1 = not opened)

    GBAPI CIniFile();
    GBAPI ~CIniFile();
    CIniFile& operator=(const CIniFile& other);

    GBAPI int  OpenFileRead(const char* filename);
    GBAPI int  OpenFileWrite(const char* filename);
    void CloseFile();
    GBAPI int  ReadSection(char* sectionName);
    GBAPI void ReadStart();
    GBAPI int  ReadLine(const char* key, char* value, int maxLen);
    GBAPI int  ReadLine(const char* key, int* value);
    GBAPI int  ReadLine(const char* key, float* value);
    GBAPI int  ReadLine(const char* key, double* value);
    GBAPI void WriteLine(const char* key, const char* value);
    void WriteLine(const char* key, int value);
    void WriteLine(const char* key, float value);
    void WriteLine(const char* key, double value);
    void WriteLineSeperator();
    GBAPI void WriteSection(const char* section);
    int  IfRead();
    gbVFile* GetFilePointer();

    // PAL3.exe 侧实现（注解/IDA 类型，A 级）—— 不带 GBAPI：
    //   char __thiscall CIniFile::LoadData()            @0x004EC700
    //   void __thiscall CIniFile::LoadStructuredConfig() @0x00504130
    char LoadData();
    void LoadStructuredConfig();
};

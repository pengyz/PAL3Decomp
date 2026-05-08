#pragma once

#include "gbengine/gbengine_types.h"
#include <windows.h>

// ======== Struct Declarations ========

class gbTimeCounter {
public:
    LARGE_INTEGER startTime;  // +0x00
    LARGE_INTEGER freq;       // +0x08
    double elapsed;           // +0x10
    double timestamp;         // +0x18: stored time value (used by C++ methods)

public:
    gbTimeCounter& operator=(const gbTimeCounter& p0);
    double Off();
    void On();
};

class gbNameVarBuf {
public:
    void* dataBuf;          // +0x00: data buffer
    int dataBufCapacity;    // +0x04: capacity of data buffer in bytes
    int dataBufUsed;        // +0x08: used bytes in data buffer
    void* varTable;         // +0x0C: variable descriptor table (16 bytes per entry)
    int varTableCapacity;   // +0x10: max number of entries in varTable
    int varCount;           // +0x14: number of registered variables
    int locked;             // +0x18: lock flag

public:
    gbNameVarBuf();
    ~gbNameVarBuf();
    gbNameVarBuf& operator=(const gbNameVarBuf& p0);
    void GetVariant(unsigned int p0, void* p1);
    int IsVarExist(unsigned int p0);
    void* LockVariant(unsigned int p0, int* p1);
    void RegVariant(unsigned int p0, int p1, int p2);
    void SetVariant(unsigned int p0, void* p1);
    void UnlockVariant();
};

// ======== CRC32 Functions ========

void gbCrc32Init(void);
unsigned int gbCrc32Compute(const char* data, int len);
unsigned int gbCrc32Compute(const char* str);

// ======== String Functions ========

char* gbStrChr(const char* str, const char* chars);
char* gbStrRChr(const char* str, const char* chars);
void gbStrToLowCase(char* dst, const char* src);
char* gbstrchr(char* str, char ch);
int gbstricmp(const char* a, const char* b);
char* gbstrindex(const char* str, int index);

// ======== Multi-byte Character Functions ========

int gbIsMultiChar(char* str, int pos);
int gbIsMultiCharHead(char* str, int pos);
int gbIsMultiCharTail(char* str, int pos);

// ======== Time/Profiling Functions ========

void gbTimeCounterInit(void);
double gbUpdateCurTime(void);
double gbGetCurTime(void);
unsigned int gbGetCurTick(void);
float gbGetDeltaTime(void);

// ======== Memory Functions ========

void gbMemCopy(void* dst, void* src, unsigned int size);

// ======== Message Box Functions ========

int gbMessageBox(char* Format, ...);
int gbErrorBox(UINT uType, char* Format, ...);
double gbGetFrameRate(void);
double gbGetTime(void);

// ======== Logging Functions ========

void gbLogInfo(char* fmt, ...);
void gbPopErrorBox(char* fmt, ...);
void gbReportError(const char* fmt, ...);

// ======== Profiling Functions ========

void ProfileInit(void);
void ProfileBegin(char* name);
void ProfileEnd(char* name);
void ProfileDumpOutputToFile(char* filename);

// ======== gbColorQuad Functions ========

void gbColorQuad_DefaultCtor(gbColorQuad* This);
void gbColorQuad_RGBCtor(gbColorQuad* This, unsigned char r, unsigned char g, unsigned char b);
void gbColorQuad_RGBACtor(gbColorQuad* This, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void gbColorQuad_CopyCtor(gbColorQuad* This, const gbColorQuad* other);
gbColorQuad* gbColorQuad_Assign(gbColorQuad* This, const gbColorQuad* other);

// ======== gbColorFlt Functions ========

void gbColorFlt_DefaultCtor(gbColorFlt* This);
void gbColorFlt_RGBCtor(gbColorFlt* This, float r, float g, float b);
void gbColorFlt_RGBACtor(gbColorFlt* This, float r, float g, float b, float a);
gbColorFlt* gbColorFlt_Assign(gbColorFlt* This, const gbColorFlt* other);
int gbColorFlt_NotEqual(gbColorFlt* This, gbColorFlt* other);
gbColorFlt* gbColorFlt_AddAssign(gbColorFlt* This, const gbColorFlt* other);

// ======== gbNameVarBuf Functions ========

void gbNameVarBuf_Ctor(gbNameVarBuf* This);
void gbNameVarBuf_Dtor(gbNameVarBuf* This);
gbNameVarBuf* gbNameVarBuf_Assign(gbNameVarBuf* This, const gbNameVarBuf* other);
void gbNameVarBuf_RegVariant(gbNameVarBuf* This, unsigned int nameHash, int size, int type);
int gbNameVarBuf_IsVarExist(gbNameVarBuf* This, unsigned int nameHash);
void gbNameVarBuf_GetVariant(gbNameVarBuf* This, unsigned int nameHash, void* outBuf);
void gbNameVarBuf_SetVariant(gbNameVarBuf* This, unsigned int nameHash, void* inBuf);
void* gbNameVarBuf_LockVariant(gbNameVarBuf* This, unsigned int nameHash, int* outSize);
void gbNameVarBuf_UnlockVariant(gbNameVarBuf* This);

// ======== gbTimeCounter Functions ========

void gbTimeCounter_On(gbTimeCounter* This);
double gbTimeCounter_Off(gbTimeCounter* This);

#pragma once

#include "gbengine/gbengine_types.h"
#include <windows.h>

// ======== Struct Declarations ========

struct gbTimeCounter {
    LARGE_INTEGER startTime;
    LARGE_INTEGER freq;
    double elapsed;
};

struct gbNameVarBuf {
    void* impl;
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

// ======== Logging Functions ========

void gbLogInfo(char* fmt, ...);
void gbPopErrorBox(char* fmt, ...);
void gbReportError(char* fmt, ...);

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

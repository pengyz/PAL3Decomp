/**
 * gbengine.dll - gbMisc
 * Utility functions and classes for gbengine
 */

#include "gbengine/gbengine_types.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <mmsystem.h>

// Forward declarations for types used in this file
struct gbTimeCounter {
    LARGE_INTEGER startTime;
    LARGE_INTEGER freq;
    double elapsed;
};

struct gbNameVarBuf {
    void* impl;
};

class gbGfxManager;

// CRC32 table
static unsigned int gbCrc32Table[256];

// Timing globals
static LARGE_INTEGER gbTimeFreq;
static LARGE_INTEGER gbTimeStart;
static int gbTimeInitialized = 0;

// Global time variables (defined in header)
double g_CurrentTime = 0.0;
unsigned int g_CurrentTick = 0;

// gbColorQuad static member
static int gbColorQuad_ColorQuadFmt = 0;

// ======== CRC32 Functions ========

void gbCrc32Init(void)
{
    unsigned int i, j, crc;

    for (i = 0; i < 256; i++) {
        crc = i << 24;
        for (j = 0; j < 8; j++) {
            if (crc & 0x80000000) {
                crc = (crc << 1) ^ 0x04C11DB7;
            } else {
                crc = crc << 1;
            }
        }
        gbCrc32Table[i] = crc;
    }
}

unsigned int gbCrc32Compute(const char* data, int len)
{
    if (len == 0) {
        return 0;
    }

    unsigned int crc = 0;
    const unsigned char* ptr = (const unsigned char*)data;

    // Process first 1-3 bytes to build initial value
    if (len >= 1) {
        crc = ptr[0] << 24;
        if (len >= 2) {
            crc |= ptr[1] << 16;
            if (len >= 3) {
                crc |= ptr[2] << 8;
                if (len >= 4) {
                    crc |= ptr[3];
                }
            }
        }
    }

    crc = ~crc;

    // Process remaining bytes (after first 4)
    int remaining = len - 4;
    if (remaining > 0) {
        ptr += 4;
        for (int i = 0; i < remaining; i++) {
            crc = (crc << 8 | ptr[i]) ^ gbCrc32Table[crc >> 24];
        }
    }

    return ~crc;
}

unsigned int gbCrc32Compute(const char* str)
{
    return gbCrc32Compute(str, (int)strlen(str));
}

// ======== String Functions ========

char* gbStrChr(const char* str, const char* chars)
{
    char c = *str;
    if (c == '\0') {
        return NULL;
    }

    const char* p;
    do {
        p = chars;
        char ch = *p;
        while (ch != '\0') {
            if (c == ch) {
                return (char*)str;
            }
            p++;
            ch = *p;
        }
        str++;
        c = *str;
    } while (c != '\0');

    return NULL;
}

char* gbStrRChr(const char* str, const char* chars)
{
    const char* last = NULL;
    const char* p = str;

    while (*p != '\0') {
        const char* ch = chars;
        while (*ch != '\0') {
            if (*p == *ch) {
                last = p;
                break;
            }
            ch++;
        }
        p++;
    }

    return (char*)last;
}

void gbStrToLowCase(char* dst, const char* src)
{
    if (*src == '\0') {
        *dst = '\0';
        return;
    }

    while (*src != '\0') {
        char c = *src;
        if (c >= 'A' && c <= 'Z') {
            c = c + 0x20;
        }
        *dst = c;
        src++;
        dst++;
    }
    *dst = '\0';
}

char* gbstrchr(char* str, char ch)
{
    return strchr(str, ch);
}

int gbstricmp(const char* a, const char* b)
{
    char buf1[2048];
    char buf2[2048];

    gbStrToLowCase(buf1, a);
    gbStrToLowCase(buf2, b);

    return strcmp(buf1, buf2);
}

char* gbstrindex(const char* str, int index)
{
    if (index < 0) {
        return (char*)str;
    }

    const char* p = str;
    for (int i = 0; i < index && *p != '\0'; i++) {
        if (IsDBCSLeadByte((BYTE)*p) && *(p + 1) != '\0') {
            p += 2;
        } else {
            p++;
        }
    }

    return (char*)p;
}

// ======== Multi-byte Character Functions ========

int gbIsMultiChar(char* str, int pos)
{
    if (pos < 0) {
        return 0;
    }

    int state = 0;
    for (int i = 0; i <= pos; i++) {
        unsigned char c = (unsigned char)str[i];

        if (state == 0) {
            if (c > 0x7F) {
                state = 1;
            }
        } else if (state == 1) {
            state = 2;
        } else if (state == 2) {
            state = (c > 0x7F) ? 1 : 0;
        }
    }

    return (state != 0) ? 1 : 0;
}

int gbIsMultiCharHead(char* str, int pos)
{
    if (pos < 0) {
        return 0;
    }

    unsigned char c = (unsigned char)str[pos];
    if (c <= 0x7F) {
        return 0;
    }

    // Check if previous position analysis shows we're at a lead byte
    int state = 0;
    for (int i = 0; i < pos; i++) {
        unsigned char ch = (unsigned char)str[i];
        if (state == 0) {
            if (ch > 0x7F) {
                state = 1;
            }
        } else {
            state = 0;
        }
    }

    return (state == 0) ? 1 : 0;
}

int gbIsMultiCharTail(char* str, int pos)
{
    if (pos < 0) {
        return 0;
    }

    unsigned char c = (unsigned char)str[pos];
    if (c <= 0x7F) {
        return 0;
    }

    // Check if previous position analysis shows we're at a trail byte
    int state = 0;
    for (int i = 0; i < pos; i++) {
        unsigned char ch = (unsigned char)str[i];
        if (state == 0) {
            if (ch > 0x7F) {
                state = 1;
            }
        } else {
            state = 0;
        }
    }

    return (state == 1) ? 1 : 0;
}

// ======== Time/Profiling Functions ========

void gbTimeCounterInit(void)
{
    gbTimeInitialized = 1;

    LARGE_INTEGER freq;
    if (QueryPerformanceFrequency(&freq)) {
        gbTimeFreq = freq;

        TIMECAPS tc;
        timeGetDevCaps(&tc, sizeof(TIMECAPS));

        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);

        double freqDbl = (double)freq.LowPart + (double)freq.HighPart * 4294967296.0;
        double counterDbl = (double)counter.LowPart + (double)counter.HighPart * 4294967296.0;
        g_CurrentTime = counterDbl / freqDbl;
    } else {
        g_CurrentTime = (double)GetTickCount() * 1000.0;
    }
}

double gbUpdateCurTime(void)
{
    if (gbTimeInitialized) {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);

        double freqDbl = (double)gbTimeFreq.LowPart + (double)gbTimeFreq.HighPart * 4294967296.0;
        double counterDbl = (double)counter.LowPart + (double)counter.HighPart * 4294967296.0;
        g_CurrentTime = counterDbl / freqDbl;
    } else {
        g_CurrentTime = (double)GetTickCount() * 1000.0;
    }

    return g_CurrentTime;
}

double gbGetCurTime(void)
{
    return g_CurrentTime;
}

unsigned int gbGetCurTick(void)
{
    return g_CurrentTick;
}

float gbGetDeltaTime(void)
{
    static double lastTime = 0.0;
    double curTime = g_CurrentTime;
    float delta = (float)(curTime - lastTime);
    lastTime = curTime;
    return delta;
}

// ======== Memory Functions ========

void gbMemCopy(void* dst, void* src, unsigned int size)
{
    unsigned int dwords = size >> 2;
    unsigned int bytes = size & 3;

    unsigned int* dstDW = (unsigned int*)dst;
    unsigned int* srcDW = (unsigned int*)src;

    for (unsigned int i = 0; i < dwords; i++) {
        *dstDW++ = *srcDW++;
    }

    unsigned char* dstB = (unsigned char*)dstDW;
    unsigned char* srcB = (unsigned char*)srcDW;

    for (unsigned int i = 0; i < bytes; i++) {
        *dstB++ = *srcB++;
    }
}

// ======== Logging Functions ========

void gbLogInfo(char* fmt, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    _vsnprintf(buffer, sizeof(buffer) - 1, fmt, args);
    va_end(args);
    buffer[sizeof(buffer) - 1] = '\0';

    OutputDebugStringA(buffer);
}

void gbPopErrorBox(char* fmt, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    _vsnprintf(buffer, sizeof(buffer) - 1, fmt, args);
    va_end(args);
    buffer[sizeof(buffer) - 1] = '\0';

    MessageBoxA(NULL, buffer, "Error", MB_OK | MB_ICONERROR);
}

void gbReportError(char* fmt, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    _vsnprintf(buffer, sizeof(buffer) - 1, fmt, args);
    va_end(args);
    buffer[sizeof(buffer) - 1] = '\0';

    OutputDebugStringA(buffer);
}

// ======== Profiling Functions (Stubs) ========

void ProfileInit(void)
{
    // Stub - profiling not implemented
}

void ProfileBegin(char* name)
{
    // Stub - profiling not implemented
}

void ProfileEnd(char* name)
{
    // Stub - profiling not implemented
}

void ProfileDumpOutputToFile(char* filename)
{
    // Stub - profiling not implemented
}

// ======== gbColorQuad Class ========

namespace {
    // Helper to handle ColorQuadFmt byte ordering
    inline void SetColorQuadBytes(gbColorQuad* cq, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        if (gbColorQuad_ColorQuadFmt == 0) {
            cq->b = b;
            cq->g = g;
            cq->r = r;
            cq->a = a;
        } else {
            cq->b = r;
            cq->g = g;
            cq->r = b;
            cq->a = a;
        }
    }
}

// gbColorQuad constructors
void gbColorQuad_DefaultCtor(gbColorQuad* This)
{
    This->b = 0;
    This->g = 0;
    This->r = 0;
    This->a = 0;
}

void gbColorQuad_RGBCtor(gbColorQuad* This, unsigned char r, unsigned char g, unsigned char b)
{
    SetColorQuadBytes(This, r, g, b, 0xFF);
}

void gbColorQuad_RGBACtor(gbColorQuad* This, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    SetColorQuadBytes(This, r, g, b, a);
}

void gbColorQuad_CopyCtor(gbColorQuad* This, const gbColorQuad* other)
{
    This->b = other->b;
    This->g = other->g;
    This->r = other->r;
    This->a = other->a;
}

gbColorQuad* gbColorQuad_Assign(gbColorQuad* This, const gbColorQuad* other)
{
    This->b = other->b;
    This->g = other->g;
    This->r = other->r;
    This->a = other->a;
    return This;
}

// ======== gbColorFlt Class ========

void gbColorFlt_DefaultCtor(gbColorFlt* This)
{
    This->r = 0.0f;
    This->g = 0.0f;
    This->b = 0.0f;
    This->a = 0.0f;
}

void gbColorFlt_RGBCtor(gbColorFlt* This, float r, float g, float b)
{
    This->r = r;
    This->g = g;
    This->b = b;
    This->a = 1.0f;
}

void gbColorFlt_RGBACtor(gbColorFlt* This, float r, float g, float b, float a)
{
    This->r = r;
    This->g = g;
    This->b = b;
    This->a = a;
}

gbColorFlt* gbColorFlt_Assign(gbColorFlt* This, const gbColorFlt* other)
{
    This->r = other->r;
    This->g = other->g;
    This->b = other->b;
    This->a = other->a;
    return This;
}

int gbColorFlt_NotEqual(gbColorFlt* This, gbColorFlt* other)
{
    return (This->r != other->r || This->g != other->g ||
            This->b != other->b || This->a != other->a) ? 1 : 0;
}

gbColorFlt* gbColorFlt_AddAssign(gbColorFlt* This, const gbColorFlt* other)
{
    This->r += other->r;
    This->g += other->g;
    This->b += other->b;
    This->a += other->a;
    return This;
}

// ======== gbNameVarBuf Class ========

struct gbNameVarBufImpl {
    void* buffer;
    int varCount;
    struct VarInfo {
        unsigned int nameHash;
        int offset;
        int size;
        int type;
    } vars[64];
};

void gbNameVarBuf_Ctor(gbNameVarBuf* This)
{
    gbNameVarBufImpl* impl = new gbNameVarBufImpl;
    impl->buffer = NULL;
    impl->varCount = 0;
    *(gbNameVarBufImpl**)This = impl;
}

void gbNameVarBuf_Dtor(gbNameVarBuf* This)
{
    gbNameVarBufImpl* impl = *(gbNameVarBufImpl**)This;
    if (impl) {
        if (impl->buffer) {
            delete[] (char*)impl->buffer;
        }
        delete impl;
    }
}

gbNameVarBuf* gbNameVarBuf_Assign(gbNameVarBuf* This, const gbNameVarBuf* other)
{
    gbNameVarBufImpl* thisImpl = *(gbNameVarBufImpl**)This;
    gbNameVarBufImpl* otherImpl = *(gbNameVarBufImpl**)other;

    if (thisImpl && otherImpl) {
        // Simple shallow copy for now
        thisImpl->varCount = otherImpl->varCount;
        memcpy(thisImpl->vars, otherImpl->vars, sizeof(thisImpl->vars));
    }

    return This;
}

void gbNameVarBuf_RegVariant(gbNameVarBuf* This, unsigned int nameHash, int size, int type)
{
    gbNameVarBufImpl* impl = *(gbNameVarBufImpl**)This;
    if (!impl || impl->varCount >= 64) {
        return;
    }

    int offset = 0;
    for (int i = 0; i < impl->varCount; i++) {
        offset += impl->vars[i].size;
    }

    impl->vars[impl->varCount].nameHash = nameHash;
    impl->vars[impl->varCount].offset = offset;
    impl->vars[impl->varCount].size = size;
    impl->vars[impl->varCount].type = type;
    impl->varCount++;

    // Reallocate buffer if needed
    if (impl->buffer) {
        delete[] (char*)impl->buffer;
    }
    impl->buffer = new char[offset + size];
    memset(impl->buffer, 0, offset + size);
}

int gbNameVarBuf_IsVarExist(gbNameVarBuf* This, unsigned int nameHash)
{
    gbNameVarBufImpl* impl = *(gbNameVarBufImpl**)This;
    if (!impl) {
        return 0;
    }

    for (int i = 0; i < impl->varCount; i++) {
        if (impl->vars[i].nameHash == nameHash) {
            return 1;
        }
    }

    return 0;
}

void gbNameVarBuf_GetVariant(gbNameVarBuf* This, unsigned int nameHash, void* outBuf)
{
    gbNameVarBufImpl* impl = *(gbNameVarBufImpl**)This;
    if (!impl || !impl->buffer) {
        return;
    }

    for (int i = 0; i < impl->varCount; i++) {
        if (impl->vars[i].nameHash == nameHash) {
            char* src = (char*)impl->buffer + impl->vars[i].offset;
            memcpy(outBuf, src, impl->vars[i].size);
            return;
        }
    }
}

void gbNameVarBuf_SetVariant(gbNameVarBuf* This, unsigned int nameHash, void* inBuf)
{
    gbNameVarBufImpl* impl = *(gbNameVarBufImpl**)This;
    if (!impl || !impl->buffer) {
        return;
    }

    for (int i = 0; i < impl->varCount; i++) {
        if (impl->vars[i].nameHash == nameHash) {
            char* dst = (char*)impl->buffer + impl->vars[i].offset;
            memcpy(dst, inBuf, impl->vars[i].size);
            return;
        }
    }
}

void* gbNameVarBuf_LockVariant(gbNameVarBuf* This, unsigned int nameHash, int* outSize)
{
    gbNameVarBufImpl* impl = *(gbNameVarBufImpl**)This;
    if (!impl || !impl->buffer) {
        return NULL;
    }

    for (int i = 0; i < impl->varCount; i++) {
        if (impl->vars[i].nameHash == nameHash) {
            if (outSize) {
                *outSize = impl->vars[i].size;
            }
            return (char*)impl->buffer + impl->vars[i].offset;
        }
    }

    return NULL;
}

void gbNameVarBuf_UnlockVariant(gbNameVarBuf* This)
{
    // No-op
}

// ======== gbTimeCounter Class ========

void gbTimeCounter_On(gbTimeCounter* This)
{
    QueryPerformanceFrequency(&This->freq);
    QueryPerformanceCounter(&This->startTime);
}

double gbTimeCounter_Off(gbTimeCounter* This)
{
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);

    double freqDbl = (double)This->freq.LowPart + (double)This->freq.HighPart * 4294967296.0;
    double startDbl = (double)This->startTime.LowPart + (double)This->startTime.HighPart * 4294967296.0;
    double endDbl = (double)endTime.LowPart + (double)endTime.HighPart * 4294967296.0;

    This->elapsed = (endDbl - startDbl) / freqDbl;
    return This->elapsed;
}

// ======== gbPixelFormat Class ========

enum gbPixelFmtType {
    PIXFMT_UNKNOWN = 0,
    PIXFMT_R8G8B8 = 1,
    PIXFMT_A8R8G8B8 = 2,
    PIXFMT_X8R8G8B8 = 3,
    PIXFMT_R5G6B5 = 4,
    PIXFMT_X1R5G5B5 = 5,
    PIXFMT_A1R5G5B5 = 6,
    PIXFMT_A4R4G4B4 = 7,
    PIXFMT_A8 = 8,
    PIXFMT_PALETTE8 = 9
};

struct gbPixelFormatImpl {
    int bpp;
    unsigned int rMask, gMask, bMask, aMask;
    int rShift, gShift, bShift, aShift;
    int rBits, gBits, bBits, aBits;
    gbColorQuad* palette;
};

gbPixelFormat* gbPixelFormat_Assign(gbPixelFormat* This, const gbPixelFormat* other)
{
    memcpy(This, other, sizeof(gbPixelFormatImpl));
    return This;
}

void gbPixelFormat_Init_Masks(gbPixelFormat* This, int bpp, unsigned int rMask, unsigned int gMask, unsigned int bMask, unsigned int aMask)
{
    gbPixelFormatImpl* impl = (gbPixelFormatImpl*)This;
    impl->bpp = bpp;
    impl->rMask = rMask;
    impl->gMask = gMask;
    impl->bMask = bMask;
    impl->aMask = aMask;
    impl->palette = NULL;

    // Calculate shifts and bits (simplified)
    impl->rShift = 0;
    impl->gShift = 0;
    impl->bShift = 0;
    impl->aShift = 0;
    impl->rBits = 8;
    impl->gBits = 8;
    impl->bBits = 8;
    impl->aBits = 8;
}

void gbPixelFormat_Init_Palette(gbPixelFormat* This, int bpp, gbColorQuad* palette)
{
    gbPixelFormatImpl* impl = (gbPixelFormatImpl*)This;
    impl->bpp = bpp;
    impl->palette = palette;
    impl->rMask = impl->gMask = impl->bMask = impl->aMask = 0;
}

void gbPixelFormat_Init_Copy(gbPixelFormat* This, gbPixelFormat* other)
{
    memcpy(This, other, sizeof(gbPixelFormatImpl));
}

void gbPixelFormat_Init_Type(gbPixelFormat* This, gbPixelFmtType type)
{
    gbPixelFormatImpl* impl = (gbPixelFormatImpl*)This;

    switch (type) {
    case PIXFMT_A8R8G8B8:
        impl->bpp = 32;
        impl->aMask = 0xFF000000;
        impl->rMask = 0x00FF0000;
        impl->gMask = 0x0000FF00;
        impl->bMask = 0x000000FF;
        break;
    case PIXFMT_R8G8B8:
        impl->bpp = 24;
        impl->rMask = 0x00FF0000;
        impl->gMask = 0x0000FF00;
        impl->bMask = 0x000000FF;
        impl->aMask = 0;
        break;
    default:
        impl->bpp = 0;
        impl->rMask = impl->gMask = impl->bMask = impl->aMask = 0;
        break;
    }

    impl->palette = NULL;
}

void gbPixelFormat_Convert(gbPixelFormat* This, unsigned char* dst, gbPixelFormat* dstFmt, unsigned char* src, int pixelCount)
{
    // Stub - pixel format conversion is complex
    // For now just do a simple copy
    gbPixelFormatImpl* srcImpl = (gbPixelFormatImpl*)This;
    gbPixelFormatImpl* dstImpl = (gbPixelFormatImpl*)dstFmt;

    int srcBytes = (srcImpl->bpp / 8) * pixelCount;
    int dstBytes = (dstImpl->bpp / 8) * pixelCount;
    int copyBytes = (srcBytes < dstBytes) ? srcBytes : dstBytes;

    memcpy(dst, src, copyBytes);
}

void gbPixelFormat_Release(gbPixelFormat* This)
{
    gbPixelFormatImpl* impl = (gbPixelFormatImpl*)This;
    impl->palette = NULL;
    impl->bpp = 0;
}

// ======== gbUIRect Class ========

struct gbUIRectImpl {
    float left, top, right, bottom;
    void* texture;
    void* gfxMgr;
};

gbUIRect* gbUIRect_Assign(gbUIRect* This, const gbUIRect* other)
{
    memcpy(This, other, sizeof(gbUIRectImpl));
    return This;
}

void gbUIRect_Init(gbUIRect* This, char* textureName, float left, float top, float right, float bottom, void* gfx)
{
    gbUIRectImpl* impl = (gbUIRectImpl*)This;
    impl->left = left;
    impl->top = top;
    impl->right = right;
    impl->bottom = bottom;
    impl->texture = NULL;
    impl->gfxMgr = gfx;
}

void gbUIRect_Release(gbUIRect* This)
{
    gbUIRectImpl* impl = (gbUIRectImpl*)This;
    impl->texture = NULL;
    impl->gfxMgr = NULL;
}

void gbUIRect_Render(gbUIRect* This, int flags)
{
    // Stub - rendering not implemented
}

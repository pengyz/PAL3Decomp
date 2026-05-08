/**
 * gbengine.dll - gbMisc
 * Utility functions and classes for gbengine
 */

#include "gbengine/gbMisc.h"
#include "gbengine/gbTexture.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <mmsystem.h>

// CRC32 table
static unsigned int gbCrc32Table[256];

// Timing globals (ordered to match original memory layout)
static TIMECAPS gbTimeCaps;
static int gbHasPerfCounter = 0;
static int gbTimeInitialized = 0;
static double gbTimeFreqDbl = 0.0;

// Global time variables (defined in header)
double g_CurrentTime = 0.0;
unsigned int g_CurrentTick = 0;

// gbColorQuad static member
static int gbColorQuad_ColorQuadFmt = 0;

// ======== CRC32 Functions ========

void gbCrc32Init(void)
{
    int i, j;
    unsigned int crc;

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
    unsigned int crc;
    const unsigned char* p;

    if (*str == 0) {
        return 0;
    }

    crc = (unsigned int)(unsigned char)*str << 24;
    p = (const unsigned char*)str + 1;

    if (*p != 0) {
        crc |= (unsigned int)*p << 16;
        p = (const unsigned char*)str + 2;
        if (str[2] != 0) {
            crc |= (unsigned int)(unsigned char)str[2] << 8;
            p = (const unsigned char*)str + 3;
            if (str[3] != 0) {
                crc |= (unsigned char)str[3];
                p = (const unsigned char*)str + 4;
            }
        }
    }

    crc = ~crc;

    while (*p != 0) {
        crc = (crc << 8 | *p) ^ gbCrc32Table[crc >> 24];
        p++;
    }

    return ~crc;
}

// ======== String Functions ========

char* gbStrChr(const char* str, const char* chars)
{
    if (*str == '\0') {
        return NULL;
    }

    do {
        const char* p = chars;
        while (*p) {
            if (*str == *p) {
                return (char*)str;
            }
            p++;
        }
        str++;
    } while (*str);

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
    char* p = dst;
    if (*src) {
        int offset = src - dst;
        do {
            char c = p[offset];
            if (c >= 'A' && c <= 'Z')
                c += 32;
            *p = c;
        } while (p++[offset + 1]);
    }
    *p = '\0';
}

char* gbstrchr(char* str, char ch)
{
    char* result = str;
    char c = *result;
    while (c) {
        if ((unsigned char)c > 0x7Fu) {
            result++;
        } else if (c == ch) {
            return result;
        }
        c = result[1];
        result++;
    }
    return 0;
}

int gbstricmp(const char* a, const char* b)
{
    char buf1[2048];
    char buf2[2048];
    char *dst;
    char c;
    unsigned char c1, c2;
    unsigned char *s1, *s2;

    dst = buf1;
    c = *a;
    if (c != '\0') {
        do {
            if (c < 'A' || c > 'Z')
                ;
            else
                c = c + 0x20;
            *dst = c;
            c = *(a + 1);
            dst++;
            a++;
        } while (c != '\0');
    }
    *dst = '\0';

    dst = buf2;
    c = *b;
    if (c != '\0') {
        do {
            if (c < 'A' || c > 'Z')
                ;
            else
                c = c + 0x20;
            *dst = c;
            c = *(b + 1);
            dst++;
            b++;
        } while (c != '\0');
    }
    *dst = '\0';

    s1 = (unsigned char*)buf1;
    s2 = (unsigned char*)buf2;
    for (;;) {
        c1 = *s1;
        c2 = *s2;
        if (c1 != c2) break;
        if (c1 == 0) return 0;
        c1 = s1[1];
        c2 = s2[1];
        if (c1 != c2) break;
        s1 += 2;
        s2 += 2;
        if (c1 == 0) return 0;
    }
    if (c1 < c2) return -1;
    return 1;
}

char* gbstrindex(const char* str, int index)
{
    int count = 0;
    char* result = (char*)str;

    if (*str) {
        while (count != index) {
            if ((unsigned char)*result <= 0x7Fu)
                result++;
            else
                result += 2;
            count++;
            if (!*result)
                goto end_of_string;
        }
    } else {
end_of_string:
        if (index < 0) {
            int target = count + index;
            int i = 0;
            result = (char*)str;
            if (*str) {
                while (i != target) {
                    if ((unsigned char)*result <= 0x7Fu)
                        result++;
                    else
                        result += 2;
                    i++;
                    if (!*result)
                        return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    return result;
}

// ======== Multi-byte Character Functions ========

int gbIsMultiChar(char* str, int pos)
{
    int state = 0;
    int i = 0;
    if (pos < 0)
        return 0;
    do {
        unsigned char c = (unsigned char)str[i];
        switch (state) {
        case 0:
            if (c > 0x7F)
                state = 1;
            break;
        case 1:
            state = 2;
            break;
        case 2:
            state = (c >= 0x80);
            break;
        }
        i++;
    } while (i <= pos);
    if (state != 0)
        return 1;
    return 0;
}

int gbIsMultiCharHead(char* str, int pos)
{
    int state = 0;
    int i = 0;
    if (pos < 0)
        return 0;
    do {
        unsigned char c = (unsigned char)str[i];
        switch (state) {
        case 0:
            if (c > 0x7F)
                state = 1;
            break;
        case 1:
            state = 2;
            break;
        case 2:
            state = (c >= 0x80);
            break;
        }
        i++;
    } while (i <= pos);
    if (state == 1)
        return 1;
    return 0;
}

int gbIsMultiCharTail(char* str, int pos)
{
    int state = 0;
    int i = 0;
    if (pos < 0)
        return 0;
    do {
        unsigned char c = (unsigned char)str[i];
        switch (state) {
        case 0:
            if (c > 0x7F)
                state = 1;
            break;
        case 1:
            state = 2;
            break;
        case 2:
            state = (c >= 0x80);
            break;
        }
        i++;
    } while (i <= pos);
    if (state == 2)
        return 1;
    return 0;
}

// ======== Time/Profiling Functions ========

void gbTimeCounterInit(void)
{
    LARGE_INTEGER freq;
    LARGE_INTEGER counter;

    gbTimeInitialized = 1;

    if (!QueryPerformanceFrequency(&freq)) {
        if (gbHasPerfCounter) {
            QueryPerformanceCounter(&counter);
            g_CurrentTime = ((double)counter.HighPart * 4294967296.0 + (double)(unsigned int)counter.LowPart) / gbTimeFreqDbl;
        } else {
            g_CurrentTime = (double)timeGetTime() * 1000.0;
        }
        return;
    }

    gbHasPerfCounter = 1;
    gbTimeFreqDbl = (double)freq.HighPart * 4294967296.0 + (double)(unsigned int)freq.LowPart;
    timeGetDevCaps(&gbTimeCaps, 8);

    if (gbHasPerfCounter) {
        QueryPerformanceCounter(&counter);
        g_CurrentTime = ((double)counter.HighPart * 4294967296.0 + (double)(unsigned int)counter.LowPart) / gbTimeFreqDbl;
    } else {
        g_CurrentTime = (double)timeGetTime() * 1000.0;
    }
}

double gbUpdateCurTime(void)
{
    double result;
    if (gbHasPerfCounter) {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        result = ((double)counter.HighPart * 4294967296.0 + (double)(unsigned int)counter.LowPart) / gbTimeFreqDbl;
    } else {
        result = (double)timeGetTime() * 1000.0;
    }
    g_CurrentTime = result;
    return result;
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
    static int lastTime = 0;
    int oldTime = lastTime;
    int curTime = clock();
    lastTime = curTime;
    if (!oldTime)
        return 0.0f;
    return (float)((curTime - oldTime) * 0.001);
}

// ======== Memory Functions ========

void gbMemCopy(void* pDst, void* pSrc, unsigned int nBytes)
{
    __asm {
        mov ecx, nBytes
        mov esi, pSrc
        mov edi, pDst
        mov ebx, ecx
        shr ecx, 2
        and ebx, 3
        rep movsd
        mov ecx, ebx
        rep movsb
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

// ======== Profiling Functions ========

#define NUM_PROFILE_ENTRIES 50

struct ProfileEntry {
    char isActive;
    char _pad[3];
    int totalCalls;
    int nestingCount;
    char name[256];
    float startTime;
    float selfTime;
    float childTime;
    int childCount;
};

struct ProfileOutput {
    char flag;
    char _data[0x10f];
};

static ProfileEntry g_profileEntries[NUM_PROFILE_ENTRIES];
static ProfileOutput g_profileOutputs[NUM_PROFILE_ENTRIES];
static float g_profileTime;

extern float GetTimeSeconds(void);
static void ProfileFormatOutput(char* buffer);
static ProfileEntry* g_profileEnd = &g_profileEntries[NUM_PROFILE_ENTRIES];

// 0x10031750 (46B)
void ProfileInit(void)
{
    ProfileOutput* p2 = g_profileOutputs;
    ProfileEntry* p1 = g_profileEntries;
    do {
        p1->isActive = 0;
        p2->flag = 0;
        p1++;
        p2++;
    } while ((int)p1 < (int)&g_profileEntries[NUM_PROFILE_ENTRIES]);
    g_profileTime = GetTimeSeconds();
}

void ProfileBegin(char* name)
{
    unsigned int i = 0;
    char* pName = g_profileEntries[0].name;

    while (*(pName - 12) == 1) {
        if (!strcmp(pName, name)) {
            int idx = 71 * i;
            int count = ((int*)&g_profileEntries[0])[idx] + 1;
            ((int*)&g_profileEntries[0])[idx] = count;
            ((int*)&g_profileEntries[0])[idx - 1] = ((int*)&g_profileEntries[0])[idx - 1] + 1;
            ((float*)&g_profileEntries[0])[idx + 67] = GetTimeSeconds();
            return;
        }
        pName += 284;
        ++i;
        if ((int)pName >= (int)g_profileEnd->name)
            return;
    }
    if (i < 0x32) {
        strcpy(g_profileEntries[i].name, name);
        g_profileEntries[i].isActive = 1;
        g_profileEntries[i].nestingCount = 1;
        g_profileEntries[i].totalCalls = 1;
        g_profileEntries[i].selfTime = 0;
        g_profileEntries[i].startTime = GetTimeSeconds();
        g_profileEntries[i].childTime = 0;
    }
}

void ProfileEnd(char* name)
{
    int i = 0;
    char* pName = g_profileEntries[0].name;

    while (*(pName - 12) == 1) {
        if (!strcmp(pName, name)) {
            int deepest = 0;
            int deepIdx = -1;
            float endTime = GetTimeSeconds();
            int idx = 71 * i;
            --((int*)&g_profileEntries[0])[idx];
            if (g_profileEntries[0].isActive == 1) {
                int childCount = 0;
                int j = 0;
                int jidx = 0;
                int doffs = -284;
                do {
                    if (((int*)&g_profileEntries[0])[jidx] > 0) {
                        ++childCount;
                        if (deepIdx < 0 || ((float*)&g_profileEntries[0])[jidx + 67] >= *(float*)((char*)&g_profileEntries[0].startTime + doffs)) {
                            deepIdx = j;
                            doffs = jidx * 4;
                        }
                    }
                    jidx += 71;
                    ++j;
                } while (((char*)&g_profileEntries[0])[jidx * 4] == 1);
                g_profileEntries[i].childCount = childCount;
            } else {
                g_profileEntries[i].childCount = 0;
            }
            if (deepIdx >= 0)
                g_profileEntries[deepIdx].childTime = endTime - g_profileEntries[i].startTime + g_profileEntries[deepIdx].childTime;
            g_profileEntries[i].selfTime = endTime - g_profileEntries[i].startTime + g_profileEntries[i].selfTime;
            return;
        }
        pName += 284;
        ++i;
        if ((int)pName >= (int)g_profileEnd->name)
            return;
    }
}

static void ProfileFormatOutput(char* buffer)
{
    buffer[0] = '\0';
}

void ProfileDumpOutputToFile(char* filename)
{
    FILE* fp = fopen(filename, "wt");
    char buffer[16384];
    ProfileFormatOutput(buffer);
    fprintf(fp, "%s", buffer);
    fclose(fp);
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

void gbPixelFormat::Convert(unsigned char* src, gbPixelFormat* dstFmt, unsigned char* dst, int numPixels) {
    if (!src || !dst || !dstFmt || numPixels <= 0) {
        return;
    }

    int srcBytesPerPixel = Bpp / 8;
    int dstBytesPerPixel = dstFmt->Bpp / 8;

    for (int i = 0; i < numPixels; i++) {
        unsigned int r, g, b, a;

        // Extract from source format
        if (Type == GB_PFT_P8 && Pal) {
            unsigned char index = src[i];
            r = Pal[index].r;
            g = Pal[index].g;
            b = Pal[index].b;
            a = Pal[index].a;
        } else {
            unsigned int pixel = 0;
            memcpy(&pixel, src + i * srcBytesPerPixel, srcBytesPerPixel);

            r = (pixel & r_mask) >> r_shift;
            g = (pixel & g_mask) >> g_shift;
            b = (pixel & b_mask) >> b_shift;
            a = a_mask ? ((pixel & a_mask) >> a_shift) : 0xFF;

            // Scale to 8-bit
            if (r_mask) {
                unsigned int rBits = 0;
                unsigned int temp = r_mask;
                while (temp) { rBits++; temp >>= 1; }
                r = (r * 255) / ((1 << rBits) - 1);
            }
            if (g_mask) {
                unsigned int gBits = 0;
                unsigned int temp = g_mask;
                while (temp) { gBits++; temp >>= 1; }
                g = (g * 255) / ((1 << gBits) - 1);
            }
            if (b_mask) {
                unsigned int bBits = 0;
                unsigned int temp = b_mask;
                while (temp) { bBits++; temp >>= 1; }
                b = (b * 255) / ((1 << bBits) - 1);
            }
            if (a_mask) {
                unsigned int aBits = 0;
                unsigned int temp = a_mask;
                while (temp) { aBits++; temp >>= 1; }
                a = (a * 255) / ((1 << aBits) - 1);
            }
        }

        // Pack into destination format
        unsigned int dstPixel = 0;
        if (dstFmt->r_mask) {
            unsigned int rBits = 0;
            unsigned int temp = dstFmt->r_mask >> dstFmt->r_shift;
            while (temp) { rBits++; temp >>= 1; }
            r = (r * ((1 << rBits) - 1)) / 255;
            dstPixel |= (r << dstFmt->r_shift) & dstFmt->r_mask;
        }
        if (dstFmt->g_mask) {
            unsigned int gBits = 0;
            unsigned int temp = dstFmt->g_mask >> dstFmt->g_shift;
            while (temp) { gBits++; temp >>= 1; }
            g = (g * ((1 << gBits) - 1)) / 255;
            dstPixel |= (g << dstFmt->g_shift) & dstFmt->g_mask;
        }
        if (dstFmt->b_mask) {
            unsigned int bBits = 0;
            unsigned int temp = dstFmt->b_mask >> dstFmt->b_shift;
            while (temp) { bBits++; temp >>= 1; }
            b = (b * ((1 << bBits) - 1)) / 255;
            dstPixel |= (b << dstFmt->b_shift) & dstFmt->b_mask;
        }
        if (dstFmt->a_mask) {
            unsigned int aBits = 0;
            unsigned int temp = dstFmt->a_mask >> dstFmt->a_shift;
            while (temp) { aBits++; temp >>= 1; }
            a = (a * ((1 << aBits) - 1)) / 255;
            dstPixel |= (a << dstFmt->a_shift) & dstFmt->a_mask;
        }

        memcpy(dst + i * dstBytesPerPixel, &dstPixel, dstBytesPerPixel);
    }
}

gbUIRect& gbUIRect::operator=(const gbUIRect& other) {
    memcpy(this, &other, 0x18);
    return *this;
}

void gbUIRect::Init(char* textureName, float inLeft, float inTop, float inRight, float inBottom, gbGfxManager* gfx) {
    m_pGfx = gfx;
    m_pTexture = NULL;
    left = inLeft;
    top = inTop;
    width = inRight - inLeft;
    height = inBottom - inTop;
}

void gbUIRect::Release(void) {
    m_pTexture->Release();
}

// ======== gbVec3D default constructor closure ========
// Note: VC6 automatically generates ??_FgbVec3D@@QAEXXZ (default constructor closure)
// for gbVec3D when used as a member in classes with virtual base classes.
// No manual alias needed when compiling with VC6.


// ============================================================
// Additional export implementations
// ============================================================

// Build timestamp (exported as DATA symbol)
extern "C" char stamp[] = "Mon Jan  5 16:39:11 2004";

#pragma auto_inline(off)

int gbColorQuad::ColorQuadFmt;

// ---- gbColorQuad ----
gbColorQuad::gbColorQuad(struct gbColorQuad & p0) { *(unsigned int*)this = *(unsigned int*)&p0; }

gbColorQuad::gbColorQuad(unsigned char p0, unsigned char p1, unsigned char p2) {
    if (ColorQuadFmt == 0) { r = p0; g = p1; b = p2; a = 0xFF; }
    else { r = p2; g = p1; b = p0; a = 0xFF; }
}

gbColorQuad::gbColorQuad(unsigned char p0, unsigned char p1, unsigned char p2, unsigned char p3) {
    if (ColorQuadFmt == 0) { r = p0; g = p1; b = p2; a = p3; }
    else { r = p2; g = p1; b = p0; a = p3; }
}

gbColorQuad::gbColorQuad() {
    b = g = r = a = 0;
}

struct gbColorQuad & gbColorQuad::operator=(struct gbColorQuad const & p0) { *(unsigned int*)this = *(unsigned int*)&p0; return *this; }

// ---- gbNameVarBuf ----
gbNameVarBuf::gbNameVarBuf() {
    dataBuf = 0;
    dataBufCapacity = 0;
    dataBufUsed = 0;
    varTable = 0;
    varTableCapacity = 0;
    varCount = 0;
    locked = 0;
}

void gbNameVarBuf::GetVariant(unsigned int p0, void * p1) {
    unsigned int* table = (unsigned int*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (table[i * 4] == p0) {
            unsigned int elemCount = table[i * 4 + 3];
            unsigned int elemSize = table[i * 4 + 1];
            unsigned int totalSize = elemCount * elemSize;
            memcpy(p1, (char*)dataBuf + table[i * 4 + 2], totalSize);
            return;
        }
    }
}

int gbNameVarBuf::IsVarExist(unsigned int p0) {
    unsigned int* table = (unsigned int*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (table[i * 4] == p0) {
            return 1;
        }
    }
    return 0;
}

struct VarDesc {
    unsigned int nameHash;
    unsigned int size;
    unsigned int offset;
    unsigned int count;
};

void* gbNameVarBuf::LockVariant(unsigned int nameHash, int* outSize) {
    VarDesc* desc = (VarDesc*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (desc[i].nameHash == nameHash) {
            locked = 1;
            if (outSize) {
                *outSize = desc[i].size;
            }
            return (char*)dataBuf + desc[i].offset;
        }
    }

    if (outSize) {
        *outSize = 0;
    }
    return NULL;
}

void gbNameVarBuf::RegVariant(unsigned int p0, int p1, int p2) {
    // Check if already registered
    unsigned int* table = (unsigned int*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (table[i * 4] == p0) {
            return;
        }
    }

    int totalDataSize = p1 * p2;

    // Grow data buffer if necessary
    if (dataBufUsed + totalDataSize > dataBufCapacity) {
        int newCap = (dataBufCapacity + totalDataSize) * 2;
        dataBufCapacity = newCap;
        void* newBuf = malloc(newCap);
        if (dataBufUsed != 0) {
            memcpy(newBuf, dataBuf, dataBufUsed);
        }
        if (dataBuf != 0) {
            free(dataBuf);
        }
        dataBuf = newBuf;
    }

    // Grow var table if necessary
    if (varCount == varTableCapacity) {
        int newTableCap = varTableCapacity * 2 + 2;
        varTableCapacity = newTableCap;
        void* newTable = malloc(newTableCap * 16);
        if (varCount != 0) {
            memcpy(newTable, varTable, varCount * 16);
        }
        if (varTable != 0) {
            free(varTable);
        }
        varTable = newTable;
    }

    // Add entry: [crc, elemSize, dataOffset, elemCount]
    table = (unsigned int*)varTable;
    table[varCount * 4 + 0] = p0;
    table[varCount * 4 + 2] = (unsigned int)dataBufUsed;
    table[varCount * 4 + 1] = (unsigned int)p1;
    table[varCount * 4 + 3] = (unsigned int)p2;
    varCount++;
    dataBufUsed += totalDataSize;
}

void gbNameVarBuf::SetVariant(unsigned int p0, void * p1) {
    unsigned int* table = (unsigned int*)varTable;
    for (int i = 0; i < varCount; i++) {
        if (table[i * 4] == p0) {
            unsigned int elemCount = table[i * 4 + 3];
            unsigned int elemSize = table[i * 4 + 1];
            unsigned int totalSize = elemCount * elemSize;
            memcpy((char*)dataBuf + table[i * 4 + 2], p1, totalSize);
            return;
        }
    }
}

void gbNameVarBuf::UnlockVariant() {
    locked = 0;
}

gbTimeCounter& gbTimeCounter::operator=(const gbTimeCounter& other) {
    if (this != &other) {
        startTime = other.startTime;
        freq = other.freq;
        elapsed = other.elapsed;
        timestamp = other.timestamp;
    }
    return *this;
}

double gbTimeCounter::Off() {
    if (*(double*)&startTime < 0.0) {
        return 0.0;
    }
    if (gbHasPerfCounter) {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        *(double*)&freq = ((double)counter.HighPart * 4294967296.0 + (double)(unsigned int)counter.LowPart) / gbTimeFreqDbl;
        return *(double*)&freq - *(double*)&startTime;
    } else {
        int t = timeGetTime();
        *(double*)&freq = (double)t * 0.001;
        return *(double*)&freq - *(double*)&startTime;
    }
}

void gbTimeCounter::On() {
    if (gbHasPerfCounter) {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        *(double*)&startTime = ((double)counter.HighPart * 4294967296.0 + (double)(unsigned int)counter.LowPart) / gbTimeFreqDbl;
    } else {
        int t = timeGetTime();
        *(double*)&startTime = (double)t * 1000.0;
    }
}


// ======== Random Number Generator ========

// Linear congruential generator seed - 0x1014adc4
static unsigned int g_gbRandSeed = 0;

// 0x10027620 (72B) - Generate random float in [minVal, maxVal]
// Uses LCG: seed = seed * 0x343FD + 0x269EC3
float gbRandFloat(float minVal, float maxVal) {
    g_gbRandSeed = g_gbRandSeed * 0x343FD + 0x269EC3;
    int randVal = (g_gbRandSeed >> 16) & 0x7FFF;
    return (maxVal - minVal) * (float)randVal * (1.0f / 32768.0f) + minVal;
}


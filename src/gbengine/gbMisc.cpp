/**
 * gbengine.dll - gbMisc
 * Utility functions and classes for gbengine
 */

#include "gbengine/gbMisc.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <mmsystem.h>

// CRC32 table
static unsigned int gbCrc32Table[256];

// Timing globals
static LARGE_INTEGER gbTimeFreq;
static LARGE_INTEGER gbTimeStart;
static TIMECAPS ptc;
static int gbTimerInited = 0;       // dword_1015D39C
static int gbHasQPC = 0;            // dword_1015D398
static double gbTimeFreqDbl = 0.0;  // dbl_1015D390

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

// 0x1002FB90 (206B)
int gbstricmp(const char* a1, const char* a2)
{
    char v13[2048];
    char v14[2048];

    char* v2 = v14;
    char v3 = *a1;
    if (v3) {
        int v4 = a1 - v14;
        do {
            char v5, v6;
            if (v3 < 'A' || (v5 = v2[v4], v5 > 'Z'))
                v6 = v2[v4];
            else
                v6 = v5 + 32;
            *v2 = v6;
            v3 = (v2++)[v4 + 1];
        } while (v3);
    }
    *v2 = 0;

    char* v7 = v13;
    char v8 = *a2;
    if (v8) {
        int v9 = a2 - v13;
        do {
            char v10, v11;
            if (v8 < 'A' || (v10 = v7[v9], v10 > 'Z'))
                v11 = v7[v9];
            else
                v11 = v10 + 32;
            *v7 = v11;
            v8 = (v7++)[v9 + 1];
        } while (v8);
    }
    *v7 = 0;

    return strcmp(v14, v13);
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

// 0x1002FD70 (283B)
void gbTimeCounterInit(void)
{
    LARGE_INTEGER PerformanceCount;
    LARGE_INTEGER Frequency;

    gbTimerInited = 1;
    if (!QueryPerformanceFrequency(&Frequency)) {
        if (gbHasQPC) {
            QueryPerformanceCounter(&PerformanceCount);
            double highPart = (double)PerformanceCount.HighPart;
            PerformanceCount.HighPart = 0;
            g_CurrentTime = (highPart * 4294967295.0 + (double)PerformanceCount.LowPart) / gbTimeFreqDbl;
            return;
        }
        g_CurrentTime = (double)clock() * 1000.0;
        return;
    }
    PerformanceCount.LowPart = Frequency.LowPart;
    PerformanceCount.HighPart = 0;
    gbHasQPC = 1;
    gbTimeFreqDbl = (double)Frequency.HighPart * 4294967295.0 + (double)PerformanceCount.QuadPart;
    timeGetDevCaps(&ptc, 8);
    if (gbHasQPC) {
        QueryPerformanceCounter(&PerformanceCount);
        Frequency.LowPart = PerformanceCount.LowPart;
        Frequency.HighPart = 0;
        g_CurrentTime = ((double)PerformanceCount.HighPart * 4294967295.0 + (double)Frequency.QuadPart)
                      / gbTimeFreqDbl;
    }
}

// 0x1002FE90 (100B)
double gbUpdateCurTime(void)
{
    double result;
    LARGE_INTEGER PerformanceCount;

    if (gbHasQPC) {
        QueryPerformanceCounter(&PerformanceCount);
        double HighPart = (double)PerformanceCount.HighPart;
        PerformanceCount.HighPart = 0;
        result = (HighPart * 4294967295.0 + (double)PerformanceCount.LowPart) / gbTimeFreqDbl;
    } else {
        result = (double)clock() * 1000.0;
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

#define MAX_PROFILE_ITEMS 50

// ProfileEntry: 284 bytes (71 DWORDs)
// Layout:
//   +0:   char isActive (+ 3 bytes padding)
//   +4:   int totalCalls
//   +8:   int nestingCount
//   +12:  char name[256]
//   +268: float startTime
//   +272: float selfTime
//   +276: float childTime
//   +280: int childCount
struct ProfileEntry {
    char isActive;          // +0
    char _pad[3];           // +1
    int totalCalls;         // +4
    int nestingCount;       // +8
    char name[256];         // +12
    float startTime;        // +268
    float selfTime;         // +272
    float childTime;        // +276
    int childCount;         // +280
};  // total = 284 bytes

// ProfileStat: 272 bytes (68 DWORDs)
// Layout:
//   +0:   char flag (+ padding)
//   +1:   char name[259]
//   +260: float avg
//   +264: float min
//   +268: float max
struct ProfileStat {
    char flag;              // +0
    char name[259];         // +1
    short _pad;             // +260 (actually part of float alignment)
    float avg;              // +260
    float min;              // +264
    float max;              // +268
};  // total = 272 bytes

// Use raw byte arrays to ensure exact layout matching
static char g_profileData[284 * MAX_PROFILE_ITEMS];       // ProfileEntry array
static char g_profileStatData[272 * MAX_PROFILE_ITEMS];   // ProfileStat array
static float g_profileStartTime;                           // flt_10164048
static float g_profileEndTime;                             // flt_1016404C

// Accessors for profile entries (284 bytes each)
#define PE_ACTIVE(i)      (*(char*)&g_profileData[284 * (i)])
#define PE_TOTALCALLS(i)  (*(int*)&g_profileData[284 * (i) + 4])
#define PE_NESTING(i)     (*(int*)&g_profileData[284 * (i) + 8])
#define PE_NAME(i)        ((char*)&g_profileData[284 * (i) + 12])
#define PE_STARTTIME(i)   (*(float*)&g_profileData[284 * (i) + 268])
#define PE_SELFTIME(i)    (*(float*)&g_profileData[284 * (i) + 272])
#define PE_CHILDTIME(i)   (*(float*)&g_profileData[284 * (i) + 276])
#define PE_CHILDCOUNT(i)  (*(int*)&g_profileData[284 * (i) + 280])

// Accessors for profile stats (272 bytes each)
#define PS_FLAG(i)        (*(char*)&g_profileStatData[272 * (i)])
#define PS_NAME(i)        ((char*)&g_profileStatData[272 * (i) + 1])
#define PS_AVG(i)         (*(float*)&g_profileStatData[272 * (i) + 260])
#define PS_MIN(i)         (*(float*)&g_profileStatData[272 * (i) + 264])
#define PS_MAX(i)         (*(float*)&g_profileStatData[272 * (i) + 268])

// ======== Message Box Functions ========

// 0x1002E820 (44B) - Display a message box with formatted text
int gbMessageBox(char *Format, ...)
{
    static char Buffer[1024];
    va_list va;

    va_start(va, Format);
    vsprintf(Buffer, Format, va);
    va_end(va);
    return MessageBoxA(0, Buffer, "Message", 0);
}

// 0x1002E850 (158B) - Display an error box with system error info
int gbErrorBox(UINT uType, char *Format, ...)
{
    DWORD LastError;
    CHAR Buffer[4];
    CHAR Text[4096];
    va_list va;

    va_start(va, Format);
    *(DWORD *)Buffer = 0;
    LastError = GetLastError();
    vsprintf(Text, Format, va);
    va_end(va);
    FormatMessageA(0x1300u, 0, LastError, 0x400u, Buffer, 0, 0);
    sprintf(Text, "%s\nSystem Error Code : %lu\nError Message : %s", Text, LastError, *(const char **)Buffer);
    LocalFree(*(HLOCAL *)Buffer);
    return MessageBoxA(0, Text, "Error", uType);
}

// 0x1002E8F0 (7B) - Return frame delta time
// This global is updated by the main loop and read by ProfileUpdateStats
float g_frameDeltaTime = 0.0f;

double gbGetFrameRate(void)
{
    return g_frameDeltaTime;
}

// 0x1002E900 (35B) - Get current time in seconds
double gbGetTime(void)
{
    return (double)timeGetTime() * 0.001;
}

static void ProfileUpdateStats(const char* name, float percent);
static void ProfileFormatOutput(char* buffer);

// 0x10031750 (46B)
void ProfileInit(void)
{
    char* p1 = g_profileData;
    char* p2 = g_profileStatData;
    do {
        *p1 = 0;
        *p2 = 0;
        p1 += 284;
        p2 += 272;
    } while ((int)p1 < (int)(g_profileStatData));
    g_profileStartTime = (float)gbGetTime();
}

// 0x10031780 (258B)
void ProfileBegin(char* name)
{
    unsigned int i = 0;
    const char* pName = PE_NAME(0);

    while (*(pName - 12) == 1) {
        if (!strcmp(pName, name)) {
            int nc = PE_NESTING(i) + 1;
            PE_NESTING(i) = nc;
            PE_TOTALCALLS(i) = PE_TOTALCALLS(i) + 1;
            PE_STARTTIME(i) = (float)gbGetTime();
            return;
        }
        pName += 284;
        ++i;
        if ((int)pName >= (int)PE_NAME(MAX_PROFILE_ITEMS))
            return;
    }
    if (i < 0x32) {
        strcpy(PE_NAME(i), name);
        PE_ACTIVE(i) = 1;
        PE_NESTING(i) = 1;
        PE_TOTALCALLS(i) = 1;
        PE_SELFTIME(i) = 0;
        PE_STARTTIME(i) = (float)gbGetTime();
        PE_CHILDTIME(i) = 0;
    }
}

// 0x10031890 (277B)
void ProfileEnd(char* name)
{
    int i = 0;
    const char* pName = PE_NAME(0);

    while (*(pName - 12) == 1) {
        if (!strcmp(pName, name)) {
            int deepIdx = -1;
            double endTime = gbGetTime();
            --PE_NESTING(i);
            int childCount;
            if (PE_ACTIVE(0) == 1) {
                childCount = 0;
                int j = 0;
                int deepOffs = -284;
                do {
                    if (PE_NESTING(j) > 0) {
                        ++childCount;
                        if (deepIdx < 0 || PE_STARTTIME(j) >= *(float*)((char*)&PE_STARTTIME(0) + deepOffs)) {
                            deepIdx = j;
                            deepOffs = (int)((char*)&PE_STARTTIME(j) - (char*)&PE_STARTTIME(0));
                        }
                    }
                    ++j;
                } while (PE_ACTIVE(j) == 1);
            } else {
                childCount = 0;
            }
            PE_CHILDCOUNT(i) = childCount;
            if (deepIdx >= 0)
                PE_CHILDTIME(deepIdx) = (float)endTime - PE_STARTTIME(i) + PE_CHILDTIME(deepIdx);
            PE_SELFTIME(i) = (float)endTime - PE_STARTTIME(i) + PE_SELFTIME(i);
            return;
        }
        pName += 284;
        ++i;
        if ((int)pName >= (int)PE_NAME(MAX_PROFILE_ITEMS))
            return;
    }
}

// 0x10031CA0 (402B)
static void ProfileUpdateStats(const char* name, float percent)
{
    unsigned int i = 0;
    double dt = gbGetFrameRate() * 0.80000001;
    if (dt > 1.0)
        dt = 1.0;
    const char* pName = PS_NAME(0);
    float oneMinusDt = (float)(1.0 - dt);

    while (*(pName - 1) == 1) {
        if (!strcmp(pName, name)) {
            float smoothed = (float)(dt * (double)percent);
            PS_AVG(i) = oneMinusDt * PS_AVG(i) + smoothed;
            if (percent >= PS_MIN(i))
                PS_MIN(i) = oneMinusDt * PS_MIN(i) + smoothed;
            else
                PS_MIN(i) = percent;
            if (PS_MIN(i) < 0.0f)
                PS_MIN(i) = 0.0f;
            if (percent <= PS_MAX(i))
                PS_MAX(i) = oneMinusDt * PS_MAX(i) + smoothed;
            else
                PS_MAX(i) = percent;
            return;
        }
        pName += 272;
        ++i;
        if ((int)pName >= (int)((char*)&g_profileStartTime + 1))
            return;
    }
    if (i < 0x32) {
        strcpy(PS_NAME(i), name);
        PS_FLAG(i) = 1;
        PS_MAX(i) = percent;
        PS_MIN(i) = percent;
        PS_AVG(i) = percent;
    }
}

// 0x10031A00 (661B)
static void ProfileFormatOutput(char* buffer)
{
    unsigned int i;
    char nameBuf[256];
    char indentBuf[256];
    char avgStr[16];
    char minStr[16];
    char maxStr[16];
    char countStr[16];
    char lineFormat[256];

    g_profileEndTime = (float)gbGetTime();
    *buffer = 0;
    sprintf(&buffer[strlen(buffer)], " Ave :  Min :  Max : Cnt : Profile\n");
    sprintf(&buffer[strlen(buffer)], "--------------------------------------------\n");

    i = 0;
    while (i < MAX_PROFILE_ITEMS && PE_ACTIVE(i) == 1) {
        float percent = (PE_SELFTIME(i) - PE_CHILDTIME(i)) / (g_profileEndTime - g_profileStartTime) * 100.0f;
        ProfileUpdateStats(PE_NAME(i), percent);

        // Look up stats for this entry
        float avg = 0.0f, min = 0.0f, max = 0.0f;
        unsigned int si = 0;
        const char* sName = PS_NAME(0);
        while (*(sName - 1) == 1) {
            if (!strcmp(sName, PE_NAME(i))) {
                avg = PS_AVG(si);
                min = PS_MIN(si);
                max = PS_MAX(si);
                break;
            }
            sName += 272;
            ++si;
            if ((int)sName >= (int)((char*)&g_profileStartTime + 1)) {
                avg = 0.0f; min = 0.0f; max = 0.0f;
                break;
            }
        }

        sprintf(avgStr, "%3.1f", (double)avg);
        sprintf(minStr, "%3.1f", (double)min);
        sprintf(maxStr, "%3.1f", (double)max);
        sprintf(countStr, "%3d", PE_CHILDCOUNT(i));

        strcpy(nameBuf, PE_NAME(i));
        unsigned int indent = 0;
        if (PE_CHILDCOUNT(i)) {
            do {
                sprintf(indentBuf, "   %s", nameBuf);
                strcpy(nameBuf, indentBuf);
                ++indent;
            } while (indent < (unsigned int)PE_CHILDCOUNT(i));
        }

        sprintf(lineFormat, "%5s : %5s : %5s : %3s : %s\n", avgStr, minStr, maxStr, countStr, nameBuf);
        sprintf(&buffer[strlen(buffer)], lineFormat);
        ++i;
    }

    // Reset profile entries
    char* p = g_profileData;
    do {
        *p = 0;
        p += 284;
    } while ((int)p < (int)g_profileStatData);
    g_profileStartTime = (float)gbGetTime();
}

// 0x100319B0 (79B)
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

void gbPixelFormat::Convert(unsigned char* src, gbPixelFormat* srcFmt, unsigned char* dst, int numPixels) {
    if (Pal)
        memcpy(Pal, srcFmt->Pal, 4 * (1 << Bpp));

    int dstHasPal = (int)Pal;
    gbColorQuad* srcPal = srcFmt->Pal;
    int srcBitOffset = 0;
    int dstBitOffset = 0;

    if (dstHasPal) {
        if (!srcPal)
            goto do_memcpy;
        goto indexed_to_direct;
    }

    if (srcPal) {
indexed_to_direct:
        if (!dstHasPal) {
            int rShift = (int)r_shift;
            int bShift = (int)b_shift;
            int gShift = (int)g_shift;
            unsigned char* pDst = dst;
            int aShift = (int)a_shift;
            int savedRShift = rShift;

            if (numPixels > 0) {
                int remaining = numPixels;
                while (1) {
                    unsigned char* palEntry = (unsigned char*)srcFmt->Pal + 4 * *src;
                    unsigned int palB = palEntry[2];
                    unsigned int palG = palEntry[1];
                    unsigned int palR = *palEntry;

                    unsigned int shiftedR = rShift < 0 ? palB >> (unsigned char)(-(char)rShift) : palB << rShift;
                    unsigned int shiftedG = gShift < 0 ? palG >> (unsigned char)(-(char)gShift) : palG << gShift;
                    unsigned int shiftedB = bShift < 0 ? palR >> (unsigned char)(-(char)bShift) : palR << bShift;
                    unsigned int shiftedA = aShift < 0 ? 0xFFFFFFFF >> (unsigned char)(-(char)aShift) : (unsigned int)-1 << aShift;

                    int combined = shiftedG & g_mask | shiftedR & r_mask;
                    int bPart = shiftedB & b_mask;
                    int dstBpp = Bpp;
                    int pixel = a_mask & shiftedA | bPart | combined;

                    switch (dstBpp) {
                    case 16:
                        *(unsigned short*)pDst = (unsigned short)pixel;
                        break;
                    case 24:
                        *(unsigned short*)pDst = (unsigned short)pixel;
                        pDst[2] = (unsigned char)(pixel >> 16);
                        break;
                    case 32:
                        *(unsigned int*)pDst = pixel;
                        break;
                    }

                    dstBitOffset += Bpp;
                    ++src;
                    pDst = &dst[dstBitOffset / 8];
                    if (!--remaining)
                        break;
                    rShift = savedRShift;
                }
            }
            return;
        }
do_memcpy:
        memcpy(dst, src, (unsigned int)numPixels);
        return;
    }

    int dstBpp = Bpp;
    int srcBpp = (int)srcFmt->Bpp;

    if (dstBpp == srcBpp
        && r_mask == srcFmt->r_mask
        && g_mask == srcFmt->g_mask
        && b_mask == srcFmt->b_mask
        && a_mask == srcFmt->a_mask) {
        unsigned int byteCount = numPixels * (dstBpp / 8);
        memcpy(dst, src, byteCount);
        return;
    }

    int rShiftDiff = (int)r_shift - (int)srcFmt->r_shift;
    int bShiftDiff = (int)b_shift - (int)srcFmt->b_shift;
    unsigned char* pDst = dst;
    int gShiftDiff = (int)g_shift - (int)srcFmt->g_shift;
    int aShiftDiff = (int)a_shift - (int)srcFmt->a_shift;
    unsigned char* pSrc = src;

    if (numPixels > 0) {
        int remaining = numPixels;
        while (1) {
            int srcPixel = 0;
            switch (srcBpp) {
            case 16:
                srcPixel = *(unsigned short*)pSrc;
                break;
            case 24:
                srcPixel = *pSrc | (*(unsigned short*)(pSrc + 1) << 8);
                break;
            case 32:
                srcPixel = *(unsigned int*)pSrc;
                break;
            }

            unsigned int srcR = srcFmt->r_mask;
            unsigned int srcG = srcPixel & srcFmt->g_mask;
            unsigned int srcB = srcFmt->b_mask;
            unsigned int srcA = srcFmt->a_mask;
            unsigned int maskedR = srcPixel & srcR;
            unsigned int maskedB = srcB & srcPixel;
            unsigned int maskedA = srcA ? srcPixel & srcA : (unsigned int)-1;

            unsigned int shiftedR = rShiftDiff < 0 ? maskedR >> (unsigned char)(-(char)rShiftDiff) : maskedR << rShiftDiff;
            unsigned int shiftedG = gShiftDiff < 0 ? srcG >> (unsigned char)(-(char)gShiftDiff) : srcG << gShiftDiff;
            unsigned int shiftedB = bShiftDiff < 0 ? maskedB >> (unsigned char)(-(char)bShiftDiff) : maskedB << bShiftDiff;
            unsigned int shiftedA = aShiftDiff < 0 ? maskedA >> (unsigned char)(-(char)aShiftDiff) : maskedA << aShiftDiff;

            int dstPixel = a_mask & shiftedA
                        | shiftedB & b_mask
                        | shiftedG & g_mask
                        | shiftedR & r_mask;
            int outBpp = Bpp;

            switch (outBpp) {
            case 16:
                *(unsigned short*)pDst = (unsigned short)dstPixel;
                break;
            case 24:
                *(unsigned short*)pDst = (unsigned short)dstPixel;
                pDst[2] = (unsigned char)(dstPixel >> 16);
                break;
            case 32:
                *(unsigned int*)pDst = dstPixel;
                break;
            }

            srcBpp = (int)srcFmt->Bpp;
            srcBitOffset += srcBpp;
            dstBitOffset += Bpp;
            pSrc = &src[srcBitOffset / 8];
            pDst = &dst[dstBitOffset / 8];
            if (!--remaining)
                break;
        }
    }
}

gbUIRect& gbUIRect::operator=(const gbUIRect& other) {
    memcpy(this, &other, 0x18);
    return *this;
}

void gbUIRect::Init(char* textureName, float inLeft, float inTop, float inRight, float inBottom, gbGfxManager* gfx) {
    m_pGfx = gfx;
    m_pTexture = gfx->NewTexture(textureName);
    m_pTexture->LoadTexture(1);
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
            memcpy(p1, (char*)dataBuf + table[i * 4 + 2], table[i * 4 + 1] * table[i * 4 + 3]);
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
            memcpy((char*)dataBuf + table[i * 4 + 2], p1, table[i * 4 + 1] * table[i * 4 + 3]);
            return;
        }
    }
}

void gbNameVarBuf::UnlockVariant() {
    locked = 0;
}

gbTimeCounter& gbTimeCounter::operator=(const gbTimeCounter& other) {
    startTime = other.startTime;
    freq = other.freq;
    return *this;
}

double gbTimeCounter::Off() {
    double HighPart;
    LARGE_INTEGER PerformanceCount;

    if (*(double*)&startTime < 0.0) {
        return 0.0;
    }
    if (gbHasQPC) {
        QueryPerformanceCounter(&PerformanceCount);
        HighPart = (double)PerformanceCount.HighPart;
        PerformanceCount.HighPart = 0;
        *(double*)&freq = (HighPart * 4294967295.0 + (double)PerformanceCount.LowPart) / gbTimeFreqDbl;
    } else {
        PerformanceCount.LowPart = clock();
        *(double*)&freq = (double)(int)PerformanceCount.LowPart * 0.001;
    }
    return *(double*)&freq - *(double*)&startTime;
}

void gbTimeCounter::On() {
    if (gbHasQPC) {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        double highPart = (double)counter.HighPart;
        counter.HighPart = 0;
        *(double*)&startTime = (highPart * 4294967295.0 + (double)counter.LowPart) / gbTimeFreqDbl;
    } else {
        int t = clock();
        *(double*)&startTime = (double)t * 1000.0;
    }
}


// ======== Random Number Generator ========

// Linear congruential generator seed - 0x1014adc4
static int g_gbRandSeed = 0;

// 0x10027620 (72B) - Generate random float in [minVal, maxVal]
// Uses LCG: seed = seed * 0x343FD + 0x269EC3
float gbRandFloat(float minVal, float maxVal) {
    g_gbRandSeed = g_gbRandSeed * 0x343FD + 0x269EC3;
    int randVal = (g_gbRandSeed >> 16) & 0x7FFF;
    return (maxVal - minVal) * (float)randVal * (1.0f / 32768.0f) + minVal;
}


// ======== gbSpline ========

// gbSpline structure
// Layout: pPoints(4) + pDistances(4) + numPoints(4) + matrix(64) = 76 bytes
struct gbSpline {
    gbVec3D* pPoints;      // +0x00: array of control points
    float* pDistances;     // +0x04: array of segment lengths (numPoints-1 entries)
    int numPoints;         // +0x08: number of control points
    gbMatrix4 matrix;      // +0x0C: transformation matrix
};

// 0x10029AB0 (36B)
void gbSpline_Constructor(gbSpline* spline) {
    spline->pPoints = NULL;
    spline->pDistances = NULL;
    spline->numPoints = 0;
    spline->trans.LoadIdentity();
}

// 0x10029B20 (452B)
int gbSpline_LoadFromFile(gbSpline* spline, const char* filename) {
    gbVec3D tempVec;
    tempVec.x = 0.0f;
    tempVec.y = 0.0f;
    tempVec.z = 0.0f;

    char magic[4];
    magic[3] = 0;

    gbVFile* file = g_pVFileSys->OpenFile(filename, 0x201);
    if (!file)
        return 0;

    g_pVFileSys->Read(magic, 4, file);
    if (strcmp(magic, "CSF") != 0) {
        g_pVFileSys->CloseFile(file);
        return 0;
    }

    int dummy;
    g_pVFileSys->Read(&dummy, 4, file);
    g_pVFileSys->Read(&spline->numPoints, 4, file);

    if (spline->pPoints)
        delete[] (char*)spline->pPoints;

    int numPts = spline->numPoints;
    gbVec3D* points = (gbVec3D*)operator new(12 * numPts);
    if (points) {
        for (int i = 0; i < numPts; i++) {
            points[i].x = 0.0f;
            points[i].y = 0.0f;
            points[i].z = 0.0f;
        }
    }

    spline->pPoints = points;
    g_pVFileSys->Read(points, 12 * spline->numPoints, file);
    g_pVFileSys->CloseFile(file);

    if (spline->pDistances)
        delete[] (char*)spline->pDistances;

    float* dists = (float*)operator new(4 * (spline->numPoints - 1));
    spline->pDistances = dists;

    int count = spline->numPoints - 1;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            gbVec3D* pts = spline->pPoints;
            gbVec3D diff;
            diff.x = pts[i + 1].x - pts[i].x;
            diff.y = pts[i + 1].y - pts[i].y;
            diff.z = pts[i + 1].z - pts[i].z;
            dists[i] = diff.Length();
        }
    }

    spline->trans.LoadIdentity();
    return 1;
}

#include "gbengine/gbengine_types.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbVisNode.h"
#include "gbengine/gbVFileSystem.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// gbRealWorldTime structure definition (0x20 bytes)
struct gbRealWorldTime {
    unsigned int year;          // +0x00
    unsigned int month;         // +0x04
    unsigned int dayOfWeek;     // +0x08
    unsigned int day;           // +0x0C
    unsigned int hour;          // +0x10
    unsigned int minute;        // +0x14
    unsigned int second;        // +0x18
    unsigned int milliseconds;  // +0x1C
};

// Extract directory from path
char* gbVfgetdir(const char* path, char* buf, int size) {
    if (!path || !buf || size <= 0) {
        return NULL;
    }

    // Find last slash or backslash
    const char* lastSlash = NULL;
    for (const char* p = path; *p; p++) {
        if (*p == '\\' || *p == '/') {
            lastSlash = p;
        }
    }

    if (!lastSlash) {
        // No directory separator found
        buf[0] = '\0';
        return buf;
    }

    // Copy directory part (including trailing slash)
    int len = (int)(lastSlash - path + 1);
    if (len >= size) {
        len = size - 1;
    }

    strncpy(buf, path, len);
    buf[len] = '\0';
    return buf;
}

// Extract filename from path
char* gbVfgetname(const char* path, char* buf, int size) {
    if (!path || !buf || size <= 0) {
        return NULL;
    }

    // Find last slash or backslash
    const char* lastSlash = NULL;
    for (const char* p = path; *p; p++) {
        if (*p == '\\' || *p == '/') {
            lastSlash = p;
        }
    }

    // Copy filename part (after last slash)
    const char* filename = lastSlash ? (lastSlash + 1) : path;
    strncpy(buf, filename, size - 1);
    buf[size - 1] = '\0';
    return buf;
}

// Create graphics manager (UNCERTAIN implementation)
gbGfxManager* gbCreateGraphManager(gbGfxDriverInfo* info) {
    /* UNCERTAIN */
    // This should create and return a gbGfxManager_D3D instance
    // The actual implementation requires constructor details
    return NULL;
}

// Load light file (UNCERTAIN implementation)
gbVisNode* gbLoadLightFile(const char* filename) {
    /* UNCERTAIN */
    // This should load a light definition file and create a light node
    // Format and structure are not fully known
    return NULL;
}

// Convert half-width to full-width characters (for CJK text)
int gbConvertToSBC(unsigned char* src, int srcLen, unsigned char* dst, int dstLen) {
    if (!src || !dst || srcLen <= 0 || dstLen <= 0) {
        return 0;
    }

    int outLen = 0;
    for (int i = 0; i < srcLen && outLen < dstLen - 1; i++) {
        unsigned char ch = src[i];

        // Handle multi-byte characters (pass through)
        if (ch >= 0x80) {
            if (i + 1 < srcLen && outLen < dstLen - 2) {
                dst[outLen++] = ch;
                dst[outLen++] = src[++i];
            }
        }
        // Convert ASCII space to full-width space (0xA1A1 in GB2312)
        else if (ch == ' ') {
            if (outLen < dstLen - 2) {
                dst[outLen++] = 0xA1;
                dst[outLen++] = 0xA1;
            }
        }
        // Convert ASCII printable to full-width (0xA3 prefix in GB2312)
        else if (ch >= 0x21 && ch <= 0x7E) {
            if (outLen < dstLen - 2) {
                dst[outLen++] = 0xA3;
                dst[outLen++] = ch + 0x80;
            }
        }
        // Other ASCII characters pass through
        else {
            dst[outLen++] = ch;
        }
    }

    dst[outLen] = '\0';
    return outLen;
}

// Execute external program
int gbExecProgram(const char* cmdLine) {
    if (!cmdLine) {
        return 0;
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    memset(&pi, 0, sizeof(pi));

    // Create a modifiable copy of the command line
    char cmdBuf[1024];
    strncpy(cmdBuf, cmdLine, sizeof(cmdBuf) - 1);
    cmdBuf[sizeof(cmdBuf) - 1] = '\0';

    // Create process
    BOOL result = CreateProcessA(
        NULL,           // Application name
        cmdBuf,         // Command line
        NULL,           // Process security attributes
        NULL,           // Thread security attributes
        FALSE,          // Inherit handles
        0,              // Creation flags
        NULL,           // Environment
        NULL,           // Current directory
        &si,            // Startup info
        &pi             // Process information
    );

    if (result) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return 1;
    }

    return 0;
}

// Moller-Trumbore ray-triangle intersection algorithm
int gbIntersectTriangle(gbVec3D* origin, gbVec3D* dir, gbVec3D* v0, gbVec3D* v1, gbVec3D* v2, gbVec3D* hitPoint) {
    if (!origin || !dir || !v0 || !v1 || !v2) {
        return 0;
    }

    const float EPSILON = 0.0000001f;

    // Edge vectors
    gbVec3D edge1, edge2;
    edge1.x = v1->x - v0->x;
    edge1.y = v1->y - v0->y;
    edge1.z = v1->z - v0->z;

    edge2.x = v2->x - v0->x;
    edge2.y = v2->y - v0->y;
    edge2.z = v2->z - v0->z;

    // Begin calculating determinant - also used to calculate U parameter
    gbVec3D pvec;
    pvec.x = dir->y * edge2.z - dir->z * edge2.y;
    pvec.y = dir->z * edge2.x - dir->x * edge2.z;
    pvec.z = dir->x * edge2.y - dir->y * edge2.x;

    // If determinant is near zero, ray lies in plane of triangle
    float det = edge1.x * pvec.x + edge1.y * pvec.y + edge1.z * pvec.z;

    if (det > -EPSILON && det < EPSILON) {
        return 0;
    }

    float inv_det = 1.0f / det;

    // Calculate distance from v0 to ray origin
    gbVec3D tvec;
    tvec.x = origin->x - v0->x;
    tvec.y = origin->y - v0->y;
    tvec.z = origin->z - v0->z;

    // Calculate U parameter and test bounds
    float u = (tvec.x * pvec.x + tvec.y * pvec.y + tvec.z * pvec.z) * inv_det;
    if (u < 0.0f || u > 1.0f) {
        return 0;
    }

    // Prepare to test V parameter
    gbVec3D qvec;
    qvec.x = tvec.y * edge1.z - tvec.z * edge1.y;
    qvec.y = tvec.z * edge1.x - tvec.x * edge1.z;
    qvec.z = tvec.x * edge1.y - tvec.y * edge1.x;

    // Calculate V parameter and test bounds
    float v = (dir->x * qvec.x + dir->y * qvec.y + dir->z * qvec.z) * inv_det;
    if (v < 0.0f || u + v > 1.0f) {
        return 0;
    }

    // Calculate t, ray intersects triangle
    float t = (edge2.x * qvec.x + edge2.y * qvec.y + edge2.z * qvec.z) * inv_det;

    if (t > EPSILON && hitPoint) {
        // Calculate hit point
        hitPoint->x = origin->x + dir->x * t;
        hitPoint->y = origin->y + dir->y * t;
        hitPoint->z = origin->z + dir->z * t;
    }

    return (t > EPSILON) ? 1 : 0;
}

// Enable/disable system hotkeys (Alt+Tab, Win key, etc.)
void gbEnableSystemKeys(HINSTANCE hInst, int enable) {
    // This typically uses RegisterHotKey/UnregisterHotKey or
    // low-level keyboard hooks to block system keys
    // For now, leave as stub since it's window manager specific
    /* UNCERTAIN */
}

// Get current display mode
void gbGetCurDispMode(int& width, int& height, int& bpp) {
    DEVMODEA dm;
    memset(&dm, 0, sizeof(dm));
    dm.dmSize = sizeof(dm);

    if (EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
        width = (int)dm.dmPelsWidth;
        height = (int)dm.dmPelsHeight;
        bpp = (int)dm.dmBitsPerPel;
    } else {
        // Fallback values
        width = 800;
        height = 600;
        bpp = 32;
    }
}

// Get real world time
void gbGetRealWorldTime(gbRealWorldTime* time) {
    if (!time) {
        return;
    }

    SYSTEMTIME st;
    GetLocalTime(&st);

    time->year = (unsigned int)st.wYear;
    time->month = (unsigned int)st.wMonth;
    time->dayOfWeek = (unsigned int)st.wDayOfWeek;
    time->day = (unsigned int)st.wDay;
    time->hour = (unsigned int)st.wHour;
    time->minute = (unsigned int)st.wMinute;
    time->second = (unsigned int)st.wSecond;
    time->milliseconds = (unsigned int)st.wMilliseconds;
}

// Display mode management globals
struct gbDispMode {
    int width;
    int height;
    int bpp;
    int freq;
    int reserved;
};

static int g_dispModeCount = 0;
static gbDispMode g_dispModes[128];
static int g_dispStackDepth = 0;
static gbDispMode* g_dispStack = NULL;
static gbDispMode g_curDispMode = {0, 0, 0, 0, 0};

extern void gbPopErrorBox(char* fmt, ...);

void gbInitDispSetting(void)
{
    DEVMODEA DevMode;
    BOOL result;
    DWORD iModeNum;
    FILE* fp;

    result = EnumDisplaySettingsA(NULL, 0, &DevMode);
    fp = fopen("disp_ogl.txt", "wt");
    iModeNum = 0;
    while (result) {
        gbDispMode* pMode = &g_dispModes[g_dispModeCount];
        pMode->width = DevMode.dmPelsWidth;
        pMode->height = DevMode.dmPelsHeight;
        pMode->bpp = DevMode.dmBitsPerPel;
        pMode->freq = DevMode.dmDisplayFrequency;
        if (fp) {
            fprintf(fp, "w=%d,h=%d,bpp=%d,freq=%d\n",
                pMode->width, pMode->height, pMode->bpp, DevMode.dmDisplayFrequency);
        }
        result = EnumDisplaySettingsA(NULL, iModeNum, &DevMode);
        iModeNum++;
    }
    if (fp) {
        fclose(fp);
    }
}

int gbChangeDispMode(int width, int height, int bpp)
{
    DEVMODEA DevMode;
    DWORD curFreq;
    DWORD firstMatch;
    DWORD iMode;
    LONG result;
    char buf[256];

    firstMatch = 0;
    g_curDispMode.width = width;
    g_curDispMode.height = height;
    g_curDispMode.bpp = bpp;

    EnumDisplaySettingsA(NULL, 0xFFFFFFFF, &DevMode);
    curFreq = DevMode.dmDisplayFrequency;

    iMode = 0;
    while (EnumDisplaySettingsA(NULL, iMode, &DevMode)) {
        if (DevMode.dmBitsPerPel == (DWORD)bpp
            && DevMode.dmPelsWidth == (DWORD)width
            && DevMode.dmPelsHeight == (DWORD)height
            && DevMode.dmDisplayFrequency == curFreq) {
            if (!ChangeDisplaySettingsA(&DevMode, CDS_FULLSCREEN))
                return 1;
            if (!firstMatch)
                firstMatch = iMode;
        }
        iMode++;
    }

    iMode = 0;
    while (EnumDisplaySettingsA(NULL, iMode, &DevMode)) {
        if (DevMode.dmBitsPerPel == (DWORD)bpp
            && DevMode.dmPelsWidth == (DWORD)width
            && DevMode.dmPelsHeight == (DWORD)height) {
            if (!ChangeDisplaySettingsA(&DevMode, CDS_FULLSCREEN))
                return 1;
            if (!firstMatch)
                firstMatch = iMode;
        }
        iMode++;
    }

    EnumDisplaySettingsA(NULL, firstMatch, &DevMode);
    DevMode.dmBitsPerPel = bpp;
    DevMode.dmPelsWidth = width;
    DevMode.dmPelsHeight = height;
    DevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

    if (ChangeDisplaySettingsA(&DevMode, CDS_FULLSCREEN)) {
        DevMode.dmFields = DM_BITSPERPEL;
        result = ChangeDisplaySettingsA(&DevMode, CDS_FULLSCREEN);
        if (!result) {
            DevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
            result = ChangeDisplaySettingsA(&DevMode, CDS_FULLSCREEN);
            if (result) {
                ChangeDisplaySettingsA(NULL, 0);
                goto error;
            }
            return 1;
        }
error:
        if (result == DISP_CHANGE_BADMODE) {
            sprintf(buf, "The video mode %ldx%ldx%ld-bit color is not available\n", (long)width, (long)height, (long)bpp);
        } else if (result == DISP_CHANGE_FAILED) {
            sprintf(buf, "Hardware failed to change to %ldx%ldx%ld-bit color\n", (long)width, (long)height, (long)bpp);
        } else if (result == DISP_CHANGE_RESTART) {
            sprintf(buf, "You must change your video mode to %ldx%ldx%ld-bit color and then restart\n", (long)width, (long)height, (long)bpp);
        } else {
            sprintf(buf, "Failed to change to %ldx%ldx%ld-bit color mode\n", (long)width, (long)height, (long)bpp);
        }
        gbPopErrorBox(buf);
        return 0;
    }
    return 1;
}

void gbRestoreDispMode(void)
{
    ChangeDisplaySettingsA(NULL, 0);
}

void gbPushDispMode(void)
{
    g_dispStack[g_dispStackDepth] = g_curDispMode;
    g_dispStackDepth++;
}

void gbPopDispMode(void)
{
    if (g_dispStackDepth != 0) {
        g_dispStackDepth--;
        gbDispMode mode = g_dispStack[g_dispStackDepth];
        if (mode.width == 0) {
            ChangeDisplaySettingsA(NULL, 0);
            return;
        }
        gbChangeDispMode(mode.width, mode.height, mode.bpp);
    }
}

int gbGetOSUserName(char* buf, int bufSize)
{
    DWORD size = bufSize;
    GetUserNameA(buf, &size);
    return (int)size;
}

int gbGetCPU_MHZ(void)
{
    LARGE_INTEGER freq, start, end;
    unsigned __int64 tscStart, tscEnd;
    __int64 cycles, elapsed;
    int rawMHz;
    int v1, v2;
    int tmp;

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    __asm { rdtsc }
    __asm { mov dword ptr [tscStart], eax }
    __asm { mov dword ptr [tscStart+4], edx }

    int count = 2500000;
    do { --count; } while (count);

    QueryPerformanceCounter(&end);

    __asm { rdtsc }
    __asm { mov dword ptr [tscEnd], eax }
    __asm { mov dword ptr [tscEnd+4], edx }

    cycles = tscEnd - tscStart;
    elapsed = end.QuadPart - start.QuadPart;
    rawMHz = (int)(cycles * freq.QuadPart / elapsed / 1000000);

    // Round to nearest multiple of 33.3MHz
    tmp = (int)(rawMHz * 0.03000003000003);
    if (rawMHz * 0.03000003000003 - tmp >= 0.5)
        tmp++;
    v1 = (int)(tmp * 33.3333);
    if (tmp * 33.3333 - v1 < 0.5)
        v1 = (int)(tmp * 33.3333);
    else
        v1 = v1 + 1;

    // Round to nearest multiple of 25MHz
    tmp = (int)(rawMHz * 0.04);
    if (rawMHz * 0.04 - tmp >= 0.5)
        tmp++;
    v2 = (int)(tmp * 25.0);
    if (tmp * 25.0 - v2 >= 0.5)
        v2++;

    if (abs(v1 - rawMHz) >= abs(v2 - rawMHz))
        return v2;
    return v1;
}

int gbGetINIValue(char* str, char* key, char* value)
{
    char* p = strchr(str, '[');
    if (!p)
        return 0;

    char ch = *(p + 1);
    int i = 0;
    p++;
    while (ch != ']') {
        key[i] = ch;
        i++;
        ch = *(p + 1);
        p++;
    }
    key[i] = '\0';

    p = strchr(p, '[');
    char* q = p + 1;
    i = 0;
    ch = *q;
    if (ch != ']') {
        int off = (int)((char*)value - (char*)q);
        do {
            *(q + off) = ch;
            ch = *(q + 1);
            i++;
            q++;
        } while (ch != ']');
    }
    value[i] = '\0';
    return 1;
}

// Compute vertex stride from D3D Flexible Vertex Format flags
int gbComputeFVFStride(unsigned int fvf)
{
    int stride = 0;

    // Position: XYZ(12), XYZRHW(16), XYZB1-5(16-32), XYZW(16)
    switch (fvf & 0x000E) {
        case 0x0002: stride = 12; break; // D3DFVF_XYZ
        case 0x0004: stride = 16; break; // D3DFVF_XYZRHW
        case 0x0006: stride = 16; break; // D3DFVF_XYZB1
        case 0x0008: stride = 20; break; // D3DFVF_XYZB2
        case 0x000A: stride = 24; break; // D3DFVF_XYZB3
        case 0x000C: stride = 28; break; // D3DFVF_XYZB4
        case 0x000E: stride = 32; break; // D3DFVF_XYZB5
    }

    // Normal
    if (fvf & 0x0010) stride += 12; // D3DFVF_NORMAL

    // Point size
    if (fvf & 0x0020) stride += 4; // D3DFVF_PSIZE

    // Diffuse color
    if (fvf & 0x0040) stride += 4; // D3DFVF_DIFFUSE

    // Specular color
    if (fvf & 0x0080) stride += 4; // D3DFVF_SPECULAR

    // Texture coordinates
    int numTexCoords = (fvf & 0x0F00) >> 8;
    unsigned int texCoordSize = fvf >> 16;

    for (int i = 0; i < numTexCoords; i++) {
        int coordSize = (texCoordSize >> (i * 2)) & 3;
        switch (coordSize) {
            case 0: stride += 8; break;   // D3DFVF_TEXTUREFORMAT2 (2 floats)
            case 1: stride += 12; break;  // D3DFVF_TEXTUREFORMAT3 (3 floats)
            case 2: stride += 16; break;  // D3DFVF_TEXTUREFORMAT4 (4 floats)
            case 3: stride += 4; break;   // D3DFVF_TEXTUREFORMAT1 (1 float)
        }
    }

    return stride;
}

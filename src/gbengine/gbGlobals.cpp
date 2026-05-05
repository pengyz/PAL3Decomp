#include "pal3.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbVisNode.h"
#include "gbengine/gbVFileSystem.h"
#include <windows.h>
#include <string.h>
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

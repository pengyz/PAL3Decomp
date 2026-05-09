#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_internal.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbVisNode.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbChain.h"
#include "gbengine/gbTexture.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

static int g_CurDispWidth;
static int g_CurDispHeight;
static int g_CurDispBpp;

// Global Vec3D used by audio/sound system
// Address: 0x1012B990 in original binary
static gbVec3D g_globalVec3D;

// 0x10002A50 (31B) - ResetGlobalVec3D
void ResetGlobalVec3D() {
    g_globalVec3D.x = 0.0f;
    g_globalVec3D.y = 0.0f;
    g_globalVec3D.z = 0.0f;
}

// Global texture format flag (referenced from gbTexture.cpp)
// Address: 0x10140DB0 in original binary
int dword_10140DB0 = 0;

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

// 0x10030F00
char* gbVfgetdir(const char* path, char* buf, int size) {
    char* p1;
    char* p2;
    strncpy(buf, path, size);
    p1 = strrchr(buf, '/');
    p2 = strrchr(buf, '\\');
    if (p2 > p1)
        p1 = p2;
    if (!p1)
        *buf = 0;
    else
        p1[1] = 0;
    return buf;
}

// 0x10030F50
char* gbVfgetname(const char* path, char* buf, int size) {
    const char* src;
    char* p1;
    char* p2;
    src = path;
    p1 = strrchr(path, '/');
    p2 = strrchr(path, '\\');
    if (p2 > p1)
        p1 = p2;
    if (p1)
        src = p1 + 1;
    return strcpy(buf, src);
}

// Create graphics manager - 0x1001E0C0 (145B)
// Factory function: allocates gbGfxManager_D3D and calls its Init method
// Returns NULL if Init fails (result param set to 0)
gbGfxManager* gbCreateGraphManager(gbGfxDriverInfo* info) {
    int result = 0;
    gbGfxManager* pMgr = NULL;

    if (info->type != 1 && info->type == 2) {
        // D3D9 driver type
        gbGfxManager_D3D* pD3DMgr = new gbGfxManager_D3D();
        if (pD3DMgr) {
            pMgr = pD3DMgr->InitD3D(&result, info);
        } else {
            pMgr = NULL;
        }
    }

    if (result == 0) {
        if (pMgr) {
            delete pMgr;
        }
        pMgr = NULL;
    }

    return pMgr;
}

// Load light file - 0x100135A0 (735B)
// Reads a .lgt file and constructs a tree of gbVolModNode + gbLightObj
gbVisNode* gbLoadLightFile(const char* filename) {
    gbVFile* fp = g_pVFileSys->OpenFile(filename, 0x201);

    int lightCount;
    g_pVFileSys->Read(&lightCount, 4, fp);

    // Create root container node
    gbVisNode* root = new gbVisNode();

    for (int i = 0; i < lightCount; i++) {
        // Create volume modifier node (holds transform + light)
        gbVolModNode* volNode = new gbVolModNode();

        // Read local transform matrix (64 bytes)
        g_pVFileSys->Read(&volNode->localMatrix, 0x40, fp);

        // Ensure localMatrix m[3][3] = 1.0f (homogeneous coordinate w=1)
        volNode->localMatrix.m[3][3] = 1.0f;

        // Create light object
        gbLightObj* light = new gbLightObj();

        // Read light parameters from file (matching gbVolumeModifier field layout)
        g_pVFileSys->Read(&light->lightType, 4, fp);
        g_pVFileSys->Read(&light->diffuse, 0x10, fp);
        g_pVFileSys->Read(&light->ambient, 0x10, fp);
        g_pVFileSys->Read(&light->enabled, 4, fp);
        g_pVFileSys->Read(&light->_field30, 4, fp);
        g_pVFileSys->Read(&light->_field34, 4, fp);
        g_pVFileSys->Read(&light->_field38, 4, fp);
        g_pVFileSys->Read(&light->_field3C, 4, fp);
        g_pVFileSys->Read(&light->range, 4, fp);
        g_pVFileSys->Read(&light->_field44, 4, fp);
        g_pVFileSys->Read(&light->_field48, 4, fp);
        g_pVFileSys->Read(&light->attenuation0, 4, fp);
        g_pVFileSys->Read(&light->attenuation1, 4, fp);
        g_pVFileSys->Read(&light->attenuation2, 4, fp);
        g_pVFileSys->Read(&light->_field58, 4, fp);

        // Copy range as bounding sphere radius
        light->boundSphere.radius = light->range;

        // Clear bounding sphere center
        light->boundSphere.center.x = 0.0f;
        light->boundSphere.center.y = 0.0f;
        light->boundSphere.center.z = 0.0f;

        // Set dirty flag
        light->bDirty = 1;

        // IncRef on light (gbVolumeModifier inherits gbRefObject)
        light->refCount++;

        // Assign to volmod node
        volNode->pVolMod = light;

        // Release (decrement ref, balances the IncRef above)
        light->Release();

        // Add volmod node as child of root
        root->children.AddNodeOnTail((gbChain1DNode*)volNode);
        ((gbNBTreeNode*)volNode)->pParent = (gbNBTreeNode*)root;
    }

    g_pVFileSys->CloseFile(fp);
    return root;
}

int gbConvertToSBC(unsigned char* dst, int dstLen, unsigned char* src, int srcLen) {
    return MultiByteToWideChar(0, 1, (LPCSTR)src, -1, (LPWSTR)dst, dstLen) - 1;
}

// Execute external program
// 0x1002F490 (150B)
int gbExecProgram(const char* lpFileName) {
    LPSTR FilePart;
    STARTUPINFOA StartupInfo;
    PROCESS_INFORMATION ProcessInformation;
    char Buffer[256];

    memset(&StartupInfo, 0, sizeof(StartupInfo));
    StartupInfo.cb = 68;
    memset(&StartupInfo.lpReserved, 0, 12);
    StartupInfo.lpReserved2 = 0;
    StartupInfo.cbReserved2 = 0;
    if (!GetFullPathNameA(lpFileName, 0x100, Buffer, &FilePart))
        return 1;
    if (FilePart)
        *FilePart = 0;
    return CreateProcessA(lpFileName, 0, 0, 0, 0, 0x20, 0, Buffer, &StartupInfo, &ProcessInformation);
}

// Segment-triangle intersection
// param_1=segStart, param_2=segEnd, param_3=v0, param_4=v1, param_5=v2, param_6=hitPoint
int gbIntersectTriangle(gbVec3D* param_1, gbVec3D* param_2, gbVec3D* param_3, gbVec3D* param_4, gbVec3D* param_5, gbVec3D* param_6) {
    gbVec3D edge1, edge2;
    gbVec3D normal;
    gbVec3D toOrigin, segDir;
    gbVec3D tmp;
    gbVec3D edgeA, edgeB, edgeC;
    gbVec3D segVec;
    float numerator, denominator, t;

    edge1.x = 0; edge1.y = 0; edge1.z = 0;
    edge2.x = 0; edge2.y = 0; edge2.z = 0;
    normal.x = 0; normal.y = 0; normal.z = 0;
    toOrigin.x = 0; toOrigin.y = 0; toOrigin.z = 0;

    // edge1 = v1 - v0
    tmp = gbVec3D(param_4->x - param_3->x, param_4->y - param_3->y, param_4->z - param_3->z);
    edge1 = tmp;

    // edge2 = v0 - v2
    tmp = gbVec3D(param_3->x - param_5->x, param_3->y - param_5->y, param_3->z - param_5->z);
    edge2 = tmp;

    // normal = cross(edge1, edge2)
    edge1.CrossProduct(&edge2, &normal);

    // toOrigin = param_1 - v0
    tmp = gbVec3D(param_1->x - param_3->x, param_1->y - param_3->y, param_1->z - param_3->z);
    toOrigin = tmp;

    // Compute numerator: dot(normal, toOrigin) done manually
    numerator = normal.z * toOrigin.z + normal.y * toOrigin.y + toOrigin.x * normal.x;

    // segDir = param_1 - param_2
    tmp = gbVec3D(param_1->x - param_2->x, param_1->y - param_2->y, param_1->z - param_2->z);
    segDir = tmp;

    // Compute denominator: dot(segDir, normal) done manually
    denominator = segDir.z * normal.z + segDir.y * normal.y + segDir.x * normal.x;

    t = numerator / denominator;

    if (t >= 0.0f && t <= 1.0f) {
        float oneMinusT = 1.0f - t;
        gbVec3D windNormal;

        edgeA.x = 0; edgeA.y = 0; edgeA.z = 0;
        edgeB.x = 0; edgeB.y = 0; edgeB.z = 0;
        edgeC.x = 0; edgeC.y = 0; edgeC.z = 0;
        segVec.x = 0; segVec.y = 0; segVec.z = 0;

        // hitPoint = t*param_2 + (1-t)*param_1
        param_6->x = t * param_2->x + oneMinusT * param_1->x;
        param_6->y = oneMinusT * param_1->y + t * param_2->y;
        param_6->z = oneMinusT * param_1->z + t * param_2->z;

        // edgeA = param_1 - v0
        tmp = gbVec3D(param_1->x - param_3->x, param_1->y - param_3->y, param_1->z - param_3->z);
        edgeA = tmp;

        // edgeB = param_1 - v1
        tmp = gbVec3D(param_1->x - param_4->x, param_1->y - param_4->y, param_1->z - param_4->z);
        edgeB = tmp;

        // edgeC = param_1 - v2 (via subtraction function)
        edgeC.x = param_1->x - param_5->x;
        edgeC.y = param_1->y - param_5->y;
        edgeC.z = param_1->z - param_5->z;

        // segVec = param_6 - param_1 (via subtraction function)
        segVec.x = param_6->x - param_1->x;
        segVec.y = param_6->y - param_1->y;
        segVec.z = param_6->z - param_1->z;

        // Winding test 1: cross(edgeA, edgeB) . segVec >= 0
        edgeA.CrossProduct(&edgeB, &windNormal);
        if (segVec.DotProduct(&windNormal) >= 0.0f) {
            // Winding test 2: cross(edgeB, edgeC) . segVec >= 0
            edgeB.CrossProduct(&edgeC, &windNormal);
            if (segVec.DotProduct(&windNormal) >= 0.0f) {
                // Winding test 3: cross(edgeC, edgeA) . segVec >= 0
                edgeC.CrossProduct(&edgeA, &windNormal);
                if (segVec.DotProduct(&windNormal) >= 0.0f) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Low-level keyboard hook handle
static HHOOK hhk = NULL;

#ifndef VK_LWIN
#define VK_LWIN 0x5B
#endif
#ifndef VK_RWIN
#define VK_RWIN 0x5C
#endif

typedef struct {
    DWORD vkCode;
    DWORD scanCode;
    DWORD flags;
    DWORD time;
    ULONG_PTR dwExtraInfo;
} KBDLLHOOKSTRUCT_T;

// Low-level keyboard hook proc (blocks Alt+Tab, Win key, etc.)
static LRESULT CALLBACK fn(int code, WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT_T* p = (KBDLLHOOKSTRUCT_T*)lParam;
    if (!code) {
        SHORT ctrlState = GetAsyncKeyState(VK_CONTROL);
        int vkCode = p->vkCode;
        int ctrlDown = ctrlState >> 15;
        if ((vkCode == VK_ESCAPE && ctrlDown)
            || (vkCode == VK_TAB && (p->flags & 0x20))
            || (vkCode == VK_ESCAPE && (p->flags & 0x20))
            || vkCode == VK_LWIN
            || vkCode == VK_RWIN)
        {
            return 1;
        }
    }
    return CallNextHookEx(hhk, code, wParam, lParam);
}

// Enable/disable system hotkeys (Alt+Tab, Win key, etc.)
// 0x1002F530 (193B)
void gbEnableSystemKeys(HINSTANCE hInst, int enable) {
    BYTE pvParam[4];
    OSVERSIONINFOA VersionInformation;

    VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    GetVersionExA(&VersionInformation);

    if (VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        if (VersionInformation.dwMajorVersion >= 4) {
            if (!enable) {
                hhk = SetWindowsHookExA(13, fn, hInst, 0);
            } else {
                if (hhk) {
                    UnhookWindowsHookEx(hhk);
                    hhk = NULL;
                }
            }
        }
    } else if (VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS
               && VersionInformation.dwMajorVersion >= 4) {
        if (!enable)
            SystemParametersInfoA(0x61, 1, pvParam, 0);
        else
            SystemParametersInfoA(0x61, 0, pvParam, 0);
    }
}

// Get current display mode
void gbGetCurDispMode(int& width, int& height, int& bpp) {
    width = g_CurDispWidth;
    height = g_CurDispHeight;
    bpp = g_CurDispBpp;
}

// Get real world time
// 0x10030040 (125B)
void gbGetRealWorldTime(gbRealWorldTime* a1) {
    SYSTEMTIME SystemTime;
    GetLocalTime(&SystemTime);
    a1->day = SystemTime.wDay;
    a1->dayOfWeek = SystemTime.wDayOfWeek;
    a1->hour = SystemTime.wHour;
    a1->milliseconds = SystemTime.wMilliseconds;
    a1->minute = SystemTime.wMinute;
    a1->month = SystemTime.wMonth;
    a1->second = SystemTime.wSecond;
    a1->year = SystemTime.wYear;
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

// 0x1002F0B0 (179B)
void gbInitDispSetting(void)
{
    DEVMODEA DevMode;
    BOOL result;
    DWORD iModeNum;
    FILE* fp;

    result = EnumDisplaySettingsA(NULL, 0, &DevMode);
    fp = fopen("disp_ogl.txt", "wt");
    iModeNum = 0;
    if (result) {
        do {
            gbDispMode* pMode = &g_dispModes[g_dispModeCount];
            pMode->width = DevMode.dmPelsWidth;
            pMode->height = DevMode.dmPelsHeight;
            pMode->bpp = DevMode.dmBitsPerPel;
            pMode->freq = DevMode.dmDisplayFrequency;
            if (fp) {
                fprintf(fp, "w=%d,h=%d,bpp=%d,freq=%d\n",
                    pMode->width, pMode->height, pMode->bpp, DevMode.dmDisplayFrequency);
            }
        } while (EnumDisplaySettingsA(NULL, iModeNum++, &DevMode));
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
        switch (result) {
        case DISP_CHANGE_BADMODE:
            sprintf(buf, "The video mode %ldx%ldx%ld-bit color is not available\n", (long)width, (long)height, (long)bpp);
            break;
        case DISP_CHANGE_FAILED:
            sprintf(buf, "Hardware failed to change to %ldx%ldx%ld-bit color\n", (long)width, (long)height, (long)bpp);
            break;
        case DISP_CHANGE_RESTART:
            sprintf(buf, "You must change your video mode to %ldx%ldx%ld-bit color and then restart\n", (long)width, (long)height, (long)bpp);
            break;
        default:
            sprintf(buf, "Failed to change to %ldx%ldx%ld-bit color mode\n", (long)width, (long)height, (long)bpp);
            break;
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

// 0x1002F400 (88B)
void gbPopDispMode(void)
{
    gbDispMode mode;
    if (g_dispStackDepth) {
        --g_dispStackDepth;
        memcpy(&mode, (char*)g_dispStack + 20 * g_dispStackDepth, sizeof(mode));
        if (!mode.width)
            ChangeDisplaySettingsA(NULL, 0);
        else
            gbChangeDispMode(mode.width, mode.height, mode.bpp);
    }
}

int gbGetOSUserName(char* buf, int bufSize)
{
    GetUserNameA(buf, (DWORD*)&bufSize);
    return bufSize;
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

// ============================================================================
// gbWaterMesh - Water surface mesh class (extends gbBaseMesh)
// sizeof = 0x61C (1564 bytes): gbBaseMesh(0x78) + water-specific data
// ============================================================================

// Terrain/water data block read from file (at offset +0x78 from this)
// Total terrain data size = 0x594 = 1428 bytes (from offset +120 to +1547)
// Key sub-fields within the terrain data:
//   +140 (0x8C): m_width (int)
//   +144 (0x90): m_height (int)
//   +148 (0x94): m_scaleX (float)
//   +152 (0x98): m_scaleZ (float)
//   +160 (0xA0): m_texScaleX (float)
//   +176 (0xB0): m_texScaleZ (float)
//   +192 (0xC0): m_originX (float)
//   +200 (0xC8): m_originZ (float)
//   +208 (0xD0): m_textureName1 (char[1060])
//   +1268 (0x4F4): m_textureName2 (char[280])
// After the terrain data block:
//   +1548 (0x60C): m_pHeightfield (float*) - 2 floats per vertex [height, velocity]
//   +1552 (0x610): m_meanHeight (float)
//   +1556 (0x614): m_pLookupTable (float*)
//   +1560 (0x618): m_invScale (float)

struct gbWaterMesh : public gbBaseMesh {
    // +0x78 (120): terrain data block, 1428 bytes total
    // First 20 bytes are misc params
    char _terrainHeader[20];        // +0x78 to +0x8B
    int m_width;                    // +0x8C (140)
    int m_height;                   // +0x90 (144)
    float m_scaleX;                 // +0x94 (148)
    float m_scaleZ;                 // +0x98 (152)
    char _pad9C[4];                 // +0x9C (156)
    float m_texScaleX;              // +0xA0 (160)
    char _padA4[12];                // +0xA4 (164)
    float m_texScaleZ;              // +0xB0 (176)
    char _padB4[12];                // +0xB4 (180)
    float m_originX;                // +0xC0 (192)
    char _padC4[4];                 // +0xC4 (196)
    float m_originZ;                // +0xC8 (200)
    char _padCC[4];                 // +0xCC (204)
    char m_textureName1[1060];      // +0xD0 (208) to +0x4F3 (1267)
    char m_textureName2[280];       // +0x4F4 (1268) to +0x60B (1547)
    // End of terrain data block

    float* m_pHeightfield;          // +0x60C (1548)
    float m_meanHeight;             // +0x610 (1552)
    float* m_pLookupTable;          // +0x614 (1556)
    float m_invScale;               // +0x618 (1560)
    // Total sizeof = 0x61C (1564)

    gbWaterMesh(gbGfxManager* gfxMgr);
    virtual ~gbWaterMesh();

    void InitSinCosLookupTable(float scale, int unused);
    void InitializeGraphics();
    int LoadTerrainFromFile(gbVFile* file, int unused);
    int SimulateWaterHeightfield();
    void RenderTerrain(int viewMat, int renderInfo);
    void ComputeVertexNormal(int x, int y);
};

// Static lookup table storage (global BSS)
static float g_WaterLookupTable[768];     // dword_1013B0E0 (3 floats * 256)
static float g_WaterLookupCopy[768];      // dword_1013A4E0 (mirror copy)

// Static counter for water rendering
static int g_WaterRenderCounter = 0;      // dword_1013BCE0

// Water effect script name
static const char aGfxscriptWater[] = "gfxscript/water";

// ============================================================================
// gbOctreeNode - Octree spatial node (68 bytes, allocated from gbStaticChain)
// ============================================================================
struct gbOctreeNode {
    gbStaticChainNode chainNode;    // +0x00: prev/next for static chain (8 bytes)
    float centerX;                  // +0x08
    float centerY;                  // +0x0C
    float centerZ;                  // +0x10
    float halfSize;                 // +0x14
    float halfHalfSize;             // +0x18
    int depth;                      // +0x1C
    gbOctreeNode* children[8];      // +0x20 (32 bytes)
    void* objectListHead;           // +0x40: linked list of attached objects
    // Total: 68 bytes
};

// ============================================================================
// gbOctree - Octree spatial partitioning manager (76 bytes)
// ============================================================================
struct gbOctree {
    gbOctreeNode* pRoot;            // +0x00 (DWORD 0)
    int maxDepth;                   // +0x04 (DWORD 1)
    float centerX;                  // +0x08 (DWORD 2)
    float centerY;                  // +0x0C (DWORD 3)
    float centerZ;                  // +0x10 (DWORD 4)
    float halfSize;                 // +0x14 (DWORD 5)
    gbStaticChain nodePool;         // +0x18 (28 bytes, DWORDs 6..12)
    int stats[6];                   // +0x34 (DWORDs 13..18)

    void InitQuadtreeStats();
    void Init(int maxDepth, int maxNodes, float* center, float halfSize);
    gbOctreeNode* TraverseQuadtree(float* bounds, gbOctreeNode* node);
    void AttachNodeToOctree(int* pNode);
    static void DetachNodeRecursive(int* pNode);
};

// ============================================================================
// gbWaterMesh::gbWaterMesh - Constructor (0x100138A0, 75B)
// ============================================================================
gbWaterMesh::gbWaterMesh(gbGfxManager* gfxMgr) : gbBaseMesh(gfxMgr) {
    // Zero out sections-related area at DWORD offsets 48,49,50
    // (byte offsets 192, 196, 200 → m_originX, _padC4, m_originZ)
    m_originX = 0.0f;
    *(int*)((char*)this + 196) = 0;
    m_originZ = 0.0f;

    // Zero water-specific fields at high DWORD offsets
    // DWORD 382,383,384 → bytes 1528,1532,1536
    *(int*)((char*)this + 1528) = 0;
    *(int*)((char*)this + 1532) = 0;
    *(int*)((char*)this + 1536) = 0;

    // DWORD 387 → byte 1548 (m_pHeightfield)
    m_pHeightfield = NULL;

    // DWORD 389 → byte 1556 (m_pLookupTable)
    m_pLookupTable = NULL;

    // vtable is set automatically by compiler
}

// ============================================================================
// gbWaterMesh::~gbWaterMesh - Destructor (0x10013910, 33B)
// ============================================================================
gbWaterMesh::~gbWaterMesh() {
    free(m_pHeightfield);
    // base destructor called automatically
}

// ============================================================================
// gbWaterMesh::InitSinCosLookupTable (0x10013940, 235B)
// Initializes a trigonometric lookup table for water refraction
// ============================================================================
void gbWaterMesh::InitSinCosLookupTable(float scale, int unused) {
    m_invScale = 1.0f / scale;

    if (!m_pLookupTable) {
        m_pLookupTable = g_WaterLookupTable;
        int i = 0;
        int j = 0;
        do {
            float v = (float)i * 0.00390625f;  // i/256.0
            float sinVal = (float)sin(acos((double)v));
            float refracted = sinVal * 0.75018758f;
            float* table = m_pLookupTable;

            table[j] = (float)(cos(asin((double)refracted)) * ((double)sinVal / (double)refracted) - (double)v);
            table[j + 1] = -(refracted / sinVal);
            *(int*)&table[j + 2] = (((255 - i) * (255 - i) * (255 - i)) & 0xFFFF0000) << 8;

            g_WaterLookupCopy[j] = g_WaterLookupTable[0];
            g_WaterLookupCopy[j + 1] = g_WaterLookupTable[1];
            g_WaterLookupCopy[j + 2] = g_WaterLookupTable[2];

            j += 3;
            i++;
        } while (j < 768);
    }
}

// ============================================================================
// gbWaterMesh::InitializeGraphics (0x10013A30, 684B)
// Creates textures, index buffer, and render effect for water rendering
// ============================================================================
void gbWaterMesh::InitializeGraphics() {
    int totalVerts = m_height * m_width;

    // Set numSections = 1
    m_numSections = 1;

    // Allocate a new gbMeshSection (with scalar new, mimicking new gbMeshSection[1])
    m_sections = new gbMeshSection[1];
    m_sections->m_blendMode = 1;

    // Clear material data
    memset((char*)m_sections + 76, 0, 0x44u);
    *((int*)((char*)m_sections + 148)) = 0;
    *((int*)((char*)m_sections + 152)) = totalVerts;

    // Clear bounding center
    float* pBound = (float*)((char*)m_sections + 156);
    pBound[2] = 0.0f;
    pBound[1] = 0.0f;
    pBound[0] = 0.0f;

    // Create and load texture 1 (calls virtual NewTexture slot 2, at vtable+8)
    gbTexture* tex1 = m_pGfxManager->NewTexture(m_textureName1);
    m_sections->m_textures[0] = tex1;
    tex1->LoadTexture(1);

    // Create and load texture 2
    gbTexture* tex2 = m_pGfxManager->NewTexture(m_textureName2);
    m_sections->m_textures[1] = tex2;
    tex2->LoadTexture(1);

    // Set num textures = 2
    m_sections->m_numTextures = 2;

    // Create water render effect
    gbEffectMgr* effectMgr = *(gbEffectMgr**)((char*)m_pGfxManager + 200);
    *((int*)((char*)m_sections + 168)) = (int)effectMgr->NewRenderEffect(aGfxscriptWater, 0);

    // Build triangle strip index buffer
    unsigned short* indices = (unsigned short*)operator new(6 * totalVerts);
    int w = m_width;
    int h = m_height;
    unsigned short* pIdx = indices;

    *indices = 0;
    int pos = 1;
    int col = 0;
    int row = 0;
    int nextPos = 0;

    while (1) {
        unsigned short* cur = &pIdx[pos];
        short rowOffset = (short)(w * (row + 1));

        while (1) {
            nextPos = pos + 1;
            *cur = (unsigned short)(col + rowOffset);
            unsigned short* next = cur + 1;
            if (++col >= w)
                break;
            pos = nextPos + 1;
            *next = (unsigned short)(col + w * row);
            rowOffset = (short)(w * (row + 1));
            cur = next + 1;
        }

        int lastCol = col - 1;
        int nextRow = row + 1;
        if (nextRow >= h - 1)
            break;

        short degIdx = (short)(lastCol + w * nextRow);
        indices[nextPos] = degIdx;
        int stripPos = nextPos + 1;
        if (!(w % 2))
            indices[stripPos++] = degIdx;

        short nextRowOffset2 = (short)(w * (nextRow + 1));
        unsigned short* pCur = &indices[stripPos];
        while (1) {
            pos = stripPos + 1;
            *pCur = (unsigned short)(lastCol + nextRowOffset2);
            unsigned short* pNext = pCur + 1;
            if (--lastCol < 0)
                break;
            stripPos = pos + 1;
            *pNext = (unsigned short)(lastCol + w * nextRow);
            nextRowOffset2 = (short)(w * (nextRow + 1));
            pCur = pNext + 1;
        }

        col = lastCol + 1;
        row = nextRow + 1;
        if (row >= h - 1)
            break;

        pos = pos + 1;
        short startIdx = (short)(row * w + col);
        pIdx = indices;
        indices[pos - 1] = startIdx;
        if (!(w % 2))
            indices[pos++] = startIdx;
    }

    // Create index bubble
    gbVertPoolMgr* vpm = *(gbVertPoolMgr**)((char*)m_pGfxManager + 196);
    *((int*)((char*)m_sections + 144)) = (int)vpm->NewIndexBubble((gbPrimType)3, pos);

    // Copy indices into the index bubble
    gbIndexBubble* ib = *(gbIndexBubble**)((char*)m_sections + 144);
    memcpy(ib->Lock32(), indices, 2 * pos);
    ib->Unlock();

    // Set index range
    int ibPtr = *((int*)((char*)m_sections + 144));
    *(int*)(ibPtr + 32) = w * h - 1;
    *(int*)(ibPtr + 28) = 0;

    operator delete(indices);
}

// ============================================================================
// gbWaterMesh::LoadTerrainFromFile (0x10013CE0, 266B)
// Loads terrain data from a gbVFile
// ============================================================================
int gbWaterMesh::LoadTerrainFromFile(gbVFile* file, int unused) {
    char header[12];
    float tempFloat;

    // Read 12-byte header (unused)
    g_pVFileSys->Read(header, 0xCu, file);

    // Read terrain data block (0x594 bytes starting at offset +120)
    g_pVFileSys->Read((void*)((int)this + 120), 0x594u, file);

    // Allocate heightfield buffer (2 floats per vertex: height + velocity)
    m_pHeightfield = (float*)malloc(8 * m_height * m_width);

    // Initialize heightfield to zero
    int total = m_height * m_width;
    int i = 0;
    if (total > 0) {
        do {
            i++;
            m_pHeightfield[2 * i - 2] = 0.0f;
            m_pHeightfield[2 * i - 1] = 0.0f;
        } while (i < m_height * m_width);
    }

    // Initialize lookup table
    InitSinCosLookupTable(m_scaleX, 1092616192);

    // Initialize graphics resources
    InitializeGraphics();

    // Compute bounding box
    float halfX = m_scaleX * -0.5f;
    float halfZ = m_scaleZ * -0.5f;
    *(int*)((int)this + 92) = 0;  // aabb.vMin.y = 0
    tempFloat = halfZ;
    *(float*)((int)this + 88) = halfX;       // aabb.vMin.x
    *(float*)((int)this + 96) = tempFloat;   // aabb.vMin.z

    float halfX2 = m_scaleX * 0.5f;
    float halfZ2 = m_scaleZ * 0.5f;
    *(int*)((int)this + 104) = 1036831949;   // aabb.vMax.y = ~0.3f (hex float)
    tempFloat = halfZ2;
    *(float*)((int)this + 100) = halfX2;     // aabb.vMax.x
    *(float*)((int)this + 108) = tempFloat;  // aabb.vMax.z

    return 1;
}

// ============================================================================
// gbWaterMesh::SimulateWaterHeightfield (0x10013DF0, 305B)
// Simulates water wave propagation using finite differences
// ============================================================================
int gbWaterMesh::SimulateWaterHeightfield() {
    int w = m_width;
    int h = m_height;
    double totalHeight = 0.0;
    int prevRow = w * (h - 1);
    int curRowStart = 0;
    int nextRowStart = w;

    do {
        int prev = w - 1;
        int cur = 0;
        int next = 1;

        do {
            float* hf = m_pHeightfield;

            // Average 4 direct neighbors (weight 1/6)
            float directAvg = (hf[2 * (cur + nextRowStart)]
                + hf[2 * (next + curRowStart)]
                + hf[2 * (prev + curRowStart)]
                + hf[2 * (cur + prevRow)])
                * 0.16666667f;

            // Average 4 diagonal neighbors (weight 1/12)
            float diagAvg = hf[2 * (next + nextRowStart)]
                + hf[2 * (prev + nextRowStart)]
                + hf[2 * (next + prevRow)]
                + hf[2 * (prevRow + prev)];

            float* pVertex = &hf[2 * (cur + curRowStart)];
            float avg = directAvg + diagAvg * 0.083333336f;

            // Damping
            if (pVertex[1] > 0.000099999997f || pVertex[1] < -0.000099999997f)
                pVertex[1] = pVertex[1] * 0.99000001f;

            w = m_width;

            // Velocity update: v += (avg - height) * 0.25
            float newVelocity = (avg - *pVertex) * 0.25f + pVertex[1];
            pVertex[1] = newVelocity;

            // Height update: h += v
            float newHeight = newVelocity + *pVertex;
            prev = cur;
            cur = next;
            totalHeight = totalHeight + (double)newHeight;
            next = (next + 1) % m_width;
        } while (cur);

        prevRow = curRowStart;
        curRowStart = nextRowStart;
        nextRowStart = (nextRowStart + m_width) % (m_width * h);
    } while (nextRowStart != 0);

    m_meanHeight = (float)(totalHeight / (double)(m_width * h));
    return (nextRowStart + m_width) / (m_width * h);
}

// ============================================================================
// gbWaterMesh::RenderTerrain (0x10013F30, 1200B)
// Main water surface rendering - transforms and fills dynamic vertex buffer
// ============================================================================
void gbWaterMesh::RenderTerrain(int a2, int a3) {
    // Periodically disturb the water surface
    if (!(g_WaterRenderCounter % 4000000))
        ComputeVertexNormal(m_width / 2, m_height / 2);
    g_WaterRenderCounter++;

    // Simulate water physics
    SimulateWaterHeightfield();

    // Get dynamic vertex buffer (FVF 0x13 = XYZ|NORMAL|TEX1 → stride 32)
    gbVertPoolMgr* vpm = *(gbVertPoolMgr**)((char*)m_pGfxManager + 196);
    gbDynVertBuf* dvb = vpm->GetDynVertBuf(0x13u);

    // Push world matrix stack
    gbMatrixStack* matStack = *(gbMatrixStack**)((char*)m_pGfxManager + 224);
    matStack->Push();

    // Get view matrix, zero translation, invert
    gbMatrix4 invView;
    gbMatrixStack* viewStack = *(gbMatrixStack**)((char*)m_pGfxManager + 216);
    memcpy(&invView, viewStack->GetTop(), sizeof(gbMatrix4));
    memset(invView.m[3], 0, 12);
    invView.Invert();
    matStack->LoadMatrix(&invView);

    int w = m_width;
    int h = m_height;
    int totalVerts = w * h;

    // Lock vertex buffer via virtual call (slot 3, offset 12 in vtable)
    typedef float* (__cdecl *LockFn)(gbDynVertBuf*, int);
    float* pVerts = ((LockFn)(*(int*)(*(int*)dvb + 12)))(dvb, totalVerts);

    int curRowStart = w;
    int prevRow = w * (h - 1);
    float zPos = m_originZ;
    float stepSize = m_scaleX / (float)(w - 1);
    float texScaleX = m_texScaleX / m_scaleX;
    float texScaleZ = m_texScaleZ / m_scaleZ;

    gbVec3D normal;
    gbVec3D viewDir;
    memset(&normal, 0, sizeof(normal));
    memset(&viewDir, 0, sizeof(viewDir));

    int nextRowStart = 0;
    int v8 = 0;
    int v9 = prevRow;
    int v40 = w;

    do {
        float xPos = m_originX;
        int prevColI = w - 1;
        int nextColI = 1;
        float zSq = zPos * zPos;

        while (1) {
            float* hf = m_pHeightfield;
            int curVertIdx = prevColI + nextRowStart;

            // Compute surface height (velocity + height)
            float height = hf[2 * curVertIdx + 1] + hf[2 * curVertIdx];
            hf[2 * curVertIdx] = height;  // update stored height
            float surfaceH = height - m_meanHeight;

            // Compute approximate normal from neighbors
            int nextIdx = nextColI + v40;
            float* hfData = m_pHeightfield;
            normal.x = hfData[2 * (v9 + prevColI)] - hfData[2 * nextIdx];
            normal.z = normal.x;
            normal.z += hfData[2 * (prevColI + prevRow)] - hfData[2 * (prevColI + v40)] + normal.z;
            float crossTerm = hfData[2 * (nextColI + prevRow)] - hfData[2 * (prevColI + v40)];
            normal.x = normal.x - crossTerm;
            normal.z = normal.z + crossTerm;
            float sideTerm = hfData[2 * (v8 + prevColI)] - hfData[2 * (nextColI + v8)];
            normal.y = 1.0f;
            normal.x = sideTerm + normal.x;
            normal.Normalize();

            // Compute view direction
            viewDir.z = -zPos;
            viewDir.x = -xPos;
            viewDir.y = 1000.0f - surfaceH;
            viewDir.Normalize();

            // Dot product for refraction lookup
            float dotVal = viewDir.y * normal.y + viewDir.z * normal.z + viewDir.x * normal.x;
            int lookupIdx = (int)(dotVal * -255.0f);
            float* lookupEntry = m_pLookupTable + (-lookupIdx * 3);

            // Write vertex position
            pVerts[0] = xPos;
            pVerts[1] = surfaceH;
            pVerts[2] = zPos;

            // Write normal
            pVerts[3] = normal.x;
            pVerts[4] = normal.y;
            pVerts[5] = normal.z;

            // Compute reflected direction
            float reflX = lookupEntry[0] * normal.x;
            float reflY = lookupEntry[0] * normal.y;
            float rx = reflX + viewDir.x;
            float ry = viewDir.y + reflY;
            float refractFactor = lookupEntry[1];
            float rfx = rx * refractFactor;
            float rfy = ry * refractFactor;
            float rfz = (lookupEntry[0] * normal.z + viewDir.z) * refractFactor;

            // Check if point is within refraction sphere
            float dy = surfaceH - 2000.0f;
            float distSq = dy * dy + xPos * xPos + zSq - 12250000.0f;

            if (distSq >= 0.0f) {
                // Simple UV mapping
                pVerts[6] = (xPos - m_originX) * texScaleX;
                pVerts[7] = (zPos - m_originZ) * texScaleZ;
            } else {
                // Refraction UV mapping
                float projDot = dy * rfy + rfx * xPos + rfz * zPos;
                float discriminant = (float)sqrt((double)((projDot + projDot) * (projDot + projDot) - distSq * 4.0f));
                float t = (discriminant - (projDot + projDot)) * 0.5f;
                pVerts[6] = (rfx * t + xPos - m_originX) * texScaleX;
                pVerts[7] = (rfz * t + zPos - m_originZ) * texScaleZ;
            }

            // Advance to next column
            prevColI = nextColI - 1;
            int nextNext = (nextColI + 1) % w;
            xPos = xPos + stepSize;
            pVerts += 8;  // stride = 32 bytes = 8 floats
            nextColI = nextNext;

            if (nextNext == 0)
                break;

            v9 = prevRow;
            v8 = v8;
        }

        // Advance to next row (circular)
        nextRowStart = v40;
        prevRow = v8;
        zPos = zPos + stepSize;
        v8 = v40;
        prevRow = nextRowStart;
        v40 = (v40 + w) % totalVerts;
    } while (v40 != 0);

    // Draw the water surface via DynVertBuf virtual call (slot 4, offset 16)
    typedef void (__cdecl *DrawFn)(gbDynVertBuf*, int, int, int);
    ((DrawFn)(*(int*)(*(int*)dvb + 16)))(
        dvb,
        *((int*)((char*)m_sections + 144)),   // index bubble
        *(int*)(a3 + 12),                     // render effect
        (int)((char*)m_sections + 8));        // texture array

    // Pop matrix stack
    matStack->Pop();
}

// ============================================================================
// gbWaterMesh::ComputeVertexNormal (0x100143E0, 441B)
// Disturbs the water heightfield at a given point (ripple effect)
// ============================================================================
void gbWaterMesh::ComputeVertexNormal(int x, int y) {
    if (x < 0)
        return;
    if (x >= m_width || y < 0 || y >= m_height)
        return;

    // Perturb center vertex
    *(float*)((int)this + 124) = 1045220557;  // set some param (float ~0.03)
    m_pHeightfield[2 * (x + y * m_width) + 1] -= 0.050000001f;

    // Perturb 4 direct neighbors
    if (x > 0)
        m_pHeightfield[2 * (x + y * m_width) - 1] -= 0.025f;

    if (x < m_width - 1)
        m_pHeightfield[2 * (x + y * m_width) + 3] -= 0.025f;

    if (y > 0) {
        int idx = x + m_width * (y - 1);
        m_pHeightfield[2 * idx + 1] -= 0.025f;
    }

    if (y < m_height - 1) {
        int idx = x + m_width * (y + 1);
        m_pHeightfield[2 * idx + 1] -= 0.025f;
    }

    // Perturb 4 diagonal neighbors
    if (x > 0 && y > 0) {
        int idx = x + m_width * (y - 1);
        m_pHeightfield[2 * idx - 1] -= 0.0125f;
    }

    if (x < m_width - 1 && y < m_height - 1)
        m_pHeightfield[2 * (x + m_width * (y + 1)) + 3] -= 0.0125f;

    if (x > 0 && y < m_height - 1) {
        int idx = x + m_width * (y + 1);
        m_pHeightfield[2 * idx - 1] -= 0.0125f;
    }

    if (x < m_width - 1 && y > 0) {
        int idx = x + m_width * (y - 1);
        m_pHeightfield[2 * idx + 3] -= 0.0125f;
    }
}

// ============================================================================
// gbOctree::InitQuadtreeStats (0x10013880, 23B)
// Zeroes 6 statistic counters
// ============================================================================
void gbOctree::InitQuadtreeStats() {
    stats[0] = 0;
    stats[1] = 0;
    stats[2] = 0;
    stats[3] = 0;
    stats[4] = 0;
    stats[5] = 0;
}

// ============================================================================
// gbOctree::Init (0x100145A0, 161B)
// Initializes the octree with center, half-size, and max depth
// ============================================================================
void gbOctree::Init(int depth, int maxNodes, float* center, float size) {
    centerX = 0.0f;
    centerY = 0.0f;
    centerZ = 0.0f;
    *(float*)&nodePool.pBuffer = 0.0f;  // zero the chain at float offset 6
    *(float*)&nodePool.pIterator = 0.0f;   // float offset 9
    *(float*)&nodePool.pUsedHead = 0.0f;   // float offset 8
    *(float*)&nodePool.pFreeHead = 0.0f;   // float offset 7

    maxDepth = depth;
    centerX = center[0];
    centerY = center[1];
    centerZ = center[2];
    halfSize = *(float*)&size;

    nodePool.InitBuffer(maxNodes, 68);

    float hs = halfSize;
    gbStaticChainNode* rootNode = nodePool.NewOneNode();
    gbOctreeNode* root = (gbOctreeNode*)rootNode;
    root->centerX = centerX;
    root->centerY = centerY;
    root->centerZ = centerZ;
    root->halfSize = hs;
    root->halfHalfSize = hs * 0.5f;
    root->depth = 0;
    root->objectListHead = NULL;
    memset(root->children, 0, 0x20u);
    pRoot = root;
}

// ============================================================================
// gbOctree::TraverseQuadtree (0x10014660, 362B)
// Traverses the octree to find/create the leaf node for a given bounding sphere
// ============================================================================
gbOctreeNode* gbOctree::TraverseQuadtree(float* bounds, gbOctreeNode* node) {
    gbOctreeNode* cur = node;

    while (cur->depth < maxDepth) {
        // If object's bounding radius > quarter of node size, stop here
        if (cur->halfSize * 0.25f <= bounds[0])
            break;

        // Determine which octant the center falls in
        float dy = bounds[1] - cur->centerX;
        int octant = (dy > 0.0f) ? 1 : 0;

        float dz = bounds[2] - cur->centerY;
        if (dz > 0.0f)
            octant |= 2;

        float dw = bounds[3] - cur->centerZ;
        if (dw > 0.0f)
            octant |= 4;

        // Create child node if it doesn't exist
        if (!cur->children[octant]) {
            float childHalfSize = cur->halfSize * 0.5f;
            float cx, cy, cz;

            cx = cur->centerX;
            if (octant & 1)
                cx = cx + childHalfSize;
            else
                cx = cx - childHalfSize;

            cy = cur->centerY;
            if (octant & 2)
                cy = cy + childHalfSize;
            else
                cy = cy - childHalfSize;

            cz = cur->centerZ;
            if (octant & 4)
                cz = cz + childHalfSize;
            else
                cz = cz - childHalfSize;

            int childDepth = cur->depth + 1;
            gbStaticChainNode* newNode = nodePool.NewOneNode();
            gbOctreeNode* child = (gbOctreeNode*)newNode;
            child->centerX = cx;
            child->centerY = cy;
            child->centerZ = cz;
            child->halfSize = childHalfSize;
            child->halfHalfSize = childHalfSize * 0.5f;
            child->depth = childDepth;
            child->objectListHead = NULL;
            memset(child->children, 0, 0x20u);
            cur->children[octant] = child;
        }

        cur = cur->children[octant];
    }

    return cur;
}

// ============================================================================
// gbOctree::AttachNodeToOctree (0x100147D0, 154B)
// Attaches a scene node to the octree by computing its bounding sphere
// and traversing to the appropriate octree node
// ============================================================================
void gbOctree::AttachNodeToOctree(int* pNode) {
    float bounds[4];

    memset(&bounds[1], 0, 12);
    // Call GetBoundSphere virtual method (vtable slot at offset 28)
    typedef void (__cdecl *GetBoundFn)(int*, float*);
    ((GetBoundFn)(*(int*)(*(int*)pNode + 28)))(pNode, bounds);

    if (bounds[0] > 0.0f) {
        // Find the appropriate octree node
        gbOctreeNode* octNode = TraverseQuadtree(bounds, pRoot);

        // Store octree node reference in scene node
        pNode[17] = (int)octNode;
        pNode[19] = 0;
        pNode[18] = 0;

        // Insert into octree node's object linked list (head insertion)
        int head = (int)octNode->objectListHead;
        if (head) {
            pNode[19] = head;
            *(int*)(head + 72) = (int)pNode;  // prev of old head = new node
        }
        octNode->objectListHead = (void*)pNode;
    }

    // Recursively attach all children
    int child = pNode[3];  // first child (gbNBTreeNode::children.pHead)
    pNode[6] = child;      // store as iterator
    while (child) {
        AttachNodeToOctree((int*)child);
        child = *(int*)(pNode[6] + 4);  // pNext
        pNode[6] = child;
    }
}

// ============================================================================
// gbOctree::DetachNodeRecursive (0x10014870, 109B)
// Recursively detaches a scene node and all children from the octree
// ============================================================================
void gbOctree::DetachNodeRecursive(int* pNode) {
    // Recursively detach all children first
    int child = pNode[3];  // first child
    pNode[6] = child;
    while (child) {
        DetachNodeRecursive((int*)child);
        child = *(int*)(pNode[6] + 4);  // pNext
        pNode[6] = child;
    }

    // Detach this node from its octree node
    int octNode = pNode[17];  // octree node reference (byte 68)
    if (octNode) {
        int prev = pNode[18];  // prev in linked list (byte 72)
        if (prev)
            *(int*)(prev + 76) = pNode[19];  // prev->next = our next

        int next = pNode[19];  // next in linked list (byte 76)
        if (next)
            *(int*)(next + 72) = pNode[18];  // next->prev = our prev

        // If we are the head of the octree node's list, update it
        if (pNode == *(int**)(octNode + 64))
            *(int*)(octNode + 64) = pNode[19];

        pNode[17] = 0;
        pNode[19] = 0;
        pNode[18] = 0;
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    return TRUE;
}

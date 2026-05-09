// PAL3.exe WinMain.cpp - Matching Decompilation
// Compiler: MSVC 7.1 (cl.exe 13.10.3077)
// Optimization: /O2 /Ob2 /Oi /Ot /Oy /GF /Gy (FPO, full optimization)

#include <windows.h>
#include <stdio.h>
#include <string.h>

// Global variables
extern "C" char Data[260];              // CD drive path buffer
extern "C" char Filename[260];          // exe path buffer
extern "C" double dbl_1895070;          // last frame time
extern "C" double g_CurrentTime;        // current time
extern "C" DWORD dword_5833B8;          // game active flag
extern "C" HINSTANCE hInstance;         // global hInstance
extern "C" char WindowName[];           // "PAL3--SOFTSTAR.sh"

// String constants (must match .rdata layout)
static const char aSoftwareSoftst_1[] = "software\\softstar\\pal3";
static const char aCdriver[] = "CDriver";
static const char asc_5D41EC[] = "\\";
static const char aPal3[] = "PAL3";

// External functions
extern "C" void __cdecl gbUpdateCurTime(void);
extern "C" BOOL __cdecl sub_5382D0(const char* path);

class PAL3 {
public:
    static void __cdecl Create(int ebp_frame, HINSTANCE hInst);
    static void __cdecl Update(float dt);
    static void __cdecl Render(void);
    static void __cdecl Destroy(void);
};

class CCBSystem {
public:
    static int __cdecl ProcUseItem(HWND hwnd);
};

// ========================================================================
// LowLevelKeyboardProc (fn in IDA)
// Address: 0x005417C0, Size: 121 bytes
// __stdcall, ret 12
// ========================================================================
LRESULT __stdcall fn(int code, WPARAM wParam, int *lParam)
{
    int v3;
    LRESULT result;

    if (code)
        return CallNextHookEx(0, code, wParam, (LPARAM)lParam);
    switch (wParam)
    {
    case 0x100u:
    case 0x101u:
    case 0x104u:
    case 0x105u:
        v3 = *lParam;
        if (v3 != 91
            && v3 != 92
            && v3 != 93
            && (v3 != 9 || (lParam[2] & 0x20) == 0)
            && (v3 != 27 || (lParam[2] & 0x20) == 0 && (((unsigned short)GetKeyState(17) >> 8) & 0x80u) == 0))
        {
            return CallNextHookEx(0, code, wParam, (LPARAM)lParam);
        }
        result = 1;
        break;
    default:
        return CallNextHookEx(0, code, wParam, (LPARAM)lParam);
    }
    return result;
}

// ========================================================================
// GetDefaultCD
// Address: 0x00541860, Size: 118 bytes
// __cdecl, no frame pointer
// ========================================================================
extern "C" void __cdecl GetDefaultCD(void)
{
    char v0;
    unsigned char v2;
    char RootPathName[8];

    v0 = 'A';
    v2 = 'A';
    while (1)
    {
        sprintf(RootPathName, "%c:\\", v2);
        if (GetDriveTypeA(RootPathName) == 5)
            break;
        v2 = ++v0;
        if ((unsigned char)v0 > 0x5Au)
            return;
    }
    UINT len = strlen(RootPathName) + 1;
    memcpy(Data, RootPathName, len);
}

// ========================================================================
// ReadRegistry (sub_541C40)
// Address: 0x00541C40, Size: 114 bytes
// __cdecl char(CHAR *lpSubKey, LPCSTR lpValueName, LPBYTE lpData)
// ========================================================================
extern "C" char __cdecl sub_541C40(char *lpSubKey, const char *lpValueName, BYTE *lpData)
{
    DWORD cbData;
    DWORD Type;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, lpSubKey, 0, 0x20019u, (PHKEY)&lpSubKey))
    {
        *lpData = 0;
        return 0;
    }
    else
    {
        cbData = 324;
        Type = 1;
        RegQueryValueExA((HKEY)lpSubKey, lpValueName, 0, &Type, lpData, &cbData);
        RegCloseKey((HKEY)lpSubKey);
        return 1;
    }
}

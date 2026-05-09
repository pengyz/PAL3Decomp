// PAL3.exe WinMain.cpp - Matching Decompilation
// Compiler: MSVC 7.1 (cl.exe 13.10.3077) — note: WinMain.cpp was compiled by VC7.1
// The rest of PAL3 code is compiled by VC6 SP5, but this particular TU uses VC7.1
// Optimization: /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /EHsc
// Note: WinMain uses ebp frame due to SEH; helper functions use FPO

#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>
#include <string.h>

// ============================================================
// Global variables (defined elsewhere, linked)
// ============================================================
extern "C" char Data[260];              // 0x01894970 - CD drive path buffer
extern "C" char Filename[260];          // 0x01894A74 - exe path buffer
extern "C" double dbl_1895070;          // 0x01895070 - last frame time
extern "C" DWORD g_bGameActive;          // 0x005833B8 - game active flag
extern "C" HINSTANCE hInstance;         // 0x00BFDA48 - global hInstance
extern "C" char WindowName[];           // 0x005839C4 - "PAL3--SOFTSTAR.sh"

// gbengine.dll import - g_CurrentTime accessed via IAT pointer
__declspec(dllimport) double g_CurrentTime;  // IAT at 0x0056A4F4

// ============================================================
// String constants
// ============================================================
// These are in .data section at known addresses
extern "C" char aSoftwareSoftst_1[];    // 0x00609010 "software\softstar\pal3"
extern "C" char aCdriver[];             // 0x00609028 "CDriver"
extern "C" char asc_5D41EC[];           // 0x005D41EC "\\"
extern "C" char aPal3[];                // 0x00608FDC "Pal3"
extern "C" char aPercentSMovie[];       // 0x00609008 "%sMovie"
extern "C" char aPlsInsertDisc[];       // 0x00608FE4 "Please Insert Disc4 to Dirver %c:"
extern "C" char aPal3Exception[];       // 0x00608FC8 "Pal3::Exception ..."

// ============================================================
// External functions
// ============================================================
__declspec(dllimport) double __cdecl gbUpdateCurTime(void);  // IAT 0x0056A4F8
extern "C" BOOL __cdecl sub_5382D0(const char* path);  // check directory exists
extern "C" char __cdecl ReadRegistryValue(char *lpSubKey, const char *lpValueName, BYTE *lpData);

// Exception class used in PAL3
class _Exception {
public:
    char message[1024];
};

// Helper for exception message display
extern "C" void __cdecl sub_408BC0(void *buf, const char *msg, int code);
extern "C" DWORD dword_BFD774;  // 0x00BFD774 - MessageBoxA proc address?

// ============================================================
// Class declarations
// ============================================================
class PAL3 {
public:
    static void __cdecl Create(HINSTANCE hInst);       // 0x00404800
    static void __cdecl Update(float dt);              // 0x004055D0
    static void __cdecl Render(void);                  // 0x00405C00
    static void __cdecl Destroy(void);                 // 0x00406230
};

class CCBSystem {
public:
    unsigned long ProcUseItem(unsigned long hwnd);  // 0x00513380 (__thiscall)
};

extern "C" void *g_pCBSystem;  // CCBSystem instance pointer  0x00BFDA74

// ========================================================================
// LowLevelKeyboardProc
// Address: 0x005417C0, Size: 121 bytes
// __stdcall, ret 12
// Blocks Win keys, App key, Alt+Tab, Alt+Escape while game is running
// ========================================================================
LRESULT __stdcall LowLevelKeyboardProc(int code, WPARAM wParam, int *lParam)
{
    int vkCode;
    LRESULT result;

    if (code)
        return CallNextHookEx(0, code, wParam, (LPARAM)lParam);
    switch (wParam)
    {
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
        vkCode = *lParam;
        if (vkCode != VK_LWIN
            && vkCode != VK_RWIN
            && vkCode != VK_APPS
            && (vkCode != VK_TAB || (lParam[2] & 0x20) == 0)
            && (vkCode != VK_ESCAPE || (lParam[2] & 0x20) == 0 && (((unsigned short)GetKeyState(VK_CONTROL) >> 8) & 0x80u) == 0))
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
// __cdecl, FPO (no frame pointer)
// ========================================================================
extern "C" void __cdecl GetDefaultCD(void)
{
    char driveLetter;
    unsigned char driveChar;
    char RootPathName[8];

    driveLetter = 'A';
    driveChar = 'A';
    while (1)
    {
        sprintf(RootPathName, "%c:\\", driveChar);
        if (GetDriveTypeA(RootPathName) == DRIVE_CDROM)
            break;
        driveChar = ++driveLetter;
        if ((unsigned char)driveLetter > 'Z')
            return;
    }
    size_t len = strlen(RootPathName) + 1;
    memcpy(Data, RootPathName, len);
}

// ========================================================================
// WinMain
// Address: 0x00541900, Size: 824 bytes
// __stdcall (ret 16), has ebp frame (due to C++ EH)
// EH structure: try { ... } catch (_Exception&) { show error }
// States: 0=in try, 1=v8 allocated (needs delete on unwind)
// ========================================================================
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    HWND WindowA;
    BOOL i;
    char *v7;
    void *v8;
    double v9;
    HWND ActiveWindow;
    CHAR Text[256];
    char Buffer[324];
    struct tagMSG Msg;
    int v16;
    void *v17;
    int v18;
    char v19;
    char v20;
    char v21;
    HHOOK hhk;
    float hInstancea;

    WindowA = FindWindowA(WindowName, WindowName);
    if (IsWindow(WindowA))
    {
        ShowWindow(WindowA, SW_SHOWNORMAL);
        return 0;
    }
    hInstance = hInst;
    hhk = SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, hInst, 0);
    memset(Data, 0, sizeof(Data));
    if (!(unsigned char)ReadRegistryValue(aSoftwareSoftst_1, aCdriver, (BYTE *)Data))
        GetDefaultCD();
    if (!strrchr((const char *)Data, '\\'))
        strcat((char *)Data, asc_5D41EC);
    sprintf(Buffer, aPercentSMovie, (const char *)Data);
    for (i = sub_5382D0(Buffer); !i; i = sub_5382D0(Buffer))
    {
        sprintf(Text, aPlsInsertDisc, (char)Data[0]);
        if (MessageBoxA(0, Text, aPal3, MB_OKCANCEL | MB_ICONINFORMATION) == IDCANCEL)
            return 0;
    }
    memset(Filename, 0, sizeof(Filename));
    GetModuleFileNameA(0, Filename, 260);
    v7 = strrchr(Filename, '\\');
    if (v7)
        *v7 = 0;
    PAL3::Create(hInst);
    gbUpdateCurTime();
    v16 = 20;
    *((__int64 *)&dbl_1895070) = *((__int64 *)&g_CurrentTime);
    v8 = operator new(0x50u);
    v17 = v8;
    memset(v8, 0, 0x50u);
    v18 = 0;
    v19 = 1;
    v20 = 0;
    v21 = 0;
    while (1)
    {
        if (!PeekMessageA(&Msg, 0, 0, 0, 0))
            goto LABEL_20;
        if (!GetMessageA(&Msg, 0, 0, 0))
            break;
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
    LABEL_20:
        gbUpdateCurTime();
        v9 = g_CurrentTime - dbl_1895070;
        *((__int64 *)&dbl_1895070) = *((__int64 *)&g_CurrentTime);
        hInstancea = (float)v9;
        if (g_bGameActive || (ActiveWindow = GetActiveWindow(), ((CCBSystem *)g_pCBSystem)->ProcUseItem((unsigned long)ActiveWindow)))
        {
            PAL3::Update(hInstancea);
            PAL3::Render();
        }
        else
        {
            Sleep(100u);
        }
    }
    if (v8)
        operator delete(v8);
    UnhookWindowsHookEx(hhk);
    PAL3::Destroy();
    return Msg.wParam;
}

// ========================================================================
// ReadRegistryValue
// Address: 0x00541C40, Size: 114 bytes
// __cdecl, FPO (no frame pointer)
// ========================================================================
extern "C" char __cdecl ReadRegistryValue(char *lpSubKey, const char *lpValueName, BYTE *lpData)
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

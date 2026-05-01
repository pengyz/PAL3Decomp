/**
 * PAL3 Decompilation Project - WinMain Implementation
 *
 * Address: 0x00541900 (388 bytes)
 * Compiler: MSVC 7.1 (VS2003)
 * Calling convention: __stdcall (WinMain signature)
 *
 * This file implements the main entry point for PAL3.exe, including:
 *   - CD-ROM detection and registry reading
 *   - Movie folder verification (disc check)
 *   - Low-level keyboard hook for blocking system keys
 *   - Main message loop with frame timing
 */

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "pal3/gbengine_dynamic.h"
#include "pal3/pal3_game.h"

/* ========================================================================
 * Global Variables
 * ======================================================================== */

char g_cdDrivePath[260];        // 0x01894970
char g_exePath[260];            // 0x01894a74
double g_lastFrameTime;         // 0x01895070
char* g_cmdLine;                // 0x01896d10

static HHOOK g_hKeyboardHook;

/* ========================================================================
 * Forward Declarations
 * ======================================================================== */

static int ReadRegistry(const char* subKey, const char* valueName, char* outBuffer);
static void DetectCDDrive(void);
static bool CheckFileExists(const char* path);
static LRESULT CALLBACK KbdHookProc(int nCode, WPARAM wParam, LPARAM lParam);
static int IsOurGameWindow(HWND hwnd);
static void CleanupObject(void* ptr);

/* FrameRender declared in pal3_game.h */

/* ========================================================================
 * WinMain - Main entry point
 * ======================================================================== */

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    HWND hwndExisting;
    char moviePath[260];
    char* lastSlash;
    double currentTime;
    float deltaTime;
#ifndef PAL3_DEV_MODE
    char driveLetter;
    char errorMsg[280];
#endif

    /* Save command line */
    g_cmdLine = lpCmdLine;

    /* Check for duplicate instance */
    hwndExisting = FindWindowA("PAL3--SOFTSTAR.sh", NULL);
    if (hwndExisting != NULL) {
        SetForegroundWindow(hwndExisting);
        return 0;
    }

#ifndef PAL3_DEV_MODE
    /* Install low-level keyboard hook */
    g_hKeyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, KbdHookProc, hInstance, 0);
#endif

    /* Zero-fill CD drive path buffer */
    memset(g_cdDrivePath, 0, sizeof(g_cdDrivePath));

    /* Read CD drive path from registry */
    if (!ReadRegistry("software\\softstar\\pal3", "CDriver", g_cdDrivePath)) {
        /* Registry read failed, detect CD drive */
        DetectCDDrive();
    }

    /* Verify CD drive path ends with backslash */
    lastSlash = strrchr(g_cdDrivePath, '\\');
    if (lastSlash == NULL) {
        /* No backslash found, append one */
        strcat(g_cdDrivePath, "\\");
    }

    /* Build movie path and check if it exists */
    sprintf(moviePath, "%sMovie", g_cdDrivePath);
#ifndef PAL3_DEV_MODE
    while (!CheckFileExists(moviePath)) {
        /* Movie folder not found, prompt user to insert disc */
        driveLetter = g_cdDrivePath[0];
        sprintf(errorMsg, "Please Insert Disc4 to Dirver %c", driveLetter);
        MessageBoxA(NULL, errorMsg, "PAL3", MB_OK | MB_ICONWARNING);
    }
#endif

    /* Get executable path */
    memset(g_exePath, 0, sizeof(g_exePath));
    GetModuleFileNameA(NULL, g_exePath, 0x104);

    /* Truncate at last backslash to get directory */
    lastSlash = strrchr(g_exePath, '\\');
    if (lastSlash != NULL) {
        *(lastSlash + 1) = '\0';
    }

    /* Initialize game */
    PAL3_Create(hInstance);

    /* Load gbengine.dll */
    if (!LoadGBEngine()) {
#ifdef PAL3_DEV_MODE
        MessageBoxA(NULL,
            "PAL3 Dev Build\n\n"
            "gbengine.dll not found. Running in stub mode.\n"
            "Place gbengine.dll next to PAL3.exe for full functionality.",
            "PAL3 Dev", MB_OK | MB_ICONINFORMATION);
#endif
    }

    /* Initialize frame timing */
    if (pfn_gbUpdateCurTime != NULL) {
        g_lastFrameTime = pfn_gbUpdateCurTime();
    } else {
        g_lastFrameTime = 0.0;
    }

    /* Main message loop */
    while (1) {
        /* Process all pending messages */
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                goto cleanup;
            }
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        /* Only update/render if window is active */
        if (PAL3_s_bActive && IsOurGameWindow(GetActiveWindow())) {
            /* Update frame timing */
            if (pfn_gbUpdateCurTime != NULL) {
                currentTime = pfn_gbUpdateCurTime();
                deltaTime = (float)(currentTime - g_lastFrameTime);
                g_lastFrameTime = currentTime;
            } else {
                deltaTime = 0.0f;
            }

            /* Update game logic */
            PAL3_Update(deltaTime);

            /* Render frame */
            FrameRender();
        } else {
            /* Window is inactive, sleep to reduce CPU usage */
            Sleep(100);
        }
    }

cleanup:
    /* Cleanup */
    if (g_hKeyboardHook != NULL) {
        UnhookWindowsHookEx(g_hKeyboardHook);
        g_hKeyboardHook = NULL;
    }

    PAL3_Destroy();

    return (int)msg.wParam;
}

/* ========================================================================
 * ReadRegistry - Read string value from HKEY_LOCAL_MACHINE
 * Address: 0x00541c40 (114 bytes)
 * ======================================================================== */

static int ReadRegistry(const char* subKey, const char* valueName, char* outBuffer)
{
    HKEY hKey;
    LSTATUS status;
    DWORD bufSize;
    DWORD type;

    status = RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_READ, &hKey);
    if (status != ERROR_SUCCESS) {
        *outBuffer = '\0';
        return 0;
    }

    bufSize = 0x144;  /* 324 bytes max */
    type = REG_SZ;
    RegQueryValueExA(hKey, valueName, NULL, &type, (LPBYTE)outBuffer, &bufSize);
    RegCloseKey(hKey);

    return 1;
}

/* ========================================================================
 * DetectCDDrive - Find first CD-ROM drive letter
 * Address: 0x00541860 (118 bytes)
 * ======================================================================== */

static void DetectCDDrive(void)
{
    char drivePath[8];
    char letter;

    for (letter = 'A'; letter <= 'Z'; letter++) {
        sprintf(drivePath, "%c:\\", letter);
        if (GetDriveTypeA(drivePath) == DRIVE_CDROM) {
            strcpy(g_cdDrivePath, drivePath);
            return;
        }
    }
}

/* ========================================================================
 * CheckFileExists - Check if path exists and is a directory
 * Address: 0x005382d0 (69 bytes)
 * ======================================================================== */

static bool CheckFileExists(const char* path)
{
    WIN32_FIND_DATAA findData;
    HANDLE hFind;

    hFind = FindFirstFileA(path, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return false;
    }

    FindClose(hFind);
    return (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

/* ========================================================================
 * KbdHookProc - Low-level keyboard hook
 * Address: 0x005417c0 (121 bytes)
 *
 * Blocks Windows keys, Alt+Tab, Ctrl+Esc, and Alt+Esc to prevent
 * users from leaving the game.
 * ======================================================================== */

static LRESULT CALLBACK KbdHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* pKbd;

    if (nCode == HC_ACTION) {
        pKbd = (KBDLLHOOKSTRUCT*)lParam;

        switch (wParam) {
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
            /* Block Windows keys */
            if (pKbd->vkCode == VK_LWIN || pKbd->vkCode == VK_RWIN || pKbd->vkCode == VK_APPS) {
                return 1;
            }

            /* Block Alt+Tab */
            if (pKbd->vkCode == VK_TAB && (pKbd->flags & LLKHF_ALTDOWN)) {
                return 1;
            }

            /* Block Alt+Esc and Ctrl+Esc */
            if (pKbd->vkCode == VK_ESCAPE) {
                if (pKbd->flags & LLKHF_ALTDOWN) {
                    return 1;
                }
                if (GetKeyState(VK_CONTROL) & 0x8000) {
                    return 1;
                }
            }
            break;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

/* ========================================================================
 * Stubs
 * ======================================================================== */

/* IsOurGameWindow - Check if hwnd is our game window (0x00513380) */
static int IsOurGameWindow(HWND hwnd)
{
    /* Stub: always return true for now */
    return 1;
}

/* CleanupObject - Mysterious cleanup function (0x00541d10, 538 callers) */
static void CleanupObject(void* ptr)
{
    /* Stub: does nothing for now */
}

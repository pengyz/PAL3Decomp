/**
 * PAL3 Decompilation Project - gbengine.dll Dynamic Loading Layer
 *
 * This header declares function pointers and loading functions for dynamically
 * loading gbengine.dll at runtime via LoadLibrary/GetProcAddress.
 */

#pragma once

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================
 * gbengine.dll types (minimal forward declarations)
 * ======================================================================== */

struct gbGfxDriverInfo {
    int type;
    int subtype;
    int width;
    int height;
    int colorbits;
    int depthbits;
    int stensilbits;
    int nbackbuf;
    int fullscreen;
    int refreshrate;
    char winname[0x80];
    DWORD hinst;
    HWND hgfxwnd;
    int newwindow;
    int waitforverticalblank;
};

struct gbGfxManager;

/* ========================================================================
 * gbengine.dll Module Handle
 * ======================================================================== */

extern HMODULE g_hGBEngine;

/* ========================================================================
 * Function Pointer Types
 * ======================================================================== */

typedef double (__cdecl *PFN_gbUpdateCurTime)(void);
typedef struct gbGfxManager* (__cdecl *PFN_gbCreateGraphManager)(struct gbGfxDriverInfo*);

/* gbGfxManager virtual method call helpers (thiscall) */
typedef int (__thiscall *PFN_gbGfxManager_BeginScene)(struct gbGfxManager*);
typedef void (__thiscall *PFN_gbGfxManager_EndScene)(struct gbGfxManager*);

/* ========================================================================
 * Function Pointers (resolved at runtime)
 * ======================================================================== */

extern PFN_gbUpdateCurTime pfn_gbUpdateCurTime;
extern PFN_gbCreateGraphManager pfn_gbCreateGraphManager;

/* ========================================================================
 * Global Variable Pointers (resolved at runtime)
 * ======================================================================== */

extern double* pg_CurrentTime;

/* ========================================================================
 * Loading and Unloading Functions
 * ======================================================================== */

BOOL LoadGBEngine(void);
void UnloadGBEngine(void);

#ifdef __cplusplus
}
#endif

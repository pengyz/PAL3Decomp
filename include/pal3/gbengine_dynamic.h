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

/* gbMatrixStack methods (thiscall, called from UI rendering) */
struct gbMatrixStack;
typedef void (__thiscall *PFN_gbMatrixStack_Push)(struct gbMatrixStack*);
typedef void (__thiscall *PFN_gbMatrixStack_Pop)(struct gbMatrixStack*);
typedef void (__thiscall *PFN_gbMatrixStack_LoadIdentity)(struct gbMatrixStack*);

/* gbCamera methods (thiscall, from gbengine.dll) */
typedef void (__thiscall *PFN_gbCamera_SetDimention)(void* camera, int width, int height);

/* Bink video API (stdcall, from binkw32.dll via IAT) */
typedef void (__stdcall *PFN_BinkDoFrame)(void* bink);
typedef void (__stdcall *PFN_BinkCopyToBuffer)(void* bink, void* buf, int pitch, int height, int x, int y, unsigned int flags);
typedef void (__stdcall *PFN_BinkNextFrame)(void* bink);

/* ========================================================================
 * Function Pointers (resolved at runtime)
 * ======================================================================== */

extern PFN_gbUpdateCurTime pfn_gbUpdateCurTime;
extern PFN_gbCreateGraphManager pfn_gbCreateGraphManager;
extern PFN_gbMatrixStack_Push pfn_gbMatrixStack_Push;
extern PFN_gbMatrixStack_Pop pfn_gbMatrixStack_Pop;
extern PFN_gbMatrixStack_LoadIdentity pfn_gbMatrixStack_LoadIdentity;
extern PFN_gbCamera_SetDimention pfn_gbCamera_SetDimention;
extern PFN_BinkDoFrame pfn_BinkDoFrame;
extern PFN_BinkCopyToBuffer pfn_BinkCopyToBuffer;
extern PFN_BinkNextFrame pfn_BinkNextFrame;

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

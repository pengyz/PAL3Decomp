/**
 * PAL3 Decompilation Project - gbengine.dll Dynamic Loading Implementation
 *
 * Runtime loading of gbengine.dll using LoadLibrary/GetProcAddress.
 */

#include "pal3/gbengine_dynamic.h"
#include <stdio.h>

/* ========================================================================
 * Module Handle
 * ======================================================================== */

HMODULE g_hGBEngine = NULL;

/* ========================================================================
 * Function Pointers
 * ======================================================================== */

PFN_gbUpdateCurTime pfn_gbUpdateCurTime = NULL;
PFN_gbCreateGraphManager pfn_gbCreateGraphManager = NULL;

/* ========================================================================
 * Global Variable Pointers
 * ======================================================================== */

double* pg_CurrentTime = NULL;

/* ========================================================================
 * LoadGBEngine - Load gbengine.dll and resolve function addresses
 * ======================================================================== */

BOOL LoadGBEngine(void)
{
    g_hGBEngine = LoadLibraryA("gbengine.dll");
    if (g_hGBEngine == NULL) {
#ifdef PAL3_DEV_MODE
        OutputDebugStringA("PAL3 DEV: gbengine.dll not found, running without graphics\n");
        return FALSE;
#else
        MessageBoxA(NULL,
            "Failed to load gbengine.dll.\n"
            "Please ensure gbengine.dll is in the same directory as PAL3.exe.",
            "PAL3 Error",
            MB_OK | MB_ICONERROR);
        return FALSE;
#endif
    }

    /* ?gbUpdateCurTime@@YANXZ */
    pfn_gbUpdateCurTime = (PFN_gbUpdateCurTime)GetProcAddress(
        g_hGBEngine, "?gbUpdateCurTime@@YANXZ");

    /* ?gbCreateGraphManager@@YAPAVgbGfxManager@@PAUgbGfxDriverInfo@@@Z */
    pfn_gbCreateGraphManager = (PFN_gbCreateGraphManager)GetProcAddress(
        g_hGBEngine, "?gbCreateGraphManager@@YAPAVgbGfxManager@@PAUgbGfxDriverInfo@@@Z");

    /* ?g_CurrentTime@@3NA */
    pg_CurrentTime = (double*)GetProcAddress(
        g_hGBEngine, "?g_CurrentTime@@3NA");

    if (pfn_gbUpdateCurTime == NULL || pfn_gbCreateGraphManager == NULL) {
#ifdef PAL3_DEV_MODE
        OutputDebugStringA("PAL3 DEV: Failed to resolve gbengine functions\n");
#else
        MessageBoxA(NULL,
            "Failed to resolve required functions from gbengine.dll.",
            "PAL3 Error",
            MB_OK | MB_ICONERROR);
#endif
        UnloadGBEngine();
        return FALSE;
    }

    return TRUE;
}

/* ========================================================================
 * UnloadGBEngine - Free gbengine.dll and clear all function pointers
 * ======================================================================== */

void UnloadGBEngine(void)
{
    pfn_gbUpdateCurTime = NULL;
    pfn_gbCreateGraphManager = NULL;
    pg_CurrentTime = NULL;

    if (g_hGBEngine != NULL) {
        FreeLibrary(g_hGBEngine);
        g_hGBEngine = NULL;
    }
}

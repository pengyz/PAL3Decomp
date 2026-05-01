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
PFN_gbMatrixStack_Push pfn_gbMatrixStack_Push = NULL;
PFN_gbMatrixStack_Pop pfn_gbMatrixStack_Pop = NULL;
PFN_gbMatrixStack_LoadIdentity pfn_gbMatrixStack_LoadIdentity = NULL;
PFN_gbCamera_SetDimention pfn_gbCamera_SetDimention = NULL;
PFN_BinkDoFrame pfn_BinkDoFrame = NULL;
PFN_BinkCopyToBuffer pfn_BinkCopyToBuffer = NULL;
PFN_BinkNextFrame pfn_BinkNextFrame = NULL;

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

    /* gbMatrixStack methods */
    pfn_gbMatrixStack_Push = (PFN_gbMatrixStack_Push)GetProcAddress(
        g_hGBEngine, "?Push@gbMatrixStack@@QAEXXZ");
    pfn_gbMatrixStack_Pop = (PFN_gbMatrixStack_Pop)GetProcAddress(
        g_hGBEngine, "?Pop@gbMatrixStack@@QAEXXZ");
    pfn_gbMatrixStack_LoadIdentity = (PFN_gbMatrixStack_LoadIdentity)GetProcAddress(
        g_hGBEngine, "?LoadIdentity@gbMatrixStack@@QAEXXZ");

    /* gbCamera methods */
    pfn_gbCamera_SetDimention = (PFN_gbCamera_SetDimention)GetProcAddress(
        g_hGBEngine, "?SetDimention@gbCamera@@QAEXHH@Z");

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
    pfn_gbMatrixStack_Push = NULL;
    pfn_gbMatrixStack_Pop = NULL;
    pfn_gbMatrixStack_LoadIdentity = NULL;
    pfn_gbCamera_SetDimention = NULL;
    pfn_BinkDoFrame = NULL;
    pfn_BinkCopyToBuffer = NULL;
    pfn_BinkNextFrame = NULL;
    pg_CurrentTime = NULL;

    if (g_hGBEngine != NULL) {
        FreeLibrary(g_hGBEngine);
        g_hGBEngine = NULL;
    }
}

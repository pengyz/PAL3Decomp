/**
 * PAL3 Decompilation - Global Variable Declarations
 *
 * All global variables identified from the original binary.
 * Add entries here as globals are discovered during decompilation.
 *
 * Naming convention:
 *   g_xxx      - simple global
 *   g_pXxx     - global pointer
 *   g_nXxx     - global count/number
 *   g_bXxx     - global boolean
 *   g_szXxx    - global string buffer
 */

#ifndef PAL3_GLOBALS_H
#define PAL3_GLOBALS_H

#include "pal3_types.h"

/* ========================================================================
 * Engine State Globals
 * ======================================================================== */

/* TODO: Fill in as globals are identified from Ghidra
 *
 * Example:
 *   extern HWND             g_hWnd;          // Main window handle
 *   extern HINSTANCE        g_hInstance;      // Application instance
 *   extern BOOL32           g_bRunning;      // Game loop flag
 *   extern u32              g_dwFrameCount;  // Frame counter
 *   extern f32              g_fDeltaTime;    // Time since last frame
 */

/* ========================================================================
 * Rendering Globals
 * ======================================================================== */

/* TODO:
 *   extern IDirect3DDevice8 *g_pd3dDevice;   // D3D device
 *   extern u32               g_dwScreenWidth;
 *   extern u32               g_dwScreenHeight;
 */

/* ========================================================================
 * Game State Globals
 * ======================================================================== */

/* TODO:
 *   extern struct GameState  *g_pGameState;
 *   extern struct ScriptVM   *g_pScriptVM;
 */

/* ========================================================================
 * Global Arrays / Tables
 * ======================================================================== */

/* TODO:
 *   extern char g_szGamePath[260];
 *   extern char g_szSavePath[260];
 */

#endif /* PAL3_GLOBALS_H */

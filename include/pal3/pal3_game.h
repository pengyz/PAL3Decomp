/**
 * PAL3 Decompilation Project - Game Framework Header
 *
 * Declares core game framework functions and global variables for PAL3.exe.
 */

#pragma once

#include <windows.h>
#include "pal3/gbengine_dynamic.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================
 * Game Framework Functions
 * ======================================================================== */

void PAL3_Create(HINSTANCE hInstance);
void PAL3_Update(float deltaTime);
void PAL3_Destroy(void);
void PAL3_InitGFX(void);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void FrameRender(void);

/* ========================================================================
 * Global Variables (addresses from PAL3patch)
 * ======================================================================== */

extern HINSTANCE g_hInstance;                    /* 0x00BFDA48 */
extern int PAL3_s_gamestate;                     /* 0x00BFDA6C */
extern int PAL3_s_bActive;                       /* 0x005833B8 */
extern unsigned int PAL3_s_flag;                 /* 0x005833BC */
extern float PAL3_m_gametime;                    /* 0x00BFDAA0 */
extern struct gbGfxManager* GB_GfxMgr;           /* 0x00BFDA60 */
extern struct gbGfxDriverInfo PAL3_s_drvinfo;    /* 0x00BFD6C8 */

#ifdef __cplusplus
}
#endif

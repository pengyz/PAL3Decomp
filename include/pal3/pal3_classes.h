/**
 * PAL3 Decompilation - Game Class Declarations
 *
 * Forward declarations and minimal struct layouts for PAL3 game classes.
 * Based on PAL3patch reverse engineering and Ghidra decompilation.
 *
 * Note: Original code uses __thiscall (this in ECX). We implement these
 * as C++ class methods to get correct calling convention.
 */

#pragma once

#include <windows.h>

/* ========================================================================
 * gbBinkVideo - Bink video player wrapper (0x00A3A7D8)
 * ======================================================================== */

struct gbBinkVideo {
    char padding[0x0C];
    void* hBink;       /* offset 0x0C: HBINK handle */

    int GetWidth();          /* 0x0053c710 (11 bytes) */
    int GetHeight();         /* 0x0053c720 (12 bytes) */
    void BinkWait();         /* 0x0053c460 (16 bytes) */
};

/* ========================================================================
 * UIWnd - Base window class for UI system
 * ======================================================================== */

struct UIWnd {
    void** vtable;     /* offset 0x00: vtable pointer */
    char padding1[0x0C];
    RECT rect;         /* offset 0x10: window rect (left, top, right, bottom) */

    void MoveWindow(int x, int y);    /* 0x00445d20 (28 bytes) */
    void SetRect(RECT* pRect);        /* 0x00445fa0 (52 bytes) */
};

/* ========================================================================
 * CCBRoleState - Combat role state
 *
 * Array of role states, each entry is 0x37C bytes.
 * Offset 0x241: bExists (char)
 * Offset 0x242: bAlive (char)
 * ======================================================================== */

struct CCBRoleState {
    int IsAlive(int roleIndex);       /* 0x004ed010 (46 bytes) */
};

/* ========================================================================
 * UICursor - Mouse cursor manager (singleton at 0x005415F0)
 *
 * Offset 0x1C: bVisible (char)
 * Offset 0x1D: bSoftwareCursor (char)
 * ======================================================================== */

struct UICursor {
    char padding[0x1C];
    char bVisible;           /* offset 0x1C */
    char bSoftwareCursor;    /* offset 0x1D */

    void Show(int bShow);            /* 0x00541710 (51 bytes) */
};

extern "C" UICursor* UICursor_Inst(void);  /* 0x005415F0 */

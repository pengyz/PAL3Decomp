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
    int DrawFrameEx(void* buf, int pitch, int height, int x, int y, unsigned int flags);
                             /* 0x0053c530 (106 bytes) */
};

/* ========================================================================
 * UIWnd - Base window class for UI system
 * ======================================================================== */

struct UIWnd {
    void** vtable;     /* offset 0x00: vtable pointer */
    char padding1[0x0C];
    RECT rect;         /* offset 0x10: window rect (left, top, right, bottom) */
    char padding2[4];  /* offset 0x20 */
    void** children;   /* offset 0x24: child UIWnd* array */
    int nChildren;     /* offset 0x28: child count */
    char padding3[0x0C];
    int bVisible;      /* offset 0x38: visibility flag */
    int bEnabled;      /* offset 0x3C: enabled/interactive flag */

    void MoveWindow(int x, int y);              /* 0x00445d20 (28 bytes) */
    void SetRect(RECT* pRect);                  /* 0x00445fa0 (52 bytes) */
    void Render();                              /* 0x00445cd0 (49 bytes) */
    int Update(int msg, int param);             /* 0x00445c60 (99 bytes) */
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

/* ========================================================================
 * UIRenderObj - UI rendering scope helper (push/pop matrix stacks)
 *
 * Ctor pushes projection + view matrix stacks, loads identity.
 * Dtor pops both stacks.
 * Used as RAII guard around UI rendering calls.
 * ======================================================================== */

struct UIRenderObj {
    UIRenderObj* Ctor();             /* 0x00540f60 (58 bytes) */
    void Dtor();                     /* 0x00540fa0 (34 bytes) */
};

/* ========================================================================
 * GRPinput - DirectInput wrapper (global at 0x00BFAD70, sizeof=0x2958)
 *
 * Offset 0x00: m_lpDI (IDirectInput8*)
 * Offset 0x04: m_lpDIDKeyboard (IDirectInputDevice8*)
 * Offset 0x08: m_lpDIDMouse (IDirectInputDevice8*)
 * Offset 0x68: m_keyStates[270]
 * Offset 0x176: m_shiftedKeyStates[270]
 * Offset 0x278: m_keyPressTimes[270] (ULONG)
 * Offset 0x6B0: m_keyDragStartPositions[270][2] (ULONG)
 * Offset 0x1878: m_DIKToKEY[256] + misc
 * Offset 0x186C: m_bMouse (int)
 * Offset 0x1870: m_bKeyboard (int)
 * ======================================================================== */

struct GRPinput {
    void* m_lpDI;                    /* offset 0x00: IDirectInput8* */
    void* m_lpDIDKeyboard;           /* offset 0x04: IDirectInputDevice8* */
    void* m_lpDIDMouse;              /* offset 0x08: IDirectInputDevice8* */
    char padding1[0x186C - 0x0C];
    int m_bMouse;                    /* offset 0x186C */
    int m_bKeyboard;                 /* offset 0x1870 */
    char padding2[0x2958 - 0x1874];

    void AcquireMouse();             /* 0x00402310 (65 bytes) */
    void AcquireKeyboard();          /* 0x00402380 (75 bytes) */
    void ClearKeyStates();           /* 0x00402220 (77 bytes) */
    void GetCursorPos(POINT* pt);    /* 0x004022e0 (14 bytes) */
    void SetCursorPos(int x, int y); /* 0x00402290 (19 bytes) */
};

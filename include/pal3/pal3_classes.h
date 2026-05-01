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
    void** vfptr;      /* offset 0x00: vtable pointer */
    POINT m_pos;       /* offset 0x04: display position (x, y) */
    void* hBink;       /* offset 0x0C: HBINK handle */

    int GetWidth();          /* 0x0053c710 (11 bytes) */
    int GetHeight();         /* 0x0053c720 (12 bytes) */
    void BinkWait();         /* 0x0053c460 (16 bytes) */
    int DrawFrameEx(void* buf, int pitch, int height, int x, int y, unsigned int flags);
                             /* 0x0053c530 (106 bytes) */
    int DrawFrame();         /* 0x0053c470 (190 bytes) */
};

/* ========================================================================
 * UIWnd - Base window class for UI system
 * ======================================================================== */

struct UIWnd {
    void** vtable;     /* offset 0x00: vtable pointer */
    char padding1[8];  /* offset 0x04: unknown */
    int m_id;          /* offset 0x0C: window ID */
    RECT rect;         /* offset 0x10: window rect (left, top, right, bottom) */
    void* m_pParent;   /* offset 0x20: parent UIWnd* */
    void** children;   /* offset 0x24: child UIWnd* array */
    int nChildren;     /* offset 0x28: child count */
    char padding3[8];  /* offset 0x2C: unknown */
    int m_bFocusable;  /* offset 0x34: focusable flag */
    int bVisible;      /* offset 0x38: visibility flag */
    int bEnabled;      /* offset 0x3C: enabled/interactive flag */

    void Create(int id, RECT* pRect, void* parent);  /* 0x00445b90 (87 bytes) */
    void SetEnabled(int bEnable);               /* 0x00445e50 (17 bytes) */
    void GetRect(RECT* pOut);                   /* 0x00445fe0 (36 bytes) */
    void MoveWindow(int x, int y);              /* 0x00445d20 (28 bytes) */
    void SetRect(RECT* pRect);                  /* 0x00445fa0 (52 bytes) */
    void Render();                              /* 0x00445cd0 (49 bytes) */
    int Update(int msg, int param);             /* 0x00445c60 (99 bytes) */
};

/* ========================================================================
 * UIFrameWnd - Framed window (extends UIWnd at 0x00..0x3F)
 *
 * Offset 0x40: unknown (4 bytes)
 * Offset 0x44: m_pFrameTex (texture/resource handle for frame border)
 * ======================================================================== */

struct UIFrameWnd {
    /* Inherits UIWnd fields at 0x00..0x3F */
    void** vtable;     /* offset 0x00 */
    char padding1[8];
    int m_id;          /* offset 0x0C */
    RECT rect;         /* offset 0x10 */
    void* m_pParent;   /* offset 0x20 */
    void** children;   /* offset 0x24 */
    int nChildren;     /* offset 0x28 */
    char padding3[8];
    int m_bFocusable;  /* offset 0x34 */
    int bVisible;      /* offset 0x38 */
    int bEnabled;      /* offset 0x3C */
    /* UIFrameWnd-specific fields */
    int padding4;      /* offset 0x40 */
    int m_pFrameTex;   /* offset 0x44: frame texture handle */

    void Render();           /* 0x0043ddf0 (74 bytes) */
};

/* ========================================================================
 * CCBLineupWindow - Combat lineup window (extends UIFrameWnd)
 *
 * Offset 0x60: pages[N] (UIWnd* array, indexed by currentPage)
 * Offset 0x74: currentPage (int)
 * ======================================================================== */

struct CCBLineupWindow {
    char base[0x60];         /* UIFrameWnd base + more fields */
    void** pages;            /* offset 0x60: page UIWnd pointers (inline array) */
    char padding_pages[0x10];
    int currentPage;         /* offset 0x74 */

    void Render();           /* 0x0051b920 (22 bytes) */
    int IsPtOnFace(int pageIdx, int x, int y);  /* 0x0051b950 (80 bytes) */
};

/* ========================================================================
 * SoundMgr - Sound manager
 *
 * Offset 0x328: m_pAudioMgr (gbAudioManager*)
 * ======================================================================== */

struct SoundMgr {
    char padding[0x328];
    void* m_pAudioMgr;      /* offset 0x328: gbAudioManager* */

    void Destroy();          /* 0x0053def0 (49 bytes) */
};

/* ========================================================================
 * Role - Game character/role object
 *
 * Large struct (>0x528 bytes), manages character movement, animation, etc.
 * ======================================================================== */

struct Role {
    char padding0[0x278];
    int m_nBehaviourFlags;   /* offset 0x278 */
    char padding1[0x4f4 - 0x27C];
    int m_nMoveState;        /* offset 0x4F4 */
    int m_nBehaviourType;    /* offset 0x4F8 */
    char padding2[8];
    int m_nAnimState;        /* offset 0x504 */
    char padding3[8];
    int m_nTargetX;          /* offset 0x510 */
    int m_nTargetY;          /* offset 0x514 */
    int m_nTargetZ;          /* offset 0x518 */
    int m_nCurrentX;         /* offset 0x51C */
    int m_nCurrentY;         /* offset 0x520 */
    int m_nCurrentZ;         /* offset 0x524 */

    void OnBehaviourFinish();  /* 0x004142e0 (98 bytes) */
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
 * CCBAttackSequen - ATB (Active Time Battle) gauge manager
 *
 * Manages ATB timers for 11 combat roles. Each role has a 0x28-byte entry
 * starting at this+0x0C. ATB max value = 0x2CEC (11500).
 * ======================================================================== */

struct CCBAttackEntry {
    float deltaTime;         /* +0x00: frame delta time */
    char padding[0x10];      /* +0x04..+0x13 */
    int atbNormal;           /* +0x14: normal ATB accumulator */
    int atbBuff;             /* +0x18: buff ATB accumulator */
    int overflowCount;       /* +0x1C: times ATB crossed max */
    unsigned char speed;     /* +0x20: normal speed */
    unsigned char buffSpeed; /* +0x21: buff speed */
    unsigned char bIsBuffing;/* +0x22: is receiving buff */
    char padding2;           /* +0x23 */
    unsigned char bExists;   /* +0x24: slot active flag */
    char padding3[3];        /* +0x25..+0x27 */
};

struct CCBAttackSequen {
    void* m_pBattleState;    /* offset 0x00: pointer (->+0x10 = CCBRoleState*) */
    char padding[8];         /* offset 0x04..0x0B */
    CCBAttackEntry entries[11];  /* offset 0x0C: 11 entries * 0x28 bytes */

    void RunOneStep();       /* 0x004dba60 (185 bytes) */
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
 * C2DSpark - 2D particle/spark effect system
 *
 * Particle array at offset 0x00, each particle is 0x2C bytes.
 * Max 0x200 (512) particles.
 * Offset 0x29 per particle: bActive (char)
 * Offset 0x5808: nHighWaterMark (int) - highest active index + 1
 * ======================================================================== */

struct C2DSpark {
    char particles[0x2C * 0x200];    /* offset 0x00: particle array */
    int nHighWaterMark;              /* offset 0x5808: tracks highest used slot */

    int CreateSingle(void* sparkData);    /* 0x004d5ec0 (83 bytes) */
};

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
 * CTrail - Trail/ribbon effect renderer
 *
 * Offset 0x04: bReady (char)
 * Offset 0x05: bEnabled (char)
 * Offset 0x08: pCamera (gbCamera*)
 * Offset 0x34: nFrameCount (int, incremented each frame)
 * Offset 0x38: nCurrentBuffer (int, = nFrameCount & 7)
 * Offset 0x3C: buffers[8] (each 0x60 bytes, matrix/transform data)
 * ======================================================================== */

struct CTrail {
    char padding0[4];        /* offset 0x00: unknown */
    char bReady;             /* offset 0x04 */
    char bEnabled;           /* offset 0x05 */
    char padding1[2];        /* offset 0x06 */
    void* pCamera;           /* offset 0x08: gbCamera* */
    char padding2[0x28];     /* offset 0x0C..0x33 */
    int nFrameCount;         /* offset 0x34 */
    int nCurrentBuffer;      /* offset 0x38 */
    char buffers[8 * 0x60];  /* offset 0x3C: 8 transform buffers */

    void Begin(void* camera);    /* 0x004c65f0 (124 bytes) */
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

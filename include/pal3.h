/**
 * PAL3 Decompilation - Master Header
 *
 * Common types, macros, and forward declarations used across the codebase.
 * This file should be included by all decompiled source files.
 */

#ifndef PAL3_H
#define PAL3_H

/* Windows and standard headers */
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ========================================================================
 * Basic Types
 * ======================================================================== */

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned __int64    u64;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed __int64      s64;

typedef float               f32;
typedef double              f64;

typedef int                 BOOL32;  /* Win32 BOOL (4 bytes) */

/* ========================================================================
 * Common Macros
 * ======================================================================== */

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  0
#endif

#define ARRAY_SIZE(a)   (sizeof(a) / sizeof((a)[0]))

/* Align to boundary */
#define ALIGN(x, a)     (((x) + ((a) - 1)) & ~((a) - 1))

/* ========================================================================
 * Math Types (to be refined from reverse engineering)
 * ======================================================================== */

typedef struct {
    f32 x, y, z;
} Vec3;

typedef struct {
    f32 x, y, z, w;
} Vec4;

typedef struct {
    f32 m[4][4];
} Matrix4x4;

typedef struct {
    f32 x, y;
} Vec2;

/* ========================================================================
 * Forward Declarations
 * Add as classes/structs are discovered
 * ======================================================================== */

/* Core engine */
/* struct RenderDevice; */
/* struct InputManager; */
/* struct AudioSystem; */

/* Game logic */
/* struct GameState; */
/* struct Character; */
/* struct BattleSystem; */

/* Script engine */
/* struct ScriptVM; */
/* struct ScriptContext; */

/* ========================================================================
 * Global Variable Declarations
 * Add as globals are identified
 * ======================================================================== */

/* Example:
 * extern struct GameState* g_pGameState;
 * extern struct RenderDevice* g_pRenderDevice;
 */

#endif /* PAL3_H */

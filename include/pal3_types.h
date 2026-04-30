/**
 * PAL3 Decompilation - Base Type Definitions
 *
 * Fundamental types matching the original MSVC compilation.
 * This file defines platform-specific sizes and common typedefs.
 */

#ifndef PAL3_TYPES_H
#define PAL3_TYPES_H

/* ========================================================================
 * Fixed-Width Integer Types
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

/* Windows BOOL is 4 bytes (int) */
typedef int                 BOOL32;

/* Pointer-sized integer */
typedef unsigned int        uptr;  /* 32-bit build */
typedef signed int          sptr;

/* ========================================================================
 * Common Constants
 * ======================================================================== */

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

/* ========================================================================
 * Utility Macros
 * ======================================================================== */

#define ARRAY_SIZE(a)       (sizeof(a) / sizeof((a)[0]))
#define ALIGN_UP(x, a)      (((x) + ((a) - 1)) & ~((a) - 1))
#define ALIGN_DOWN(x, a)    ((x) & ~((a) - 1))
#define MIN(a, b)           (((a) < (b)) ? (a) : (b))
#define MAX(a, b)           (((a) > (b)) ? (a) : (b))
#define CLAMP(x, lo, hi)    MIN(MAX(x, lo), hi)

/* Bit manipulation */
#define BIT(n)              (1u << (n))
#define BITS(x, lo, hi)    (((x) >> (lo)) & ((1u << ((hi)-(lo)+1)) - 1))

/* ========================================================================
 * Math Types
 * ======================================================================== */

/* Math constants */
#define GB_PI             3.14159265358979323846f
#define GB_FLOAT_EPSILON  1.192092896e-07f  /* FLT_EPSILON for MSVC */
#define GB_DEG_TO_RAD     0.01745329251994329576f  /* PI / 180 */
#define GB_RAD_TO_DEG     57.29577951308232087679f /* 180 / PI */

typedef struct Vec2 {
    f32 x, y;
} Vec2;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;

/* Column-major 4x4 matrix (matches D3DMATRIX layout) */
typedef struct Matrix4x4 {
    union {
        f32 m[4][4];
        struct {
            f32 _11, _12, _13, _14;
            f32 _21, _22, _23, _24;
            f32 _31, _32, _33, _34;
            f32 _41, _42, _43, _44;
        };
    };
} Matrix4x4;

typedef struct Quaternion {
    f32 x, y, z, w;
} Quaternion;

typedef struct Rect {
    s32 left, top, right, bottom;
} Rect;

typedef struct RectF {
    f32 left, top, right, bottom;
} RectF;

typedef struct Color4f {
    f32 r, g, b, a;
} Color4f;

typedef u32 Color32;  /* ARGB packed color */

/* Bounding volumes */
typedef struct AABB {
    Vec3 min;
    Vec3 max;
} AABB;

typedef struct Sphere {
    Vec3 center;
    f32 radius;
} Sphere;

/* ========================================================================
 * String Types
 * ======================================================================== */

/* Fixed-length path buffer (MAX_PATH = 260 on Windows) */
typedef char PathStr[260];

/* Fixed-length name buffer */
typedef char NameStr[64];

/* ========================================================================
 * Callback / Function Pointer Types
 * ======================================================================== */

typedef void (*VoidFunc)(void);
typedef int  (*CompareFunc)(const void *, const void *);

#endif /* PAL3_TYPES_H */

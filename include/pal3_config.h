/**
 * PAL3 Decompilation - Build Configuration
 *
 * Compilation settings that must match the original binary.
 * These ensure the compiled output is byte-compatible.
 */

#ifndef PAL3_CONFIG_H
#define PAL3_CONFIG_H

/* ========================================================================
 * Compiler Detection & Compatibility
 * ======================================================================== */

/* Verify we're building with MSVC */
#ifndef _MSC_VER
#error "PAL3 matching decompilation requires MSVC (cl.exe)"
#endif

/* Warn if MSVC version doesn't match original
 * _MSC_VER values:
 *   1200 = MSVC 6.0
 *   1300 = MSVC 7.0 (VS2002)
 *   1310 = MSVC 7.1 (VS2003)
 *   1400 = MSVC 8.0 (VS2005)
 *
 * TODO: Update after confirming from Rich Header analysis
 */
#if defined(PAL3_STRICT_COMPILER_CHECK)
  #if _MSC_VER != 1310
    #pragma message("WARNING: Original PAL3 was compiled with MSVC 7.1 (_MSC_VER=1310)")
  #endif
#endif

/* ========================================================================
 * Struct Packing
 * ======================================================================== */

/* Default MSVC packing is 8 bytes.
 * Use these macros around structs that need different packing. */
#define PAL3_PACK_PUSH(n)   __pragma(pack(push, n))
#define PAL3_PACK_POP()     __pragma(pack(pop))

/* Some game structs may use 1-byte packing (for file formats) */
#define PAL3_PACKED_STRUCT  __pragma(pack(push, 1))
#define PAL3_PACKED_END     __pragma(pack(pop))

/* ========================================================================
 * Calling Conventions
 * ======================================================================== */

/* Default: __cdecl (already compiler default with /Gd) */
#define PAL3_CDECL          __cdecl
#define PAL3_STDCALL        __stdcall
#define PAL3_THISCALL       __thiscall
#define PAL3_FASTCALL       __fastcall

/* ========================================================================
 * Inline / Force-inline
 * ======================================================================== */

#define PAL3_INLINE         __inline
#define PAL3_FORCEINLINE    __forceinline
#define PAL3_NOINLINE       __declspec(noinline)

/* ========================================================================
 * Alignment
 * ======================================================================== */

#define PAL3_ALIGN(n)       __declspec(align(n))

/* ========================================================================
 * DLL Import/Export (for matching import table entries)
 * ======================================================================== */

#define PAL3_DLLIMPORT      __declspec(dllimport)
#define PAL3_DLLEXPORT      __declspec(dllexport)

/* ========================================================================
 * Debug / Assertion
 * ======================================================================== */

#ifdef DEBUG
  #define PAL3_ASSERT(expr)  do { if (!(expr)) { __debugbreak(); } } while(0)
  #if _MSC_VER >= 1300
    #define PAL3_TRACE(fmt, ...) /* OutputDebugString or printf */
  #else
    #define PAL3_TRACE(x)
  #endif
#else
  #define PAL3_ASSERT(expr)  ((void)0)
  #if _MSC_VER >= 1300
    #define PAL3_TRACE(fmt, ...) ((void)0)
  #else
    #define PAL3_TRACE(x)
  #endif
#endif

/* ========================================================================
 * Build Constants
 * ======================================================================== */

/* Screen defaults (may be overridden at runtime) */
#define PAL3_DEFAULT_WIDTH    800
#define PAL3_DEFAULT_HEIGHT   600
#define PAL3_DEFAULT_BPP      32

/* Resource limits */
#define PAL3_MAX_PATH_LEN     260
#define PAL3_MAX_NAME_LEN     64

#endif /* PAL3_CONFIG_H */

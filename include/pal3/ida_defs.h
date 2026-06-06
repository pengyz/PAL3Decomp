#pragma once
// IDA Hex-Rays pseudo-code compatibility macros
// These allow IDA-generated code to compile directly

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#include "pal3/pal3_stl.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbActor.h"
#include "gbengine/gbActorMgr.h"
#include "gbengine/gbAudio.h"
#include "gbengine/gbGeomNode.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbMisc.h"
#include "gbengine/gbParticle.h"
#include "gbengine/gbPrintFont.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbVisNode.h"

typedef char _BYTE;
typedef unsigned short _WORD;
typedef unsigned long _DWORD;
typedef unsigned __int64 _QWORD;

// DirectInput 8 (DX SDK provides full dinput.h with IDirectInput8A)
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// (DirectInput forward declarations moved above GRPinput include)

// Allow C-style implicit void* conversion (IDA generated code relies on this)
#pragma warning(disable: 4133)  // incompatible pointer types

#define LOBYTE(x)   (*((_BYTE*)&(x)))
#define HIBYTE(x)   (*(((_BYTE*)&(x))+1))
#define LOWORD(x)   (*((_WORD*)&(x)))
#define HIWORD(x)   (*(((_WORD*)&(x))+1))
#define LODWORD(x)  (*((_DWORD*)&(x)))
#define HIDWORD(x)  (*(((_DWORD*)&(x))+1))

#define BYTE1(x)    (*(((_BYTE*)&(x))+1))
#define BYTE2(x)    (*(((_BYTE*)&(x))+2))
#define BYTE3(x)    (*(((_BYTE*)&(x))+3))

#define BYTEn(x, n) (*(((_BYTE*)&(x))+(n)))
#define WORDn(x, n) (*(((_WORD*)&(x))+(n)))

#define PAIR64(high, low) (((unsigned __int64)(high) << 32) | (unsigned long)(low))

// IDA boolean type
#ifndef BOOL
typedef int BOOL;
#endif

// Allow void* implicit conversion (C++ compatibility for IDA code)
#pragma warning(disable: 4312)  // conversion to greater size
#pragma warning(disable: 4311)  // pointer truncation
#pragma warning(disable: 4302)  // truncation
#pragma warning(disable: 4267)  // size_t conversion
#pragma warning(disable: 4244)  // narrowing
#pragma warning(disable: 4018)  // signed/unsigned mismatch

// IDA decompiler artifacts (Hex-Rays pseudo-code that leaked through codegen)
#define JUMPOUT(x)
typedef void _UNKNOWN;
#define _EAX 0
#define _EBX 0
#define _ECX 0
#define _EDX 0
#define _ESI 0
#define _EDI 0
#define _EBP 0
#define _AX 0
#define _ET1 0
#define Func 0
static void *retaddr = 0;
#define BYTE4(x) (*(((_BYTE*)&(x))+4))
#define SBYTE4(x) (*(((char*)&(x))+4))
#define COERCE_VOID_THISCALL_DWORD_DWORD_(x) ((void*)(x))

// IDA helpers
#define qmemcpy memcpy
#define SLODWORD(x) (*((_DWORD*)&(x)))
#define SHIDWORD(x) (*(((_DWORD*)&(x))+1))
#define COERCE_FLOAT(x) (*(float*)&(x))
#define COERCE_DOUBLE(x) (*(double*)&(x))
#define __PAIR64__(high, low) (((unsigned __int64)(high) << 32) | (unsigned int)(low))

// IDA FLIRT misidentifications
#define CRT_set_new_handler srand
#define __OFSUB__(x, y) (((x) ^ ((x) - (y))) & ((x) ^ (y)))

// IDA helper functions
inline int abs32(int x) { return x < 0 ? -x : x; }
inline void memset32(void *dst, unsigned long val, unsigned int count) {
    unsigned long *p = (unsigned long *)dst;
    while (count--) *p++ = val;
}
#define NAN (*(float*)&_nan_bytes)
static unsigned int _nan_bytes = 0x7FC00000;

// MSVC internal exception throw info
extern _s__ThrowInfo _TI1_AV_Exception__;

// Forward declarations for common game/engine types used in generated code
class gbMatrixStack;
class gbSound2DNode;
class gbSound3DNode;

// Note: IDA misidentifies UIWnd as stdiobuf/std::ios_base in this binary.
// gen_cpp.py post-processing replaces these with UIWnd* automatically.

// Common game functions (should be declared via annotations + codegen pipeline)
// DO NOT add function declarations here — use data/annotations/functions.json
void PushMatrixStacks(int nMode = 0);
void PopMatrixStacks(int nMode = 0);
int UIRenderQuad(...);
void UIQuadManager_Reset();

// gbengine imports used across many files
void * __cdecl gbLoadLightFile(const char *szFilename);
void * __cdecl gbCreateGraphManager(int mode);

// CRT functions that IDA references directly
extern "C" long __cdecl _ftol(double);
extern "C" unsigned char * __cdecl _mbsrchr(const unsigned char *, unsigned int);

// Bink Video SDK (external library, not in PAL3.exe)
extern "C" {
void *BinkOpen(void *data, unsigned int flags);
void BinkClose(void *bink);
int BinkDoFrame(void *bink);
int BinkWait(void *bink);
void BinkNextFrame(void *bink);
int BinkCopyToBuffer(void *bink, void *buf, int pitch, int height, int x, int y, int flags);
void *BinkOpenMiles(unsigned int freq);
void *BinkOpenDirectSound(unsigned int freq);
int BinkSetSoundSystem(void *soundsys, unsigned int freq);
}

// Suppress [[maybe_unused]] equivalent for MSVC6 (no-op)
// MSVC6 calls __thiscall "reserved for future use" when used in function pointer types
#pragma warning(disable: 4234)

// CCBSystem member function to __cdecl function pointer cast (via union type pun).
// MSVC6 C-style cast from member fn ptr to __cdecl fn ptr is illegal.
// Overloaded overloads need explicit static_cast to disambiguate.
template <typename F, typename M>
inline F mfp_cast(M mfp) {
    union { M m; F f; } u;
    u.m = mfp;
    return u.f;
}

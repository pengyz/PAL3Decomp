#pragma once
// IDA Hex-Rays pseudo-code compatibility macros
// These allow IDA-generated code to compile directly

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "pal3/pal3_stl.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbActor.h"

typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned long _DWORD;
typedef unsigned __int64 _QWORD;

// DirectInput forward declarations (used by GRPinput)
struct IDirectInput8A;
struct IDirectInputDevice8A;

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

// IDA helper: qmemcpy = memcpy
#define qmemcpy memcpy

// Note: IDA misidentifies UIWnd as stdiobuf/std::ios_base in this binary.
// gen_cpp.py post-processing replaces these with UIWnd* automatically.

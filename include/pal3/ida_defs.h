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

typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned long _DWORD;
typedef unsigned __int64 _QWORD;

// DirectInput 8 (DX SDK provides full dinput.h with IDirectInput8A)
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// GRPinput full definition (for g_Input member access in generated code)
#include "pal3/gen/GRP_KEYREG.h"
#include "pal3/gen/GRPinput.h"

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

// IDA helpers
#define qmemcpy memcpy
#define SLODWORD(x) (*((_DWORD*)&(x)))
#define SHIDWORD(x) (*(((_DWORD*)&(x))+1))
#define COERCE_FLOAT(x) (*(float*)&(x))
#define __PAIR64__(high, low) (((unsigned __int64)(high) << 32) | (unsigned int)(low))
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

// Common game functions that may be called from generated code
void PushMatrixStacks();
void PopMatrixStacks();
int UIRenderQuad(...);
void UIQuadManager_Reset();

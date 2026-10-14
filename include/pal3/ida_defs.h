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

// ttl aliases + uchar/uint now live in pal3/ida_types.h (single definition
// site, shared with standalone-compiled generated headers)
#include "pal3/ida_types.h"

// DirectInput 8 (DX SDK provides full dinput.h with IDirectInput8A)
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// (DirectInput forward declarations moved above GRPinput include)

// Allow C-style implicit void* conversion (IDA generated code relies on this)
#pragma warning(disable: 4133)  // incompatible pointer types

#define LOBYTE(x)   (*((_BYTE*)&(x)))
#define HIBYTE(x)   (*(((_BYTE*)&(x))+(sizeof(x)-1)))
#define LOWORD(x)   (*((_WORD*)&(x)))
#define HIWORD(x)   (*(((_WORD*)&(x))+1))
// 挂账⑥ C2065 补 2026-10-06：IDA 符号字宏（HIWORD 同款解引用形——位保持）
#define SLOWORD(x)  (*(((__int16*)&(x))))
#define SHIWORD(x)  (*(((__int16*)&(x))+1))
// 挂账⑥ 2026-10-06：三方 Bink API 声明（调用点 2 参证：handle+volume）——无址导入表形
extern "C" int __cdecl BinkSetVolume(int hBink, __int64 volume);
// 阶2批 2026-10-06：MMX 型（MagicUI __m64 C2065 族——MSVC6 内建型缺声明；`__int64` MSVC6 形）
typedef __int64 __m64;
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

// CRT 前向声明（T145）。A 级证据：PAL3.exe@0x55434F
//   `6a 19` push 0x19 ; `e8 1c 0e 00 00` call 0x555172 ; `59` pop ecx ; `c3` ret
//   ⇒ caller-clean = __cdecl，1 个 int 形参，void 返回。
//   VC6 公开头未声明该符号 ⇒ RenderTarget2.cpp:3262 C2065。
extern "C" void __cdecl _amsg_exit(int);
#define SLODWORD(x) (*((_DWORD*)&(x)))
#define SHIDWORD(x) (*(((_DWORD*)&(x))+1))
#define COERCE_FLOAT(x) (*(float*)&(x))
#define COERCE_DOUBLE(x) (*(double*)&(x))
#define __PAIR64__(high, low) (((unsigned __int64)(high) << 32) | (unsigned int)(low))

// 【2026-09-15 加】上面三个宏内部对实参取地址（`&(x)`）⇒ **实参必须是 lvalue**。 
// 而 Hex-Rays 会产出 `COERCE_FLOAT(GetTickCount())` 这类**对 rvalue 取地址**的形态 
// ⇒ MSVC6 报 `C2102: '&' requires l-value`（实测 pal3/src/Misc/UI3DCtrl.cpp:384/389）。 
// 下面用**取值传参的 inline 函数**替代：形参本身即 lvalue ⇒ 语义等价（按位重解释）， 
// 且 __forceinline 保证与宏一致的零开销（MSVC6 支持 __forceinline）。 
// ⚠️ 名字刻意避开双下划线开头（那是实现保留命名空间）。 
__forceinline float  _pal3_coerce_f32(unsigned long v) { return *(float *)&v; }
__forceinline double _pal3_coerce_f64(unsigned __int64 v) { return *(double *)&v; }
__forceinline long   _pal3_slo_dword(unsigned __int64 v) { return (long)(unsigned long)v; }
__forceinline long   _pal3_shi_dword(unsigned __int64 v) { return (long)(unsigned long)(v >> 32); }

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
class UIWnd;

// Common game functions (should be declared via annotations + codegen pipeline)
// DO NOT add function declarations here - use data/annotations/functions.json
//
// F80 (round 138): these two stubs were declared `void f(int nMode = 0)`
// (free function, argument passed on the STACK), which does not match the binary.
// Evidence (IDA disassembly, A-level):
//   * every one of the 22 call sites is `lea ecx, [esp+..]` / `mov ecx, ..`
//     immediately followed by `call 0x00540F60 / 0x00540FA0` -> the argument
//     travels in ECX, there is no `push` at all;
//   * callee 0x00540F60: `mov ebx, ecx ... mov eax, ebx; retn` (no stack args,
//     returns the value unchanged) -> the parameter is a POINTER, not an int.
// Correct declaration is `void __fastcall f(void *a1)`: VC6 __fastcall puts the
// first argument in ECX and the callee does its own `retn`. This both clears the
// 11+11 `cannot convert parameter 1 from 'char [4]' / '.. *' to 'int'` errors and
// makes the emitted call sequence (`lea ecx`, not the former `push`) match the
// binary. NOTE: keep this comment ASCII-only - a UTF-8 Chinese comment read as
// GBK can end a line with byte 0x5C and swallow the next line (documented gotcha).
void __fastcall PushMatrixStacks(void *a1 = 0);
void __fastcall PopMatrixStacks(void *a1 = 0);
int UIRenderQuad(...);
void UIQuadManager_Reset();

// gbengine imports used across many files
void * __cdecl gbLoadLightFile(const char *szFilename);
// [T10] 形参实证：PAL3::InitGFX@0x404FF0 调用点 `0x40500e push 0xbfd6c8` 后
// `0x405013 call [0x56a1fc]`（gbengine 导入）——0xbfd6c8 = &g_DrvInfo（globals.json
// 结构体全局，含 display/window 参数）⇒ 实参是结构体指针，`int mode` 为占位误标。
void * __cdecl gbCreateGraphManager(struct gbGfxDriverInfo *pDriverInfo);

// [T18] _TEB 最小定义：IDA 伪代码 `NtCurrentTeb()->NtTib.ExceptionList` 引用
// Windows SDK 的 _TEB（winnt.h 只前向声明、winternl.h 未引入 ⇒ C2027/C2227/C2228
// 三错同源）。A 级证据：CEffGrid@0x004C98F0 内 4c98f2 mov eax,fs:0x0 读 +
// 4c9903 mov fs:0x0,esp 写 —— fs:[0] 即 TEB.NtTib.ExceptionList（NtTib=TEB 首
// 成员、ExceptionList=NT_TIB 首成员，二者皆 offset 0，段寄存器寻址直证）。
// 仅补被引用通路所需的最小形；NT_TIB 复用 SDK winnt.h 既有定义。
struct _TEB {
    NT_TIB NtTib;
};

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

// Forward declarations for types used by decomp but not in VC6 SDK
// LPSPropValue is from MAPI (propidl.h/mapidefs.h) — not available in VC6
struct _SPropValue;
typedef struct _SPropValue *LPSPropValue;

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

// [T14/T9-F-memfnptr] 成员函数指针→位模式（实参形等价变换）：
// MSVC6 单继承 PMF 紧凑表示=4 字节纯地址（实测 sizeof==4）⇒ union 位拷贝取出
// 的 u 与原始「地址入参」字节一致；MSVC6 拒绝 PMF↔整型直接 cast（C2440，
// T9 探针实测）⇒ union 旁路是唯一不改字节的表达式形。模板参数化以容纳任意 PMF 形。
template <class PMF>
inline unsigned int pmf_to_u32(PMF pmf) {
    union { PMF p; unsigned int u; } _c;
    _c.p = pmf;
    return _c.u;
}

// Hex-Rays MACRO_NULL enumeration (None = 0)
#ifndef None
#define None 0
#endif

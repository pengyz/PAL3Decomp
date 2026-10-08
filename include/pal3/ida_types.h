#pragma once
// Minimal type base so generated headers compile standalone.
//
// <windows.h> provides the Win32 primitives generated headers reference
// (BYTE/WORD/DWORD/UINT/BOOL/...). The typedefs below are the Hex-Rays
// ttl aliases used by codegen output. ida_defs.h includes this header
// instead of redefining them — this file is the single definition site.
#include <windows.h>
// 2026-09-26：FILE（ArtistPlugIn.h 等生成头的成员类型）在 MSVC6 由 <stdio.h> 提供，
// windows.h 不带入；CatchableType 是 MSVC RTTI 内部结构，生成头（_s_CatchableTypeArray.h）
// 只用其指针 ⇒ 前向声明即可。
#include <stdio.h>

struct CatchableType;

typedef char _BYTE;
typedef unsigned short _WORD;
typedef unsigned long _DWORD;
typedef unsigned __int64 _QWORD;

// Hex-Rays type aliases (unsigned char -> uchar, unsigned int -> uint)
typedef unsigned char uchar;
typedef unsigned int uint;

#pragma once
// Minimal type base so generated headers compile standalone.
//
// <windows.h> provides the Win32 primitives generated headers reference
// (BYTE/WORD/DWORD/UINT/BOOL/...). The typedefs below are the Hex-Rays
// ttl aliases used by codegen output. ida_defs.h includes this header
// instead of redefining them — this file is the single definition site.
#include <windows.h>

typedef char _BYTE;
typedef unsigned short _WORD;
typedef unsigned long _DWORD;
typedef unsigned __int64 _QWORD;

// Hex-Rays type aliases (unsigned char -> uchar, unsigned int -> uint)
typedef unsigned char uchar;
typedef unsigned int uint;

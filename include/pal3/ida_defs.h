#pragma once
// IDA Hex-Rays pseudo-code compatibility macros
// These allow IDA-generated code to compile directly

typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned long _DWORD;
typedef unsigned __int64 _QWORD;

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
typedef int BOOL;
